// Created on Sat January 17 2015 hi
void drive_forward(int power);
void turn_right(int power);
void driveand_turnright(int power);
int main()
{
	printf("Hello, World!\n");
	msleep(2500);
	printf("jordan\n");
	
	driveand_turnright(80);
	
	driveand_turnright(80);
	
	driveand_turnright(80);
	
	driveand_turnright(80);

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
