// Created on Sun March 24 2013

void main ()
{
	int loop_done = 0;
	int task_A_done = 0;
	int task_B_done = 0;
	int angle0 = 0;
	
	
	//get_create_total_ angle (.1);
	//create_drive_direct (left speed, right speed)\
	//move_to_position (motor #, motor power(-for backwards), end position)
	//get_motor_done (motor#)
	//clear_motor_position_counter (motor#)
	//msleep (seconds)
		//i'll probably use this often
	create_connect ();
	
	clear_motor_position_counter (0);
	
	angle0 = get_create_total_angle (.1);
	create_drive_direct (150,-150);
	
	move_to_position (0, -900, -1550);
	
	while(! loop_done)
	{
		printf("a0: %d, a: %d, d: %d\n", angle0, get_create_total_angle (.1), task_A_done);
		if (angle0 - get_create_total_angle (.1) < 90)
		{
			create_drive_direct (150,-150);
		}
		else
		{
			task_A_done = 1;
		}
		if (get_motor_done (0))
		{
			
		}
		else
		{
			task_B_done = 1;
		}
		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
		msleep(0.1);
	}
	
	create_stop ();
	create_disconnect ();
	
	//put specific commands to control robot in here
//	loop_done = 0;
//	task_A_done = 0;
//	task_B_done = 0;
//	while(! loop_done)
//	{
//		if (/*task A is not done*/)
//		{
//			//continue doing task A
//		}
//		else
//		{
//			task_A_done = 1;
//		}
//		if (/*task B is not done*/)
//		{
//			//continue doing task B
//		}
//		else
//		{
//			task_B_done = 1;
//		}
//		if (task_A_done && task_B_done)
//		{
//			loop_done = 1;
//		}
//	}
}


