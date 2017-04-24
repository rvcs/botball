// Created on Wed March 26 2014

#include <string.h>

#define NUM_TRACKING 4

#define count_of(X) (sizeof(X)/sizeof(X[0]))

#define ORANGE 0
#define YELLOW 1
#define RED 2
#define BLUE 3

int plot(rectangle * prect, char ch);
double seconds();

char message[1025];
char * msg;
int diag()
{
  msg = message + strlen(message);
  return 0;
}

int main(int argc, char *argv[])
{
  int blob_count = 0, i = 0;
  int main_channel = 2; /* red - botguy */
  double time_of_snapshot = 0.0;
  double start = 0.0;

  printf("args: %d\n", argc);
  if (argc > 1)
  {
    if (argv[1][0] == '0') main_channel = 0;
    else if (argv[1][0] == '1') main_channel = 1;
    else if (argv[1][0] == '2') main_channel = 2;
    else if (argv[1][0] == '3') main_channel = 3;
  }
  for (i = 0; i < argc; i++) {
    printf("arg[%d] = %s\n", i, argv[i]);
  }
  printf("\n");
  
  int area[NUM_TRACKING];
  point2 center[NUM_TRACKING];
  rectangle blob[NUM_TRACKING];
  //int area1 = 0, areaX = 0;
  //point2 center;

  init_grid();

  //wait_for_light(0);

  camera_open();
  printf("Num channels: %d", get_channel_count());
  camera_update();
  time_of_snapshot = seconds();
  msleep(300);
  
  start = seconds();
  do {
    // Initialize
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

        //show_xy(center[0].x, center[0].y);
      }

      //printf(" |%3d %4d <-> %4d %3d|  %s\n", delta_left, left, right, delta_right, message);
      printf("%s\n", message);
      message[0] = 0;
      diag();

      show_grid();
    }

    //printf("The time is: %f   %f\n", seconds(), seconds() - start);
  } while (seconds() - start <= 4.0);

  camera_close();

  return 0;
}


#define MAX_WIDTH 160
#define MAX_HEIGHT 120
#define SHOW_WIDTH 64

int show_xy(int x, int y)
{
  static char disp[SHOW_WIDTH + 2];
  int char_pos = (int)((float)x * (float)SHOW_WIDTH / (float)MAX_WIDTH);
  memset(disp, ' ', SHOW_WIDTH + 1);
  disp[SHOW_WIDTH] = '|';
  disp[SHOW_WIDTH + 1] = 0;
  disp[char_pos] = '*';
  sprintf(msg, "%5d %5d %s", x, y, disp);
  diag();

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

