#include <kipr/botball.h>
        
int main()
{
    printf("Hello World\n");
  while(digital(1)==0){
    if (analog(1)>1000){
      motor(0,100);
      motor(2,80);
    }
    else {
      motor(0,80);
      motor(2,100);
    }
  }
  ao();
    return 0;
}