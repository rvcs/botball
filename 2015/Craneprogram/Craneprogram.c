// Created on Sat March 7 2015

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0


void go (int left, int right);
void stop ();

int main()
{
	enable_servos();
	printf("Starting Program!\n");
	
	set_servo_position(0, 1350);
	set_servo_position(1, 1);
	
	msleep(2000);
	
	go (50,50);
	msleep(1300);
	
	stop();
	
	set_servo_position(1,600);
	stop();
	msleep(1000);
	// This is the part after it has supopsetly grabed the boxes.
	set_servo_position(0, 491);
	
	go (50,50);
	msleep (4900);
	//It has now  found its way to the mesa.
	
	stop ();
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
	// It should have droped the boxes.
	
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
