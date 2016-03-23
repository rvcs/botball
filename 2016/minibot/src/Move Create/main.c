#include <kipr/botball.h>

int main()
{
  printf("Hello Create\n");
  printf("press R button to start\n");
  while(digital(13) ==0){
    msleep(20);
  }
  printf("Connecting\n");
  create_connect(); // this engages the create
  while(get_create_lbump()==0 && get_create_rbump()==0){
    create_drive_direct(100,-100);
  }
  create_stop();
  create_disconnect();
  msleep(500);
  return 0;
}