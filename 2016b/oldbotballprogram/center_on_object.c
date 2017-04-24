#define OUTSIDE 1
#define INSIDE 0
#define LIGHT 600
#define DARK 600
#define LEFT_MOTOR 3
#define RIGHT_MOTOR 1
#define SENSOR_SLEEP 10
#include <stdio.h>

int analog10(int);
int motor(int, int);
int msleep(int);
 
int main()
{
  int left_speed = 0, right_speed = 0;
  int left, right;

  for (;;) {
    /* Initialize loop */
    left = analog10(0);
    right = analog10(1);

    if (left > DARK && right > DARK) {
      left_speed = 60, right_speed = 90;
    }

    /* Set the motor speeds */
    printf("%4d %4d\n", left, right);
    motor(LEFT_MOTOR, left_speed);
    motor(RIGHT_MOTOR, right_speed);
    msleep(10);
  }
}

