#include <kipr/botball.h>

#define MOVE_DELTA 200

int main()
{
  printf("connecting to Create\n");
  create_connect();
  double startTime = seconds(), dtime = 0.0;

  int x = 0/*, y = 0*/;
  camera_open();        // activate camera

  set_create_distance(0); // reset the cumulative distance traveled
  set_create_total_angle(0); // reset the cumulative angle turned through
  create_drive_direct(100, -100); // start move in an arc

  int dda = 0, ddb = 0;
  for (;(seconds() - startTime) < 34.5;) {
    dda = 0; ddb = 0;
    camera_update();      // get most recent camera image and process it
    dtime = seconds() - startTime;
    printf("t: %lf", dtime);
    if (get_object_count(0) > 0 && get_object_area(0,0) > 90) { // there is a blob
      x = get_object_center(0,0).x;  // get image center x data
      //      y = get_object_center(0,0).y;  //    and y data
      printf(", x: %d, a: %d", x, get_object_area(0,0));
      if (x > 90) {
        dda += MOVE_DELTA; ddb += -MOVE_DELTA;
        //create_drive_direct(50, -50); // start move in an arc
      } else if (x < 70) {
        dda += -MOVE_DELTA; ddb += MOVE_DELTA;
        //create_drive_direct(-50, 50); // start move in an arc
      }
      
      if (get_object_area(0,0) < 400) {
        dda += -MOVE_DELTA; ddb += -MOVE_DELTA;
      }
    } else {
      dda = 0; ddb = 0;
      //create_drive_direct(10, -10); // start move in an arc
    }
    create_drive_direct(dda, ddb); // start move in an arc
    printf(" dda: %d, ddb: %d\n", dda, ddb);
    msleep(1);
  }

  create_stop();

  printf("\nResults:\n");
  printf("  distance = %d mm\n", get_create_distance(0.1));
  printf("  angle = %d degrees\n", get_create_total_angle(0.1));
  printf("\ndisconnecting from Create\n");
  camera_close();
  create_disconnect();

  return 0;
}

