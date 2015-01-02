// minib Created on Sat June 21 2014

// Motor port numbers
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 0

#define ARM_SERVO 0

#define ARM_UP 1153
#define ARM_DOWN 622

void go (int left, int right);
void stop ();

int main()
{
	printf("Mini Bot!\n");
	enable_servos();
	set_servo_position(ARM_SERVO, ARM_UP);

	printf("Waiting for light!\n");
	while (analog(0) > 700 && a_button() == 0)
	{
		msleep(10);
	}
	shut_down_in(118.0);
	
	msleep (25000);
	
	go(90, 90);
	msleep(6700);
	stop();
	
	
	
	msleep(100);
	printf("stopped\n");
	set_servo_position(ARM_SERVO, ARM_DOWN);
	
	printf("arm down\n");
	
	
	go(-80,-80);
	msleep(500);
	stop();
	
	go(-90, 90);
	msleep(1150);
	stop();
	
	go(90, 90);
	msleep(2500);
	stop();
	set_servo_position(ARM_SERVO, ARM_UP);
	
	
	go(90, 90);
	msleep(2500);
	stop();
	
    msleep(1000000);
	return 0;
}

void go (int left, int right)
{
	printf("GO                                                       %d %d\n", left, right);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
}

void stop ()
{
	go (0,0);
}
