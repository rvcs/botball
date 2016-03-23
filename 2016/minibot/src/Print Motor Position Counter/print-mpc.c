#include <kipr/botball.h>

int main()
{
  printf("Starting Program\n");
  while(digital(13)==0){ // While the R button is not pressed repeat...
    printf("Press and Hold R to Exit.  MPC 0 = %d\n",gmpc(0));
    msleep(500); // Slow update rate to 2HZ so user can read
  }
  return 0;
}