// Created on Sat January 17 2015 hi
void drive_forward(int power);
void turn_right(int power);
void driveand_turnright(int power);
int main()
{
	printf("Hello, World!3\n");
	while (digital(8) !=1)
	{
		printf("%d\n", analog(1));
		if (analog(1)>600)
		{
			motor(0,10);
			motor(3,100);
		}
		else
		{
			motor(0,100);
			motor(3,10);
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
	msleep(2000);	
}
void turn_right(int power)
{
		// make the robot move for two seconds or something like that
	motor(0, power);
	motor(3, 0);
	msleep(2000);
}
