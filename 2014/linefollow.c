#define OUTSIDE 1
#define INSIDE 0
#define LIGHT 600
#define DARK 600
#define LEFT_MOTOR 3
#define RIGHT_MOTOR 1
#define SENSOR_SLEEP 10
#include <stdio.h>
 
int position;
int within = 2;
int start = 1;
int line_follow(void);
 
int main()
{
        line_follow();
}
 
line_follow(void)
{
        while(start == 1) { //go forward till black line is seen
                motor(LEFT_MOTOR,100);
                motor(RIGHT_MOTOR,100);
                //printf("a\n");
                if(analog10(0) > DARK || analog10(1) > DARK) {
                        start = 0;
                        ao();
                }
        }       //does not enter this while loop again
        while(1) {
       
                while(analog10(0) > DARK && analog10(1) < LIGHT) { //
                        motor(LEFT_MOTOR,60);
                        motor(RIGHT_MOTOR,90);
                        position = OUTSIDE;
                        //printf("b\n");
                        within = 0;
                        msleep(SENSOR_SLEEP);
                }
                while(analog10(0) < LIGHT && analog10(1) > DARK) {
                        motor(LEFT_MOTOR,90);
                        motor(RIGHT_MOTOR,60);
                        position = INSIDE;
                        //printf("c\n");
                        within = 0;
                        msleep(SENSOR_SLEEP);
                }
                while(analog10(0) > DARK && analog10(1) > DARK) { //while on line
                        if(position == INSIDE && (within == 0 || within == 1)) { //if last recorded location
                                motor(LEFT_MOTOR,90);
                                motor(RIGHT_MOTOR,60);
                                //printf("d\n");
                                within = 1;
                                msleep(SENSOR_SLEEP);  
                        }
                        if(position == OUTSIDE && (within == 0 || within == 1)) {
                                motor(LEFT_MOTOR,60);
                                motor(RIGHT_MOTOR,90);
                                //printf("e\n");
                                within = 1;
                                msleep(SENSOR_SLEEP);
                        }
                        if(within == 2) {
                                motor(LEFT_MOTOR,-10);
                                motor(RIGHT_MOTOR,50);
                                //printf("f\n");
                                within = 1;
                                msleep(SENSOR_SLEEP);
                        }
                }
                while(analog10(0) < LIGHT && analog10(1) < LIGHT) {
                        if(within == 1 && position == INSIDE) {
                                motor(LEFT_MOTOR,50);
                                motor(RIGHT_MOTOR,0);
                                //printf("g\n");
                                //camera_update();
                                msleep(SENSOR_SLEEP);
                        }      
                        if(within == 0 && position == INSIDE) {
                                motor(LEFT_MOTOR,0);
                                motor(RIGHT_MOTOR,50);
                                //printf("h\n");
                                msleep(SENSOR_SLEEP);
                        }
                        if(within == 1 && position == OUTSIDE) {
                                motor(LEFT_MOTOR,0);
                                motor(RIGHT_MOTOR,50);
                                //printf("i\n");
                                msleep(SENSOR_SLEEP);
                        }
                        if(within == 0 && position == OUTSIDE) {
                                motor(LEFT_MOTOR,50);
                                motor(RIGHT_MOTOR,0);
                                //printf("j\n");
                                msleep(SENSOR_SLEEP);
                        }
                }
        }
}
