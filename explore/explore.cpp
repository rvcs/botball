// Created on Sun December 28 2014

#include "rvcs_util.hpp"
#include "kovan/kovan.h"
#include <iostream>

using namespace rvcs;
using namespace std;

bool want_new_blobs();
bool want_yellow_blocks();
bool ctrl_state_approach_orange();
void log_ctrl_state();

enum e_ctrl_state {
  ctrl_state_first = 1, 
  ctrl_state_rotate_to_find_orange_right,
    ctrl_state_rotate_to_find_orange_rightB,
  ctrl_state_approach_orange_right, 
    ctrl_state_approach_orange_right_max,

  other_to_end_ctrl_state
};

enum e_move_mode {
  move_mode_none = 1,
  move_mode_spin,
  move_mode_spin_ccw,
  move_mode_target_prime_blob_spin,
  move_mode_target_prime_blob_move,

  move_mode_back_and_to_right,
  move_mode_back_and_to_left,

  other_to_end_move_mode
};

enum e_eye_mode {
  eye_mode_none = 1,
  eye_mode_normal,
  eye_mode_target_prime_blob,

  other_to_end_eye_mode
};

enum e_arm_state {
};

e_ctrl_state ctrl_state = ctrl_state_rotate_to_find_orange_right;
e_eye_mode  eye_mode  = eye_mode_normal;
e_move_mode move_mode = move_mode_none;

int main(int argc, char *argv[])
{
  int i = 0;
  double start_time = seconds(), loop_start_time = 0;

  // Startup
  if (!rvcs::start()) {
    die();
  }

  // The main loop
  int left_power = 0, right_power = 0;
  int eye_pos = 0, eye_pos_max = 100000, eye_pos_min = -100000;
  int loop_num, num_frames = 0;
  bool halt = false;
  for (loop_num = 1; !halt; ++loop_num) {
    log("__________________________________a", 0);
    log("loop_num", loop_num);
    log("loop_start_time", loop_start_time = seconds());
    log_ctrl_state();

    BlobList blobs, blobsYellow, removed, removedYellow;

    if (digital(8) || digital(15) || digital(14)) {
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

    if (ctrl_state == ctrl_state_rotate_to_find_orange_right) {
      move_mode = move_mode_spin_ccw;
      ctrl_state = ctrl_state_rotate_to_find_orange_rightB;

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
      if (ctrl_state == ctrl_state_rotate_to_find_orange_rightB) {
        blobsYellow = first(blobsYellow, 2, &removedYellow);
        log(blobsYellow, "object", "good_objectsY");
        blobs = score_by_nx(blobs);
        if (blobs.size() > 0 && blobsYellow.size() >= 2) {
          ctrl_state = ctrl_state_approach_orange_right;
        } else {
          //move_mode = move_mode_target_prime_blob_spin;
        }
      } else if (ctrl_state == ctrl_state_approach_orange_right) {
        if (blobs.size() > 1) {
          blobs = score_by_x(blobs);
        }
        if (blobs.size() > 0) {
          move_mode = move_mode_target_prime_blob_move;
        }
      }
      log(removed, "object", "removed_lower_quality_objects");

      if (blobs.size() > 0) {
        eye_mode = eye_mode_target_prime_blob;
      }
    }

    log(blobs, "object", "good_objects");
    //log(removed, "object", "removed_objects");

    // Action
    Blob const & targetBlob = head(blobs);

    if (eye_mode == eye_mode_normal) {
      eye_pos = 600;
      eye_mode = eye_mode_none;
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
      left_power = right_power = 70;
      left_power += targetBlob.center.x / 5;
      right_power -= targetBlob.center.x / 5;
    } else if (move_mode == move_mode_back_and_to_right) {
      left_power = right_power = -50;
      left_power -= 20;
    } else if (move_mode == move_mode_back_and_to_left) {
      left_power = right_power = -50;
      right_power -= 20;
    }
    move(left_power, right_power);

    log("loop_compute_time", seconds() - loop_start_time);
    if (time_since(start_time) > 10.0) { break; }
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
  if (ctrl_state >= ctrl_state_approach_orange_right && ctrl_state <= ctrl_state_approach_orange_right_max) {
    return true;
  }

  if (ctrl_state == ctrl_state_rotate_to_find_orange_rightB) {
    return true;
  }

  return false;
}

char const * name(e_ctrl_state enu) {
  switch(enu) {
    case ctrl_state_rotate_to_find_orange_right:  return "ctrl_state_rotate_to_find_orange_right"; break;
    case ctrl_state_rotate_to_find_orange_rightB:  return "ctrl_state_rotate_to_find_orange_rightB"; break;
    case ctrl_state_approach_orange_right:     return "ctrl_state_approach_orange_right";     break;
    case ctrl_state_approach_orange_right_max: return "ctrl_state_approach_orange_right_max"; break;
  }

  return "unknown";
}

void log_ctrl_state() {
  log("ctrl_state", ctrl_state, name(ctrl_state));
}

