// Created on Sat March 7

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0


void go (int left, int right);
void stop ();

int main()
{
	enable_servos();
	printf("Houston we have ignition\n");
	
	set_servo_position(0, 1350);
	set_servo_position(1, 1);
	
	msleep(2000);
	
	go (50,50);
	msleep(1300);

	stop();
	
	set_servo_position(1,600);
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
	set_servo_position(1, 1);
	
	go (-40, -40);
	
	msleep(4000);
	stop();
	
	go (-35, 30);
	
	msleep(1650);
	stop();
	
	go (40, 40);
	
	msleep (1950);
	
	set_servo_position(1, 600);
	
	msleep(800);
	
	go (0, 100);
	msleep (1000);
	stop ();
	
	go(50, 50);
	msleep (2500);
	stop();
	
	go,(0, 50);
	msleep(1000);
	stop();
	
	set_servo_position(1, 1350);
	
	go(0,100);
	msleep(1000);
	stop();
	
	go(100, 100);
	msleep(1500);
	stop();
	
	go(100, 0);
	msleep(1000);
	stop();
	
	set_servo_position(0, 1350);
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
