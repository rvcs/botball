// Created on Thu March 27 2014

#define NUM_TRACKING 4

#define count_of(X) (sizeof(X)/sizeof(X[0]))

#define ORANGE 0
#define YELLOW 1

#define ARM 0
#define FINGER 1

#define ARM_START 300
#define ARM_LOW 500
#define ARM_TOP_SHELF 1325
#define ARM_TOP_SHELF_PLUS (ARM_TOP_SHELF + 150)
#define ARM_HIGH_FOR_BALANCE 1300

#define FINGER_OPEN 0
#define FINGER_TOUCH 350
#define FINGER_CLOSED 500

#define LEFT 0
#define RIGHT 1

#define GOTO_ORANGE_CUBES1 5
#define ADJUSTER_BREAK 0
#define ADJUSTER_OK 1

#define MAX_WIDTH 160
#define MAX_HEIGHT 120

int hcenter;
int vcenter;

int area[NUM_TRACKING];
point2 center[NUM_TRACKING];
rectangle blob[NUM_TRACKING];
double time_of_snapshot = 0.0;
int main_channel = ORANGE;
int x_accel = 0, y_accel = 0, z_accel = 0;

int plot(rectangle * prect, char ch);
double seconds();

int main()
{
  int i = 0, lmpc = 0, rmpc = 0;
  double start = 0.0;

  hcenter = MAX_WIDTH / 2;
  vcenter = MAX_HEIGHT / 2;

  init_grid();

  camera_open();
  printf("Num channels: %d", get_channel_count());
  camera_update();
  time_of_snapshot = seconds();
  msleep(300);
  
  start = seconds();


  // Start.  Put the servos in the right spot
  disable_servos();
  enable_servo(ARM);
  enable_servo(FINGER);
  servo(ARM, ARM_TOP_SHELF);
  servo(FINGER, FINGER_TOUCH);

  // First, turn right to face the cubes
  //go_until(80, 0, 1500, 0);

  // Move forward toward the cubes
  go_until(80, 80, 0, GOTO_ORANGE_CUBES1);

  // We are lined up with a cube, and are going 20,20
  while (!finger_touch()) {
    lmpc = get_motor_position_counter(LEFT);
    rmpc = get_motor_position_counter(RIGHT);
    x_accel = accel_x();
    y_accel = accel_y();
    z_accel = accel_z();;
    //if (y_accel < -128) {
    //  go(0, 0, 0);
    //  msleep(100);
    //  go(-10, -20, 1);
    //  msleep(1000);
    //  go(20, 20, 1);
    //}

    printf(" XYZ: %4d %4d %4d\n", x_accel, y_accel, z_accel);
    printf("Wait for finger rpc: %d %d\n", lmpc, rmpc);
    show_blobs();
    msleep(10);
  }

  printf("-- Finger Touch --------------------\n");

  // Got finger touch

  // Back up...
  go_until(-10, -10, 200, 0);
  go(0, 0, 0);
  msleep(1300);

  // ... Raise arm a little so we can open the finger
  servo(ARM, ARM_TOP_SHELF_PLUS);
  msleep(1300);
  servo(FINGER, FINGER_OPEN);
  msleep(1300);
  servo(ARM, ARM_TOP_SHELF);
  msleep(1300);

  // ... Then drive forward
  printf("--------------------\n");
  go_until(10, 10, 800, 0);
  go(0, 0, 0);
  msleep(1300);

  // ... Then stop, and grab the cube
  servo(FINGER, FINGER_CLOSED);
  msleep(1300);

  servo(ARM, ARM_HIGH_FOR_BALANCE);
  msleep(1300);

  // Back up a little
  go_until(-10, -10, 300, 0);
  go(0, 0, 0);
  msleep(300);
  
  // Turn towards the goal
  go_until(0, 80, 1500, 0);

  // Sprint there
  go_until(95, 95, 20000, 0);
  go(0, 0, 0);

  servo(ARM, ARM_LOW);
  msleep(300);
  servo(FINGER, FINGER_OPEN);
  msleep(4000);


	return 0;
}

int show_blobs()
{
  int blob_count = 0, i = 0;

  if (seconds() - time_of_snapshot < 0.3) {
    return 0;
  }

  clear_grid();
  camera_update();
  time_of_snapshot = seconds();
  blob_count = get_object_count(main_channel);
  printf("#:%-2d ", blob_count);
  if (blob_count > count_of(area)) {
    blob_count = count_of(area);
  }

  if (blob_count > 0) {
    for (i = 0; i < blob_count; ++i) {
      area[i]   = get_object_area(main_channel, i);
      center[i] = get_object_center(main_channel, i);
      blob[i] = get_object_bbox(main_channel, i);
      plot(&blob[i], i + '0');
    }
  }

  show_grid();
}

