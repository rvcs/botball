// Created on Sat March 23 2013
int turn_right(double seconds);
int main()
{
	int distance = 0;
	
	printf("starting connor\n");
	enable_servo(1);
	set_servo_position(1,100);
	create_connect(); 
	// opens claw
	while (! digital(11))
	{
		printf("%d\n",  digital(11));
		create_drive_direct(-150,-150);
	}
	printf("starting connor\n");
	//move forward and say the "quote" when the claw touches something
	set_servo_position(1,1400);
	while (get_create_lbump() == 0 && get_create_rbump() == 0)
		{
		create_drive_direct(150, 150);
		}
	//grab object and back up
	turn_right(250);
	move_relative_position (1, 900, 360*3);
	msleep(1000);
	//turn right and move arm up
	distance = get_create_distance (0.0);
	while (distance - get_create_distance (0.0) < 500)
		{
		create_drive_direct(-150, -150);
		}
	//move forward for (distance < 600)
	set_servo_position (1,100);
	//drop object
	disable_servos();
}


int turn_right(double seconds) 
	{
	int initial_angle = get_create_total_angle(0);
	create_drive_direct(300,-300);
	msleep(seconds*1);
	create_stop();
	return(get_create_total_angle(0) - initial_angle);
	}
