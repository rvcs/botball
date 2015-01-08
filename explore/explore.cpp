// Created on Sun December 28 2014

// arm:
//     1300 - down
//     500  - grab
#define ARM_HIT_SHELF 650
#define ARM_GRAB_TOP_CUBE 600

// finger:
//     750  - clinch tight
//     500  - semi-tight grip on cube
//     150  - straight
//     

#include "rvcs_util.hpp"
#include "kovan/kovan.h"
#include <iostream>

using namespace rvcs;
using namespace std;

#define CUBE_X_OFFSET (-50)
#define BASE_MOTOR_SPEED_TARGETING 50
#define TARGETING_MOTOR_MULTIPLE   (1.0/2.0)

bool want_new_blobs();
bool want_yellow_blocks();
double time_since_event();
double time_since_transition();

bool ctrl_state_approach_orange();
void log_ctrl_state(char const * msg);

enum e_ctrl_state {
  ctrl_state_first = 1, 
  
  ctrl_state_init,
  ctrl_state_wait_for_light,
  
  ctrl_state_rotate_to_find_orange_perp,        // Out in front of shelves, rotate to be perpendicular to shelves -- initial
    ctrl_state_rotate_to_find_orange_perpB,     // Out in front of shelves, rotate to be perpendicular to shelves -- rotate until we see blocks
  ctrl_state_approach_orange_perp, 
    ctrl_state_approach_orange_perp_max,
    
  ctrl_state_backup_to_grab_cube,
  ctrl_state_forward_to_grab_cube,
  ctrl_state_grab_cube,
  ctrl_state_backup_from_orange_cube,

  other_to_end_ctrl_state
};

void log_move_mode(char const * msg);

enum e_move_mode {
  move_mode_none = 1,
  move_mode_stop,
  move_mode_spin,
  move_mode_spin_ccw,
  move_mode_target_prime_blob_spin,
  move_mode_target_prime_blob_move,

  move_mode_back_and_to_right,
  move_mode_back_and_to_left,
  
  move_mode_forward,
  move_mode_backup,

  other_to_end_move_mode
};

void log_eye_mode(char const * msg);

enum e_eye_mode {
  eye_mode_none = 1,
  eye_mode_normal,
  eye_mode_target_prime_blob,

  other_to_end_eye_mode
};

void log_arm_mode(char const * msg);

enum e_arm_mode {
  arm_mode_none = 1,
  arm_mode_down,
  arm_mode_hit_top_shelf,
  arm_mode_grab_top_cube,
  arm_mode_drop_cube,
  
  arm_mode_end
};

void log_finger_mode(char const * msg);

enum e_finger_mode {
  finger_mode_none = 1,
  finger_mode_straight,
  finger_mode_grip,
  
  finger_mode_end
};

e_ctrl_state  ctrl_state      = ctrl_state_init;
e_ctrl_state  last_ctrl_state = ctrl_state_init;
bool transitioning_to_this_state() {
  return ctrl_state != last_ctrl_state;
}

e_eye_mode    eye_mode    = eye_mode_none;
e_move_mode   move_mode   = move_mode_none;
e_arm_mode    arm_mode    = arm_mode_none;
e_finger_mode finger_mode = finger_mode_none;

