// Created on Sun February 22 2015

// Motor port numbers
#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0


void go (int left, int right);
void stop ();

int main()
{
	enable_servos ();
	printf("Starting Program\n");
	set_servo_position(0, 1350);
	set_servo_position(1, 600);
	
	msleep(2000);
	
	go (50, 50);
	msleep (5000);
	
	stop ();
	set_servo_position(0, 430);
	
	msleep(2500);
	
	go (70, 40);
	
	msleep(2500);
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
	//at this point, the cubes have been dropped and it's going for the botguy/brick
	go(40, -40);
	
	msleep(3700);
	stop();
	
	go(50, 50);
	
	msleep(3700);
	stop();
	
	set_servo_position(0, 950);
	
	msleep(1000);
	
	set_servo_position(1, 1);
	
	disable_servos ();
	ao ();
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
