// Created on Sat March 23 2013
int turn(int degrees);
int turn3(int degrees, int left, int right, int auto_stop);
int halt_create();
int lift_arm();

int main()
{
	int loop_done = 0;
	int angle0 = get_create_total_angle(0.1);
	int degrees;
	int arm_end_position, arm_power, arm_done;
	int rotate_done;
	int left, right;
	
	clear_motor_position_counter(0);
	
	// Hit the square
	turn3(-5, 75, -75, 0);
	
	// raise the arm, continue turning
	degrees = -45;
	left = 50;
	right = -50;
	arm_power = -500;
	arm_end_position = -1400;
	
		angle0 = get_create_total_angle(0.1);
		create_drive_direct(left, right);

		move_to_position(0, arm_power, arm_end_position);

		rotate_done = 0;
		while (!loop_done)
		{
			if (get_create_total_angle(0.1) - angle0 > degrees)
				rotate_done = 1;
			if (!rotate_done)
				create_drive_direct(left, right);
			
			arm_done = get_motor_done(0);
			
			if (arm_done && rotate_done)
				loop_done = 1;
		}
	
	printf("Starting Brian\n");
	create_connect();

	halt_create();
	return 0;
//	lift_arm();
	
//	halt_create();
//	return 0;
	
	turn(-45);

	while (!digital(11))
	{
		printf("%d\n", digital(11));
		create_drive_direct(-50, -50);
	}

	turn(-25);

	while (!digital(11))
	{
		printf("%d\n", digital(11));
		create_drive_direct(-150, -150);
	}

	halt_create();
	return 0;
}

int lift_arm()
{
	int m0_position = 0,m1_position = 0;

	clear_motor_position_counter(0);

	printf("M0:%d\n", (m0_position = get_motor_position_counter(0)));
	printf("M1:%d\n", (m1_position = get_motor_position_counter(1)));
	printf("M2:%d\n", get_motor_position_counter(2));
	printf("M3:%d\n", get_motor_position_counter(3));
	
	move_to_position(0, -500, -600);

	while (!get_motor_done(0))
	{
		printf("M1:%d\n", get_motor_position_counter(0));
	}
	
	return 0;
}

int halt_create()
{
	create_stop();
	create_disconnect();
}

int turn(int degrees)
{
	if (degrees < 0)
		turn_right(degrees);
	else
		turn_left(degrees);
}

int turn3(int degrees, int left, int right, int auto_stop)
{
	if (degrees < 0)
		turn_right3(degrees, left, right, auto_stop);
	else
		turn_left3(degrees, left, right, auto_stop);
}

int turn_left3(int degrees, int left, int right, int auto_stop)
{
	int angle0 = get_create_total_angle(.1);
	
	while (get_create_total_angle(0.1) - angle0 < degrees)
	{
		printf("angle: %d", get_create_total_angle(0.1));
		create_drive_direct(left, right);
		msleep(0.1);
	}
	if (auto_stop)
		create_stop();
}

int turn_left(int degrees)
{
	return turn_left3(degrees, 250, -250, 1);
}

int turn_right3(int degrees, int left, int right, int auto_stop)
{
	int angle0 = get_create_total_angle(.1);
	
	while (get_create_total_angle(0.1) - angle0 > degrees)
	{
		printf("angle: %d", get_create_total_angle(0.1));
		create_drive_direct(left, right);
		msleep(0.1);
	}
	if (auto_stop)
		create_stop();
}

int turn_right(int degrees)
{
	return turn_right3(degrees, -250, 250, 1);
}

