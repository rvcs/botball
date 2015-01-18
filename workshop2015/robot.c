// Created on Sat January 17 2015 hi
void drive_forward(int power);
void turn_right(int power);
void driveand_turnright(int power);
int main()
{
	camera_open();
	printf("Hello, World!5 %d\n", digital(8));
	while (digital(8) !=1)
	{
		printf("D8-- %d\n", digital(8));
		camera_update();
		printf("c: %d\n",get_object_count(0));
		
		if (get_object_count(0)==0)
		{
			ao();
		}
		else if(get_object_center_x(0,0)<80)
		{
			motor(0, -50);
			printf("%d\n",get_object_center_x(0,0));
			motor(3, 50);
		}
		else
		{
			motor(0, 50);
			printf("%d\n",get_object_center_x(0,0));
			motor(3, -50);
		}
	}
	printf("Done\n");
	ao();
	camera_close();
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
