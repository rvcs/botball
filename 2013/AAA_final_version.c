 // Created on Sun March 24 2013

void main (int argc, char ** argv)
{
	int loop_done = 0;
	int task_A_done = 0;
	int task_B_done = 0;
	int angle = 0;
	int dangle = 0;
	int angle0 = 0;
	int distance0 = 0;
	int distance = 0 ;
	int ddistance = 0;
	
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
	
	//tip the square over
	
	angle0 = get_create_total_angle (.05);
	create_drive_direct (50,-50);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.05), task_A_done);
		if (angle0 - get_create_total_angle (.05) >= 10)
		{
			loop_done = 1;
			create_stop ();
		}
		msleep(1500);
	}
	
	loop_done = 0;
	
	create_stop ();
	
	task_A_done = 0;
	task_B_done = 0;
	
	// ------------------------------------------------------------------------
	//step:2 manoover through the pipes
	//lift arm
	
	printf("-----Step 2-----\n");
	move_to_position (0, -900, -3100);
	msleep (900);
	
	//turn in an arc
	
	angle0 = get_create_total_angle (.05);
	angle = angle0;
	dangle = abs (angle0 - angle);
	printf("a0: %d, a: %d, da: %d, d: %d\n", angle0, get_create_total_angle (.05), dangle , task_A_done);
	create_drive_direct (-178,-648);
	
	while(! loop_done)
	{
		if (dangle >= 105)
		{
			create_drive_direct (-105, -181);
		}
		if (dangle >= 135)
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
		angle = get_create_total_angle (.05);
		dangle = abs (angle0 - angle);
		printf("a0: %d, a: %d, da: %d, d: %d\n", angle0, get_create_total_angle (.05), dangle , task_A_done);
	}
	
	loop_done = 0;
	
	create_stop ();
	
	task_A_done = 0;
	task_B_done = 0;
	


	// ------------------------------------------------------------------------
	//step:3 aim claw to point of botguy
	//aim arm at botguy
	printf("-----Step 4-----\n");
	
	move_to_position (0, 400, -900);
	
	set_servo_position (0 ,400);
	
	//get botguy in palm
	
	create_drive_straight (-20);
	move_to_position (0, 600, -380);
	
	while (! get_motor_done (0))
	{
		msleep (50);
	}
	
	create_drive_straight (-50);
	
	msleep (1000);
	
	// ------------------------------------------------------------------------
	//step:4 grab botguy and lift him up 
	//snatch him up
	printf("-----Step 5-----\n");
	
	create_drive_direct (60, -60);
	
	while(angle0 - get_create_total_angle (.05) < 3)
	{
		msleep(50);
	}
	
	create_stop ();
	
	//lift arm up so it doesn't get caught on poles
	
	set_servo_position (0, 1300);
	move_to_position (0, -1000, -3000);
	
	msleep (2500);
	
	
	
	// ------------------------------------------------------------------------
	//step:5 move backwards and drop botguy in box
	//backing up!...backing up!...backing up...
	
	printf("-----Step 6-----\n");
	
	create_drive_direct (130, 280);
	
	distance0 = get_create_distance (.05);
	
		
	while (! loop_done)
	{
		printf("d0: %d, d: %d, d: %d\n", distance0, get_create_distance (.05), loop_done);
		if (get_create_distance (.05) - distance0 > 740)
		{
			loop_done = 1;
		}
		msleep(50);
	}
	
	loop_done = 0;
	
	//lower arm and drop
	
	move_to_position (0, -900, -500);
	create_drive_straight (-40);
	
	msleep (3500);
	
	set_servo_position (0, 200);

	create_disconnect ();

}


