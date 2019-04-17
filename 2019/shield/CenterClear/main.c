#include <kipr/botball.h>

int main()
{
   create_connect();
   wait_for_light(0);
   shut_down_in(119);
    
    //code
    msleep(1000);
    create_drive_direct(-150,150);
    msleep(1900);
    create_drive_direct(-150, -150);
    msleep(4500);
    create_drive_direct(150,-150);
    msleep(1900);
    create_drive_direct(-150,-150);
    msleep(7500);
    create_drive_direct(-25,-150);
    msleep(6000);
    create_drive_direct(-100,-100);
    msleep(2000);
    
    
   create_disconnect();
   return 0;
}