double event_time = 0.0, transition_time = 0.0;
int main(int argc, char *argv[])
{
  //int i = 0;
  double start_time = seconds(), end_of_time = seconds() + 3600.0, loop_start_time = 0;
  transition_time = start_time;
  event_time = end_of_time;

  // Startup
  ctrl_state = (e_ctrl_state)rvcs::start(argc, argv, /*arm*/ 1300, /*finger*/ 500, 0, /*eye*/ 600, (int)ctrl_state);

  // The main loop
  int left_power = 0, right_power = 0;
  int eye_pos = 0, eye_pos_max = 100000, eye_pos_min = -100000;
  int loop_num, num_frames = 0;
  
  bool halt = false;
  for (loop_num = 1; !halt && rvcs_should_run_loop(ctrl_state); ++loop_num) {
    loop_start_time = seconds();
    if (transitioning_to_this_state()) {
        transition_time = loop_start_time;
    }
    last_ctrl_state = ctrl_state;
    
    log("__________________________________a", 0);
    log("loop_num", loop_num);
    log("loop_start_time", loop_start_time);
    log_ctrl_state("ctrl_start");
    log_eye_mode("ctrl_start");
    log_arm_mode("ctrl_start");
    log_finger_mode("ctrl_start");

    BlobList blobs, blobsYellow, removed, removedYellow;

    if (digital(15) || digital(14)) {
      halt = true;
      break;
    }

    // Control

    if (want_new_blobs()) {
      rvcs_camera_update();
      num_frames += 1;
    }

    if (num_frames < 20) {
      continue;
    }

    if (want_yellow_blocks()) {
      blobsYellow = rvcs_objects(1);
      blobsYellow = filter_skininess(blobsYellow, 1.0, 2.3, &removedYellow);
      log(removedYellow, "objectY", "removed_skinny_objects");
      blobsYellow = filter_area(blobsYellow, 50, 10000, &removedYellow);
      log(removedYellow, "objectY", "removed_small_objects");

      // Score the blobs, if there are more than one
      if (blobsYellow.size() > 1) {
        for (BlobList::iterator blob = blobsYellow.begin(); blob != blobsYellow.end(); ++blob) {
          blob->score = 0.0;

          // Aspect-ratio of 1.0 is ideal
          blob->score += (10.0 - blob->skininess()) * 3.0;

          // Being close to the y-axis
          blob->score += (10.0 - abs((float)blob->center.x / 12.0)) * 1.5;
        }

        blobsYellow = reorder_by_score(blobsYellow);
      }

    }

    eye_pos_min = 500;
    eye_pos_max = 750;

    
    if (ctrl_state == ctrl_state_init) {
      ctrl_state = ctrl_state_wait_for_light;

    } else if (ctrl_state == ctrl_state_wait_for_light) {
      ctrl_state = ctrl_state_rotate_to_find_orange_perp;
      
    } else if (ctrl_state == ctrl_state_rotate_to_find_orange_perp) {
      move_mode = move_mode_spin_ccw;
      ctrl_state = ctrl_state_rotate_to_find_orange_perpB;

    } else if (ctrl_state_approach_orange()) {
      blobs = rvcs_objects(0);
      blobs = filter_skininess(blobs, 1.0, 2.3, &removed);
      log(removed, "object", "removed_skinny_objects");
      blobs = filter_area(blobs, 50, 10000, &removed);
      log(removed, "object", "removed_small_objects");

      // Score the blobs, if there are more than one
      if (blobs.size() > 1) {
        for (BlobList::iterator blob = blobs.begin(); blob != blobs.end(); ++blob) {
          blob->score = 0.0;

          // Aspect-ratio of 1.0 is ideal
          blob->score += (10.0 - blob->skininess()) * 3.0;

          // Being close to the y-axis
          blob->score += (10.0 - abs((float)blob->center.x / 12.0)) * 1.5;
        }

        blobs = reorder_by_score(blobs);
      }

      // We've shortened the list to just the decent ones... We may have to handle two
      blobs = first(blobs, 2, &removed);
      log(removed, "object", "removed_lower_quality_objects");
      
      // We have a good list of blobs; what should we do (based on the control state)
      if (ctrl_state == ctrl_state_rotate_to_find_orange_perpB) {
        blobsYellow = first(blobsYellow, 2, &removedYellow);
        log(blobsYellow, "objectY", "good_objects");
        blobs = score_by_nx(blobs);
        if (blobs.size() > 0 && blobsYellow.size() >= 2) {
          ctrl_state = ctrl_state_approach_orange_perp;
          arm_mode   = arm_mode_hit_top_shelf;
        } else {
          //move_mode = move_mode_target_prime_blob_spin;
        }
      } else if (ctrl_state == ctrl_state_approach_orange_perp) {
        if (digital(8)) {
          ctrl_state = ctrl_state_backup_to_grab_cube;
          move_mode = move_mode_stop;
        } else {
          blobs = score_by_x(blobs);

          if (blobs.size() > 0) {
            move_mode = move_mode_target_prime_blob_move;
            if (time_since_transition() > 1.5) {
              eye_mode = eye_mode_target_prime_blob;
            }
          }
        }
      }
    } else if (ctrl_state == ctrl_state_backup_to_grab_cube) {
      move_mode = move_mode_backup;
      if (time_since_transition() > 1.0) {
        ctrl_state = ctrl_state_forward_to_grab_cube;
      }
    } else if (ctrl_state == ctrl_state_forward_to_grab_cube) {
      finger_mode = finger_mode_straight;
      arm_mode = arm_mode_grab_top_cube;
      move_mode = move_mode_forward;
      if (time_since_transition() > 1.2) {
        ctrl_state = ctrl_state_grab_cube;
      }
    } else if (ctrl_state == ctrl_state_grab_cube) {
      move_mode = move_mode_stop;
      if (time_since_transition() > 0.4) {
        finger_mode = finger_mode_grip;
        ctrl_state = ctrl_state_backup_from_orange_cube;
      }
    } else if (ctrl_state == ctrl_state_backup_from_orange_cube) {
      move_mode = move_mode_back_and_to_left;
      if (time_since_transition() > 1.5) {
        halt = true;
      }
    }

    log(blobs, "object", "good_objects");
    log_ctrl_state("ctrl_end");
    log_eye_mode("ctrl_end");
    log_arm_mode("ctrl_end");
    log_finger_mode("ctrl_end");

    // ----------------------------- Actions ------------------------------------
    Blob const & targetBlob = head(blobs);

    eye_pos = 600;
    if (eye_mode == eye_mode_normal) {
    } else if (eye_mode == eye_mode_target_prime_blob) {
      // Put the prime blob onto the x-axis (y==0)
      eye_pos = get_servo_position(3) + targetBlob.center.y;
    }
    if (eye_pos > eye_pos_max) { eye_pos = eye_pos_max; }
    if (eye_pos < eye_pos_min) { eye_pos = eye_pos_min; }
    rvcs_set_servo(3, eye_pos);

    if (move_mode == move_mode_spin) {
      left_power = 80; right_power = -20;
    } else if (move_mode == move_mode_spin_ccw) {
      left_power = -20; right_power = 80;
    } else if (move_mode ==   move_mode_target_prime_blob_spin) {
      left_power  = targetBlob.center.x / 5;
      right_power = (targetBlob.center.x / 5) * -1;
    } else if (move_mode ==   move_mode_target_prime_blob_move) {
      left_power = right_power = BASE_MOTOR_SPEED_TARGETING;
      left_power += (targetBlob.center.x - CUBE_X_OFFSET) * TARGETING_MOTOR_MULTIPLE;
      right_power -= (targetBlob.center.x - CUBE_X_OFFSET) * TARGETING_MOTOR_MULTIPLE;
    } else if (move_mode == move_mode_back_and_to_left) {
      left_power = right_power = -50;
      left_power -= 20;
      right_power += 20;
    } else if (move_mode == move_mode_back_and_to_right) {
      left_power = right_power = -50;
      right_power -= 20;
      left_power += 20;
    } else if (move_mode == move_mode_stop) {
      left_power = right_power = 0;
    } else if (move_mode == move_mode_backup) {
      left_power = right_power = -70;
    } else if (move_mode == move_mode_forward) {
      left_power = right_power = 70;
    }
    move(left_power, right_power);

    if (arm_mode == arm_mode_down) {
      rvcs_set_servo(0, 1300);
    } else if (arm_mode == arm_mode_hit_top_shelf) {
      rvcs_set_servo(0, ARM_HIT_SHELF);
    } else if (arm_mode == arm_mode_grab_top_cube) {
      rvcs_set_servo(0, ARM_GRAB_TOP_CUBE);
    } else if (arm_mode == arm_mode_drop_cube) {
      rvcs_set_servo(0, 1100); //?????
    }
    
    if (finger_mode == finger_mode_straight) {
      rvcs_set_servo(1, 150);
    } else if (finger_mode == finger_mode_grip) {
      rvcs_set_servo(1, 500);
    }

    log("loop_compute_time", seconds() - loop_start_time);
    if (time_since(start_time) > 20.0) { break; }
    //if (loop_num > 10) { break; }
  }

  rvcs::end();
	return 0;
}

