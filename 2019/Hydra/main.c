#include <kipr/botball.h>
int rotateTime = 2000;
int rightWheelPercent = 100;
int leftWheelPercent =97;
int i;
int main()
{
    enable_servos();
    set_servo_position(0,1468);
    set_servo_position(1,1400);
    set_servo_position(2,2047);
    shut_down_in(180);
    motor(1,leftWheelPercent);
    motor(0,rightWheelPercent);
    msleep(3000);           
    motor(1,-leftWheelPercent);
    motor(0,rightWheelPercent);
    msleep(rotateTime);
    motor(1,leftWheelPercent);
    motor(0,rightWheelPercent);
    msleep(6000);
    motor(0,-rightWheelPercent);
    msleep(rotateTime/4);
    motor(0,rightWheelPercent);
    msleep(2000);
    motor(1,-leftWheelPercent);
    msleep(rotateTime/4);
    motor(1,leftWheelPercent);
    msleep(4300);
    motor(0,0);
    motor(1,0);
    msleep(10);
    motor(1,leftWheelPercent);
    motor(0,-rightWheelPercent);
    msleep(rotateTime/8);
    motor(1,leftWheelPercent);
    motor(0,rightWheelPercent);
    msleep(250);
   	motor(0,rightWheelPercent);
    motor(1,-leftWheelPercent);
    msleep(rotateTime*10);
    return 0;
}

