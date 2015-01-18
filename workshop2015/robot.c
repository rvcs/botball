// Created on Sat January 17 2015 hi
void drive_forward(int power);
void turn_right(int power);
void driveand_turnright(int power);
int main()
{
	printf("Hello, World!3\n");
	while (digital(8) !=1)
	{
		printf("%d\n", analog_et(5));
		if (analog_et(5)<350)
		{
			drive_forward(100);
		}
		else if(analog_et(5)>450)
		{
			drive_forward(-99);
		}
		else
		{
		}
	}
	ao();
	return 0;
}
//end of main function
void driveand_turnright(int power)
{
	drive_forward(power);
	turn_right(power);
}
void drive_forward(int power)
{
	// make the robot move for two seconds or something like that
	motor(0, power);
	motor(3, power);	
}
void turn_right(int power)
{
		// make the robot move for two seconds or something like that
	motor(0, power);
	motor(3, 0);
	msleep(2000);
}
