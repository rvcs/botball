#include <kipr/botball.h>
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 2
#define ARM_HALF 1308
#define CLAW_START 216
int left_is_black()
{
  return analog(1) <500; //changed from >500
}

int right_is_black()
{
  return analog(3) <500; //changed from >500
}

int left_is_white()
{
  return analog(1) >500; //changed from <500
}

int right_is_white()
{
  return analog(3) >500; //changed from <500
}

int on_ramp()
{
  return accel_x() > 150;
}

int wheelie_on_ramp()
{
  return accel_x() > 450;
}

int main()
{
  //left wheel is: 2
  //right wheel is: 0

  //important for line follow
    double start = 0.0;
   int a1;
  int a2;
  float factor=0.55;

  // starting the robot
    printf("Hello World\n");
  enable_servos ();
    set_servo_position(2, ARM_HALF);
    set_servo_position(3, CLAW_START);
  //finding out if the "1" is left or right
  mav(0,800); //500 on 4/23
  mav(2,800);
  msleep (3000);

  //linefollow:
  //add in the line follow later, after we know wht wheel is what
  //dont forget the info at the beginning of the program
  //using the line follow from: CLOSE RAMP

  start=seconds ();
  while(1){
    a1 =analog (1);
    a2 =analog (3);
    //printf("cave%5d %5d %5d ",a1,a2, accel_x());
    printf("%6s %5d %d%d %6s", right_is_black()?"XXXXXX":"", accel_x(), on_ramp(), wheelie_on_ramp(), left_is_black()?"XXXXXX":"");
    if(seconds()-start>15){ //8.5 on 4/23
              //used to be 4.5 2/3/16 //was14 (keep comment)
      break;
    }

    if ((left_is_white() && right_is_white()) || (left_is_black() && right_is_black())) {
              //a1=500 both // was if ((a1<400 && a2<500) || (a1>700 && a2>500)) (keep comment)
      mav(LEFT_MOTOR,1500 * factor);
              //was 0,90 2/3/16 //was900 (keep comment)
      mav(RIGHT_MOTOR,1500 * factor);
              //was 2,56 2/3/16 (keep comment)
      printf("straight\n");
    } else if (left_is_black()) {
              //was else if (a1<500) 2/17/16 (keep comment)
        // Turn left (keep comment)
      mav(LEFT_MOTOR,500 * factor);
              //left is 0 right is 2 (keep comment) if facing robot
      mav(RIGHT_MOTOR,900 * factor);
      printf("left\n");
    } else if (right_is_black()) {
              //was just "}else {" (keep comment)
        //turn right (keep comment)
      mav(LEFT_MOTOR,900 * factor);
      mav(RIGHT_MOTOR,500 * factor); //750
      printf("right\n");
        }
    }
    ao();
    return 0;
}


