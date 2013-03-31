// Created on Sat March 16 2013

int main()
{
	int delay=10;
	int i=0;
	enable_servo(2); 
	printf("%d enabled\n",get_motor_enabled(0));
	printf("%d enabled\n",get_motor_enabled(1));
	printf("%d enabled\n",get_motor_enabled(2));
	printf("%d enabled\n",get_motor_enabled(3));
	
	set_servo_position(2,100); 
	for(i=0;i<200;i++)
	{
		printf("%d position %d\n",get_motor_position(2), i); 
		msleep(delay);
	}
	msleep(1500);
	
	set_servo_position(2,1500); 
	printf("%d position\n",get_motor_position(2)); 
	msleep(1500); 
	
}
