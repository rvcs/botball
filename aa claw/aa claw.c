
// Created on Sat March 
// Claw is servo 1 
// the arm is servo 0

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0


void go (int left, int right);
void stop ();

int main()
{
//	enable_servos();
	enable_servo(0);
	enable_servo(1);
	printf("Houston we have ignition\n");
	
	set_servo_position(0, 1050);
	set_servo_position(1, 60);
	
	msleep (1000);
	
	//wait_for_light(0); 

	shut_down_in(119); 
	
	msleep(12000);
	//8 second delay after the lights to turn on to wait until the bots get out of the way
	go(41, 41);
	msleep(700);
	stop();
		
	set_servo_position(0, 1350);
	msleep(1000);
	set_servo_position(1, 1600);
	msleep(1000);
	//grabs cubes
	set_servo_position(0, 450);
	stop();
	msleep(1000);
	
	go (54,50);
	msleep (5000);
	
	stop ();
	
	go (60, 35);
	
	msleep(1900);
	stop ();
	
	go (35, -30);
	
	msleep(800);
	
	go (30, 30);
	msleep(750);
	stop();
	
	stop ();
	msleep(1000);
	enable_servo(1);
	set_servo_position(1, 600);
	//drops cubes
	go (-40, -47);
	
	msleep(1200);
	stop();
	//starts going for cube/botguy
	go (-20, 20);
	msleep(2900);
	stop();
	set_servo_position(0, 370);

	go (-20, -25);
	msleep(4000);
	stop();
	
	go (20, 25);
	msleep(5000);
	stop();
	
	go (20, -20);
	msleep(1500);
	stop();
	
	go (20, 25);
	msleep(1900);
	stop();
	
	set_servo_position(1, 1650);
	msleep(500);
	
	go (-30, -50);
	
	msleep(8500);
	stop();
	//backs up into the starting zone
	go (30, -30);
	msleep(900);
	stop();
	set_servo_position(0, 1000);
	
	msleep(500);
	stop();
	set_servo_position(1, 300);
	msleep(1200);
	//dunks botgal on the scoring zone 
	return 0;
}

void go (int left, int right)
{
	printf("GO   %d %d\n", left, right);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, (int)((double)right * 1.17));
}
void stop ()
{
	go (0,0);
}
