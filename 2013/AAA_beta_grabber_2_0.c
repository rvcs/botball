 // Created on Sun March 24 2013

void main ()
{
	int loop_done = 0;
	int task_A_done = 0;
	int task_B_done = 0;
	int angle0 = 0;
	int distance0 = 0;
	
	
	//get_create_total_ angle (.1);
	//create_drive_direct (left speed, right speed)\
	//move_to_position (motor #, motor power(-for backwards), end position)
	//get_motor_done (motor#)
	//clear_motor_position_counter (motor#)
	//msleep (seconds)
		//i'll probably use this often
	create_connect ();
	
	clear_motor_position_counter (0);
	
	enable_servo (0);
	
	//set_servo_position (1800);
	
	// ------------------------------------------------------------------------
	//step:1 aim the arm to knock over the box
	//raise arm
	
	printf("-----Step 1-----\n");
	
	move_to_position (0, -900, -1200);
	
	
	while(! loop_done)
	{
		if (get_motor_done (0))
		{
			loop_done = 1;
		}

		msleep(100);
	}
	
	create_stop ();
	
	loop_done = 0;
	
	// ------------------------------------------------------------------------
	//step:2 knock over box and turn
	//lift arm
	//turn 90
	
	printf("-----Step 2-----\n");
	move_to_position (0, -900, -2000);
	
	angle0 = get_create_total_angle (.1);
	create_drive_direct (150,-150);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.1), task_A_done);
		if (angle0 - get_create_total_angle (.1) < 81)
		{
			create_drive_direct (150,-150);
		}
		else
		{
			task_A_done = 1;
			create_stop ();
		}
		
		if (get_motor_done (0))
		{
			task_B_done = 1;
		}

		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
		msleep(100);
	}
	
	loop_done = 0;
	
	create_stop ();
	
	task_A_done = 0;
	task_B_done = 0;
	
	// ------------------------------------------------------------------------
	//step:3 move some inches forward
	//move forward

	printf("-----Step 3-----\n");
	distance0 = get_create_distance (.1);
	
	create_drive_straight (-150);
	
	while(! loop_done)
	{
		if (get_create_distance (.1) - distance0 < -540)
		{
			
			loop_done = 1;
		}
	}
	
	loop_done = 0;
	
	create_stop ();

	// ------------------------------------------------------------------------
	//step:4 aim claw to point of botguy
	//turn 20
	//lower arm
	
	printf("-----Step 4-----\n");
	move_to_position (0, 400, -50);
	
	angle0 = 0;
	
	angle0 = get_create_total_angle (.1);
	create_drive_direct (120,-120);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.1), task_A_done);
		if (angle0 - get_create_total_angle (.1) < 29)
		{
			create_drive_direct (120,-120);
		}
		else
		{
			task_A_done = 1;
			create_stop ();
			msleep(1000);
		}
		if (get_motor_done (0))
		{
			task_B_done = 1;
			msleep(1000);
		}
		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
		msleep(100);
	}
	
	loop_done = 0;
	
	task_A_done = 0;
	task_B_done = 0;
	
	create_drive_straight (-50);
	
	while (! loop_done)
	{
		if (digital (10))
		{
			create_stop ();
			
			loop_done = 1;
		}
	}
	
	
	
	loop_done = 0;
	
	
	
	// ------------------------------------------------------------------------
	//step:5 grab botguy and lift him up (not complete)
	printf("-----Step 5-----\n");
	
	set_servo_position (0, 1300);
	move_to_position (0, -900, -2000);
	
	// ------------------------------------------------------------------------
	//step:6 move backwards untill the bumper hits the transport (not completed)
	
	printf("-----Step 6-----\n");
	
	create_drive_direct (150, 250);
	
	distance0 = get_create_distance (.1);
	
		
	while (! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.1), loop_done);
		if (get_create_distance (.1) - distance0 > 800)
		{
			loop_done = 1;
		}
	}
	
	loop_done = 0;
	
	printf("-----Step 6-B-----\n");
	
	create_drive_direct (-200, -150);
	
	distance0 = get_create_distance (.1);
	
	while(! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.1), loop_done);
		if (get_create_distance (.1) - distance0 < -200)
		{
			
			loop_done = 1;
		}
	}
	
	loop_done = 0;
	// ------------------------------------------------------------------------
	//step:7 turn clockwise until over transport zone, then drop botguy.
	
	printf("-----Step 7-----\n");
	
	angle0 = 0;
	
	angle0 = get_create_total_angle (.1);
	create_drive_direct (-150,150);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, dA:%d, d: %d\n", angle0, get_create_total_angle (.1), task_A_done);
		if ((angle0 - get_create_total_angle (.1)) < -35)
		{
			create_drive_direct (-150,150);
		}
		else
		{
			create_stop ();
			loop_done = 1;
		}
	}
	
	set_servo_position (0, 200);

	
	create_disconnect ();

}

