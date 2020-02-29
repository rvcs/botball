#include <kipr/botball.h>
void go(int left_motor, int right_motor, int durration)
{
mav(0, right_motor);
mav(1, left_motor);
    msleep(durration);
}
int main()
{
    go(1300, 1500, 5000);
    printf("Hello World\n");
    return 0;
}

