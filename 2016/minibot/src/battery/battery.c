#include <kipr/botball.h>
    
void right_90(int milliseconds);
void drive_the_side(int milliseconds);

int main()
{
    printf("Hello World\n");
  
  double start=seconds();
  mav (0,1000);
  mav(2,1000);
  printf("Wait for touch.\n");
  wait_for_touch (0);
  double time=seconds()-start;
  printf("That took %lf\n",time);
  
  right_90 (1000);
  drive_the_side (time);
  
  ao();
    return 0;
}

void right_90(int milliseconds)
{
  mav(0,500);
  mav(2,-500);
  msleep(milliseconds);

}
void drive_the_side (int milliseconds)
{
  mav(0,500);
  mav(2,500);
  msleep(milliseconds);

}