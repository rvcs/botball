 // Created on Sun March 24 2013

void main (int argc, char ** argv)
{
	int loop_done = 0;
	int task_A_done = 0;
	int task_B_done = 0;
	int angle0 = 0;
	int distance0 = 0;
	
//	float lf_args[20];
	
	// read inputs
//	printf("Args: %d\n", argc);
//	for (i = 2; i < argc; i++)
//	{
//		scanf("%lf%, argv[i]
//	}
	
	
	
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
	
	set_servo_position (0 ,1300);
	
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
	
	angle0 = get_create_total_angle (.05);
	create_drive_direct (150,-150);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.05), task_A_done);
		if (angle0 - get_create_total_angle (.05) < 50)
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
	distance0 = get_create_distance (.05);
	
	create_drive_direct (-150, -200);
	
	while(! loop_done)
	{
		if (get_create_distance (.05) - distance0 < -600)
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
	move_to_position (0, 400, -900);
	
	angle0 = 0;
	
	angle0 = get_create_total_angle (.05);
	create_drive_direct (120,-140);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.05), task_A_done);
		if (angle0 - get_create_total_angle (.05) < 38)
		{
			create_drive_direct (120,-140);
		}
		else
		{
			task_A_done = 1;
			create_stop ();
			msleep(50);
		}
		if (get_motor_done (0))
		{
			task_B_done = 1;
			msleep(50);
		}
		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
		msleep(50);
	}
	
	set_servo_position (0 ,600);
	
	loop_done = 0;
	
	task_A_done = 0;
	task_B_done = 0;
	
	create_drive_straight (50);
	move_to_position (0, 400, -350);
	
	while (! get_motor_done (0))
	{
		msleep (50);
	}
	
	create_drive_straight (-50);
	
	msleep (2500);
	
	//while (! loop_done)
	if (0)
	{
		if (digital (10))
		{
			create_stop ();
			
			loop_done = 1;
		}
		if (get_create_distance (.05) - distance0 < -100)
		{
			create_stop ();
			
			loop_done = 1;
		}
	}
	
	
	
	loop_done = 0;
	
	
	
	// ------------------------------------------------------------------------
	//step:5 grab botguy and lift him up (not complete)
	printf("-----Step 5-----\n");
	
	create_drive_direct (90, -90);
	
	while(angle0 - get_create_total_angle (.05) < 10)
	{
		msleep(50);
	}
	
	create_stop ();
	
	set_servo_position (0, 1300);
	move_to_position (0, -900, -2000);
	
	
	
	// ------------------------------------------------------------------------
	//step:6 move backwards untill the bumper hits the transport (not completed)
	
	printf("-----Step 6-----\n");
	
	create_drive_direct (150, 300);
	
	distance0 = get_create_distance (.05);
	
		
	while (! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.05), loop_done);
		if (get_create_lbump() == 1 || get_create_rbump() == 1)
		{
			loop_done = 1;
		}
	}
	
	loop_done = 0;
	
	printf("-----Step 6-B-----\n");
	
	create_drive_direct (-400, -150);
	
	distance0 = get_create_distance (.05);
	
	while(! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.05), loop_done);
		if (get_create_distance (.05) - distance0 < -100)
		{
			
			loop_done = 1;
			
			create_stop ();
		}
	}
	
	loop_done = 0;
	// ------------------------------------------------------------------------
	//step:7 drop botguy.
	
	printf("-----Step 7-----\n");
	
	move_to_position (0, -900, -300);
	
	msleep (1000);
	
	set_servo_position (0, 200);
	
	
	create_disconnect ();

}


