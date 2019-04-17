#include <kipr/botball.h>
int rotateTime = 2050;
int rightWheelPercent = 100;
int leftWheelPercent =97;
int i;
int main()
{
   
    shut_down_in(180);
    motor(1,leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(3000);           
    motor(1,-leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(rotateTime);
    motor(1,leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(6000);
    motor(2,-rightWheelPercent);
    msleep(rotateTime/4);
    motor(2,rightWheelPercent);
    msleep(500);
    motor(1,-leftWheelPercent);
    msleep(rotateTime/4);
    motor(1,leftWheelPercent);
    msleep(6500);
   	motor(2,rightWheelPercent);
    motor(1,-leftWheelPercent);
    msleep(rotateTime*10);
    return 0;
}
