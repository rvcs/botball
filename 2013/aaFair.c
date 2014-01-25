// Created on Sun June 9 2013
int spin (int left, int right, int angle);
int move (int left, int right, int distance);

int move_motor (int number, int power, int amount_to_move);

int main()
{
	// Start things up
	create_connect ();
	clear_motor_position_counter (0);
	enable_servo (0);
	
	move_motor(0, -900, -1200);

if (0) {
	set_servo_position (0, 1200);
	move_motor(0, -900, -1200);

	move(-300, -400, 200);

	move(-300, -600, 500);

	spin(50, -50, 30);

	set_servo_position (0, 0);
	move_motor(0, 900, 800);
}	
	// Close down
	ao();
	create_disconnect ();
	return 0;
}

/**
 *	move the iCreate, stop at a certain distance moved.
 */
int move(int left, int right, int distance)
{
	int distance0 = 0;
	int loop_done = 0;
	
	distance0 = get_create_distance (.05);
	
	create_drive_direct (left, right);
		
	while (! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.05), loop_done);
		if (abs (distance0 - get_create_distance (.05)) > distance)
		{
			loop_done = 1;
		}
		msleep(50);
	}
}

/**
 *	move the iCreate, stop at a certain angle
 */
int spin (int left, int right,int angle)
{
	int angle0 = 0;
	int loop_done = 0;
	
	angle0 = get_create_total_angle (.05);

	create_drive_direct (left, right);
	
	while (! loop_done)
	{
		printf("a0: %d, a: %d\n", angle0, get_create_total_angle(0.05));
		if (abs ( angle0 - get_create_total_angle (.05)) > angle)
		{
			loop_done = 1;
			create_stop ();
		}
		msleep(50);
	}
}

/** 
 * Move a motor
 * 
 * Used to move the arm up and down
 */
int move_motor (int number, int power, int position)
{
	int loop_done = 0;
	
	move_to_position (number, power, position);
	
	
	while(! loop_done)
	{
		if (get_motor_done (number))
		{
			loop_done = 1;
		}

		msleep(100);
		printf("done: %d %d\n", get_motor_done(number), loop_done);
	}
	printf("moved\n");
}