int have_seen_orange_cube1 = 0;
int have_seen_orange_cube_very_high = 0;
int goc_counter = 0;
int goto_orange_cubes1(int left, int right, int distance, int lmpc, int rmpc)
{
  int i = 0, blob_count = 0;
  int area0 = 0;
  int right_most_index = 0;
  rectangle * ptarget = 0;
  point2 target_center;
  float speed_factor = 1.0;
  float ar = 0;

  if (finger_touch()) {
    printf("Finger Touch detected in goto_orange_cubes1\n");
    return ADJUSTER_BREAK;
  }

  //if (have_seen_orange_cube_very_high == 1) {
    //return ADJUSTER_OK;
  //}

  memset(center, 0, sizeof(center));
  memset(area, 0, sizeof(area));
  clear_grid();

  // Begin

  // Do not do anything with the camera until enough time has passed
  if (seconds() - time_of_snapshot >= 0.1) {
    camera_update();
    time_of_snapshot = seconds();
    blob_count = get_object_count(main_channel);
    //sprintf(msg, "#:%2d", blob_count); diag();
    printf("#:%-2d ", blob_count);
    if (blob_count > count_of(area)) {
      blob_count = count_of(area);
    }

    if (blob_count > 8) {
      return ADJUSTER_OK;
    }

    if (blob_count > 0) {
      for (i = 0; i < blob_count; ++i) {
        area[i]   = get_object_area(main_channel, i);
        center[i] = get_object_center(main_channel, i);
        blob[i] = get_object_bbox(main_channel, i);
        plot(&blob[i], i + '0');
      }

      for (i = 0; i < blob_count; ++i) {
        printf(" %3d", blob[i].width * blob[i].height);
      }

      for (; i < count_of(blob); ++i) {
        printf("    ");
      }

      printf("        ");
      for (i = 0; i < blob_count; ++i) {
        printf(" %2dx%2d", blob[i].width, blob[i].height);
      }

      if (have_seen_orange_cube_very_high != 1) {
        // Look for the right-most cube.  The way the claw works, we need to
        //   grap the right one first

        area0 = area[0];
        for (i = 0; i < blob_count; ++i) {
          // Is it big enough?
          if (area[i] < 0.45 * area0) {
            printf("Rejecting -- too small %d\n", i);
            continue;
          }
          // Is it above the center?
          if (center[i].y > vcenter) {
            printf("Rejecting -- too low %d\n", i);
            continue;
          }
          // Is it roughly square?
          ar = (float)blob[i].width / (float)blob[i].height;
          if (ar > 2.0 || ar < 0.5) {
            printf("Rejecting -- not square enough %d\n", i);
            continue;
          }

          if (center[i].x > center[right_most_index].x || ptarget == 0) {
            right_most_index = i;
            ptarget = &blob[right_most_index];
          }
        }
      } else {
        // We have seen an orange cube high in the camera.  At this point, 
        // we are going for that one, so don't change direction.
        go(20, 20, 1);
        return ADJUSTER_BREAK;
      }

      if (ptarget) {
        // We've seen something
        if (have_seen_orange_cube1 == 0) {
          printf("have_seen_orange_cube1 %d\n", goc_counter);
          if (++goc_counter > 3) {
            have_seen_orange_cube1 = 1;
            goc_counter = 0;
          } 
        }

        target_center = center[right_most_index];
        plot(ptarget, '*');

        // Found a target object... need to put it in center, and watch it go up
        if (target_center.y < MAX_HEIGHT * 0.2) {
          // Slow down
          speed_factor = 0.5;

          if (target_center.y < MAX_HEIGHT * 0.12) {
            if (have_seen_orange_cube_very_high == 0) {
              printf("have_seen_orange_cube_very_high  %d\n", goc_counter);
              if (++goc_counter > 3) {
                have_seen_orange_cube_very_high = 1;
                goc_counter = 0;
                //go(0, 0, 0);
                //return ADJUSTER_OK;
              }
            }
          }
        }

        if (target_center.x < hcenter * 0.9) {
          // Slow left wheel
          printf("goc1 - %f %f\n", speed_factor * left/2, speed_factor * right);
          go((int)(speed_factor * left/2), (int)(speed_factor * right), 0);
        } else if (target_center.x > hcenter * 1.1) {
          // Slow right wheel
          printf("goc1 - %f %f\n", speed_factor * left, speed_factor * right/2);
          go((int)(speed_factor * left), (int)(speed_factor * right/2), 0);
        } else {
          // In the center!  Back to full speed
          printf("goc1 - %f %f\n", speed_factor * left, speed_factor * right);
          go((int)(speed_factor * left), (int)(speed_factor * right), 0);
        }
      }

    }

    show_grid();
  }
  printf("goto_orange rpc: %d %d\n", lmpc, rmpc);
}

