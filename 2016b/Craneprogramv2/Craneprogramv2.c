// Created on Sat March 7

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0


void go (int left, int right);
void stop ();

int main()
{
	enable_servos();
	printf("Houston we have ignition\n");
	
	set_servo_position(0, 950);
	set_servo_position(1, 60);
	
	msleep (1000);
	
	while (analog(0) > 700 && a_button() == 0)
		{
			msleep(10);
		}
		shut_down_in(118.0);
	
	msleep(2000);
	
	go(40, 0);
	msleep(3000);
	stop();
		
	set_servo_position(0, 1350);
	msleep(1000);
	set_servo_position(1, 1400);
	msleep(1000);
		
	set_servo_position(0,600);
	stop();
	msleep(1000);
	
	go (50,50);
	msleep (4900);
	
	stop ();
	set_servo_position(0, 498);
	msleep(2500);
	
	go (70, 40);
	
	msleep(2600);
	stop ();
	
	go (35, -30);
	
	msleep(1000);
	
	go (15, 15);
	
	msleep(1500);
	
	stop ();
	set_servo_position(1, 600);
	
	go (-40, -40);
	
	msleep(4000);
	stop();
	
	go (-35, 30);
	
	msleep(1650);
	stop();
	
	go (40, 40);
	
	msleep (1950);
	
	set_servo_position(1, 600);
	
	return 0;
}

void go (int left, int right)
{
	printf("GO   %d %d\n", left, right);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
}
void stop ()
{
	go (0,0);
}
