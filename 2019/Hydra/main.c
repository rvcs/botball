#include <kipr/botball.h>
int rotateTime = 2000;
int rightWheelPercent = 100;
int leftWheelPercent =96;
int i;
int main()
{
    wait_for_light(0);
    shut_down_in (115);
    motor(1,-leftWheelPercent);
    motor(2,-rightWheelPercent);
    msleep(3000);
    motor(1,0);
    motor(2,0);
    msleep(1500);
    motor(1,leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(12050);
    motor(1,-leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(rotateTime/2);
    motor(1,leftWheelPercent);
    motor(2,-rightWheelPercent);
    msleep(rotateTime/1.9);
    motor(1,leftWheelPercent);
    motor(2,rightWheelPercent);
    msleep(1280);
    for(i = 0;i<100;i++){
        motor(1,-leftWheelPercent+4);
        motor(2,rightWheelPercent-(i*2));
        msleep(rotateTime*3);
    };
    return 0;
}