int go_until(int left, int right, int distance, int which_driver)
{
  int lmpc = 0, rmpc = 0;

  go(left, right, 1);
  while (1) {
    lmpc = get_motor_position_counter(LEFT);
    rmpc = get_motor_position_counter(RIGHT);

    if (which_driver == GOTO_ORANGE_CUBES1) {
      if (goto_orange_cubes1(left, right, distance, lmpc, rmpc) == ADJUSTER_BREAK) {
        break;
      }
    } else {
      printf("rpc: %d %d\n", lmpc, rmpc);
      if (abs(lmpc) + abs(rmpc) > abs(distance)) {
        break;
      }
    }

    msleep(10);
  }
}

int go(int left, int right, int clear_counters)
{
  if (clear_counters) {
    clear_motor_position_counter(LEFT);
    clear_motor_position_counter(RIGHT);
  }

  motor(LEFT, left);
  motor(RIGHT, right);
}

int finger_touch()
{
  return digital(8) != 0 || digital(9) != 0 || digital(10) != 0;
}

int camera_adjuster(int left, int right, int distance, int lmpc, int rmpc)
{
}

int abs(int x)
{
  if (x >= 0) {
    return x;
  }
  return -x;
}

int s_pos[4] = {300, FINGER_OPEN, 0, 0};

int servo(int s, int pos)
{
  int delta = 100;

  set_servo_position(s, s_pos[s] = pos);
  return 0;
  if (pos < s_pos[s]) {
    for (; s_pos[s] > pos; s_pos[s] -= delta) {
      set_servo_position(s, s_pos[s]);
      msleep(10);
      printf("pos: %d\n", get_servo_position(s));
    }
  }
  else {
    for (; s_pos[s] < pos; s_pos[s] += delta) {
      set_servo_position(s, s_pos[s]);
      msleep(10);
      printf("pos: %d\n", get_servo_position(s));
    }
  }

  set_servo_position(s, s_pos[s] = pos);
  printf("pos: %d\n", get_servo_position(s));
  return 0;
}

#define GRID_MAX_WIDTH 160
#define GRID_MAX_HEIGHT 60

char * grid[GRID_MAX_HEIGHT + 2];
float grid_width_multiple = 1.0;
float grid_height_multiple = 1.0;

int init_grid()
{
  grid_width_multiple = (float)GRID_MAX_WIDTH / (float)MAX_WIDTH;
  grid_height_multiple = (float)GRID_MAX_HEIGHT / (float)MAX_HEIGHT;

  printf("Grid scale: %f x %f\n", grid_width_multiple, grid_height_multiple);

  int i = 0;
  for (i = 0; i < count_of(grid); ++i) {
    grid[i] = (char*)malloc((size_t)(sizeof(char) * (3+GRID_MAX_WIDTH)));
    memset(grid[i], ' ', sizeof(char) * (2+GRID_MAX_WIDTH));
    grid[i][GRID_MAX_WIDTH] = 0;
  }
}

int clear_grid()
{
  int i = 0;
  for (i = 0; i < count_of(grid); ++i) {
    memset(grid[i], ' ', GRID_MAX_WIDTH * sizeof(char));
    //grid[i][GRID_MAX_WIDTH] = 0;
  }

  // Put a ruler across the middle
  memset(grid[GRID_MAX_HEIGHT/2], '-', GRID_MAX_WIDTH * sizeof(char));

  // Show the width and a vertical ruler across the middle
  for (i = 0; i < GRID_MAX_HEIGHT; ++i) {
    grid[i][GRID_MAX_WIDTH/2] = '|';
    grid[i][GRID_MAX_WIDTH] = '|';
  }
}

int plot(rectangle * prect, char ch)
{
  int x = 0, ix = 0, y = 0, iy = 0;
  rectangle r;

  r.ulx = prect->ulx * grid_width_multiple;
  r.uly = prect->uly * grid_height_multiple;
  r.width = prect->width * grid_width_multiple;
  r.height = prect->height * grid_height_multiple;

  printf("%d,%d:%dx%d\n", r.ulx, r.uly, r.width, r.height);
  //return 0;
  for(y = r.uly, iy = 0; iy < r.height; ++iy, ++y) {
    for(x = r.ulx, ix = 0; ix < r.width; ++ix, ++x) {
      if (x > 0 && x < GRID_MAX_WIDTH && y > 0 && y < GRID_MAX_HEIGHT) {
        grid[y][x] = ch;
      }
    }
  }
}

int show_grid()
{
  int y = 0;
  //return 0;

  for(y = 0; y < GRID_MAX_HEIGHT; ++y) {
    printf("%s\n", grid[y]);
  }
}

