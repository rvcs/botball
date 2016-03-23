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
	//to start by light, do:
	
	//while(analog(1) > 200)
	if (0)
	{
	//we have seen the light
		msleep(100);
		if(analog(1) < 800){
			shut_down_in(119);
		}
	}
	
		
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
	// swing arm to hit the box, then get back to position
	spin (50, -50, 20);
	
	spin (-50, 50, 20);
	
	create_stop ();
	
	// ------------------------------------------------------------------------
	//step:2 knock over box and turn
	//lift arm
	//turn 90
	
	printf("-----Step 2-----\n");
	move_to_position (0, -900, -2600);
	msleep (900);
	//turn create in a circular position and raise arm so it doesn't hit anything
	angle0 = get_create_total_angle (.05);
	angle = angle0;
	dangle = abs (angle0 - angle);
	printf("a0: %d, a: %d, da: %d, d: %d\n", angle0, get_create_total_angle (.05), dangle , task_A_done);
	create_drive_direct (-178,-648);
	
	while(! loop_done)
	{
		if (dangle >= 155)
		{
			task_A_done = 1;
			create_stop ();
		}
		else if (dangle >= 125)
		{
			create_drive_direct (-120, -181);
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
	//--tweaking position so it gets in just the right position
	
	move_to_position (0, 400, -900);
	
	move (20, 20, 50);
	
	set_servo_position (0 ,400);
	
	create_drive_straight (-30);
	
	move_motor (0, 600, -300);
	
	create_drive_straight (-38);// at this point, botguy is in his palm
	
	//can't remember function to program
	
	msleep (3000);
	
	loop_done = 0;
	
	if (! loop_done)
	{
		create_stop ();
		if (! digital (10))
		{
			move_motor (0, 400, -900);
			spin (20, -20, 10);
			move_motor (0, 600, -300);
			create_stop ();
			
			loop_done = 1;
		}
		else
		{
			loop_done = 1;
		}
	}
	
	
	
	// ------------------------------------------------------------------------
	//step:5 grab botguy and lift him up (not complete)
	printf("-----Step 5-----\n");
	
	move (-10, -10, 20);
	msleep (1300);
	//spin (60, -60, 5);
	//close arm and grab botguy
	set_servo_position (0, 1510);
	msleep (400);
	move_to_position (0, -1000, -3000);
	//wait for him to finish
	msleep (5000);
	
	
	
	// ------------------------------------------------------------------------
	//step:6 move backwards till it's in position
	
	printf("-----Step 6-----\n");
	//back up in an arc
	move (130, 280, 780);
	//move towards the center and lower drop height
	move_to_position (0, -900, -500);
	create_drive_straight (-20);
	
	msleep (3000);
	//drop botguy in transport
	set_servo_position (0, 200);
	create_stop ();
	//start moving towards the pipe
	move_motor (0, 500, -900);
	
	/*
	if (! loop_done)
	{
		if (get_object_count(2) == 1)
		{
			create_stop ();
			spin(-10, 10, 5);
			create_stop ();
			move(20, 20, 20);
			create_stop ();
			set_servo_position (0, 1400);
			loop_done = 1;
		}
	}
	loop_done = 0;
	spin (10, 10, 5);
	set_servo_position (0, 200);
	*/
	
/*
	spin (50, -50, 85);
	
	move_motor (0, 400, -400);
	
	move (-100, -100, 50);
	
	loop_done = 0;
	//close arm on pipe
	set_servo_position (0, 1510);
	//turn arm to face the pole
	spin (-50, 50, 50);
	//up, forward, then drop pipe
	move_motor (0, 400, -2300);
	
	move (-100, -100, 100);
	
	set_servo_position (0, 200);
	
	ao ();
*/
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

