#include <kipr/botball.h>

int main()
{
   create_connect();
   //wait_for_light(0);
   shut_down_in(119);
    
    //code
    create_drive_direct(-150,150);
    msleep(2000);
    create_drive_direct(-150, -150);
    msleep(5000);
    create_drive_direct(150,-150);a
    msleep(1975);
    create_drive_direct(-150,-150);
    msleep(8000);
    create_drive_direct(150,-150);
    msleep(2000);
    create_drive_direct(-100,-100);
    msleep(3500);
    
    
   create_disconnect();
   return 0;
}

