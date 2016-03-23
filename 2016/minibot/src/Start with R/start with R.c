#include <kipr/botball.h>

int main()
{
  printf("Hello Press R to start\n");
  wait_for_touch(13); // 13 is the cvode for the R button
  printf("I have started\n");
  return 0;
}