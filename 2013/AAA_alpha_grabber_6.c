 // Created on Sun March 24 2013
int spin ();
int move ();
int move_motor ();

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
	
	move_motor (0, -900, -1200);
	
	spin (50, -50, 20);
	
	spin (-50, 50, 20);
	
	create_stop ();
	
	// ------------------------------------------------------------------------
	//step:2 knock over box and turn
	//lift arm
	//turn 90
	
	printf("-----Step 2-----\n");
	move_to_position (0, -900, -3100);
	msleep (900);
	
	angle0 = get_create_total_angle (.05);
	angle = angle0;
	dangle = abs (angle0 - angle);
	printf("a0: %d, a: %d, da: %d, d: %d\n", angle0, get_create_total_angle (.05), dangle , task_A_done);
	create_drive_direct (-178,-648);
	
	while(! loop_done)
	{
		if (dangle >= 125)
		{
			create_drive_direct (-120, -181);
		}
		if (dangle >= 155)
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
	
	
	create_stop ();


	// ------------------------------------------------------------------------
	//step:4 aim claw to point of botguy
	//turn 20
	//lower arm
	
	printf("-----Step 4-----\n");
	
	move_to_position (0, 400, -900);
	
	move (20, 20, 50);
	
	set_servo_position (0 ,400);
	
	create_drive_straight (-20);
	
	move_motor (0, 600, -300);
	
	create_drive_straight (-50);
	
	msleep (2200);
	
	
	
	// ------------------------------------------------------------------------
	//step:5 grab botguy and lift him up (not complete)
	printf("-----Step 5-----\n");
	
	spin (60, -60, 5);
	
	set_servo_position (0, 1510);
	move_to_position (0, -1000, -3000);
	
	msleep (5000);
	
	
	
	// ------------------------------------------------------------------------
	//step:6 move backwards untill the bumper hits the transport (not completed)
	
	printf("-----Step 6-----\n");
	
	move (130, 280, 700);
	
	move_to_position (0, -900, -500);
	create_drive_straight (-20);
	
	msleep (3000);
	
	set_servo_position (0, 200);
	
	move_motor (0, 400, -700);
	
	spin (50, -50, 85);
	
	move_motor (0, 400, -400);
	
	move (-100, -100, 50);
	
	loop_done = 0;
	
	set_servo_position (0, 1510);
	
	spin (-50, 50, 220);
	
	//set_servo_position (0, 200);
	
	move_motor (0, 400, -150);
	
	//set_servo_position (0, 1510);
	
	move_motor (0, 400, -2300);
	
	move (-100, -100, 100);
	
	set_servo_position (0, 200);
	
	ao ();
	
	create_disconnect ();
}

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
	}
}