bool want_new_blobs() {
  return true;
}

bool want_yellow_blocks() {
  return true;
}

bool ctrl_state_approach_orange() {
  if (ctrl_state >= ctrl_state_approach_orange_perp && ctrl_state <= ctrl_state_approach_orange_perp_max) {
    return true;
  }

  if (ctrl_state == ctrl_state_rotate_to_find_orange_perpB) {
    return true;
  }

  return false;
}

char const * to_name(e_ctrl_state enu) {
  switch(enu) {
    case ctrl_state_rotate_to_find_orange_perp:  return "ctrl_state_rotate_to_find_orange_perp"; break;
    case ctrl_state_rotate_to_find_orange_perpB:  return "ctrl_state_rotate_to_find_orange_perpB"; break;
    case ctrl_state_approach_orange_perp:     return "ctrl_state_approach_orange_perp";     break;
    case ctrl_state_approach_orange_perp_max: return "ctrl_state_approach_orange_perp_max"; break;
  }

  return "unknown";
}

void log_ctrl_state(char const * msg) {
  string name("ctrl_state_");
  name += msg;
  log(name.c_str(), ctrl_state, to_name(ctrl_state));
}

char const * to_name(e_eye_mode enu) {
  switch(enu) {
  }

  return "unknown";
}

void log_eye_mode(char const * msg) {
  string name("eye_mode_");
  name += msg;
  log(name.c_str(), eye_mode, to_name(eye_mode));
}

char const * to_name(e_arm_mode enu) {
  switch(enu) {
  }

  return "unknown";
}

void log_arm_mode(char const * msg) {
  string name("arm_mode_");
  name += msg;
  log(name.c_str(), arm_mode, to_name(arm_mode));
}

char const * to_name(e_finger_mode enu) {
  switch(enu) {
  }

  return "unknown";
}

void log_finger_mode(char const * msg) {
  string name("finger_mode_");
  name += msg;
  log(name.c_str(), finger_mode, to_name(finger_mode));
}

double time_since_event() {
  return seconds() - event_time;
}

double time_since_transition() {
  return seconds() - transition_time;
}
