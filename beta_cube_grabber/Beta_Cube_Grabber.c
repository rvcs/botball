// Created on Sat March 15 2014

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0
#define ARM_UP 900
#define ARM 0
#define TOO_FAR_LEFT 55
#define TOO_FAR_RIGHT 85
#define CORRECT_HEIGHT 90
#define CLAW 1
#define CLAW_OPEN 700
#define CLAW_CLOSED 200

int main()
{
	//initalise sensors and servos and stuff
	printf("Hello, World!\n");
	enable_servos ();
	
	camera_open();
	camera_update();
	msleep(300);
	printf("initialised hardware\n");
	
	arm_to_shelf_height ();
	set_servo_position (1, 500);
	
	if (move_to_shelf_w_camera_2() != 1)
	{
		//wait for button press, that means we hit a cube
		while (!digital(8))
		{
			printf(".");
			msleep (10);
		}
	}
	printf("Hit the cube\n");
	
	//stop, back up
	stop ();
	go (-10, -10);
	msleep(250);
	stop ();

#if 0
	//raise arm, open finger
	set_servo_position (0, 1500);
	msleep (300);
#endif
	finger_wide_open ();
	msleep (300);

#if 0
	// Lower arm, go forward
	arm_to_shelf_height ();
	msleep (2000);
#endif
	go (10, 10);
	msleep (1250);
	stop ();
	
	// Grab cube
	finger_grab ();

	// Backup and turn to drop-off corner
	//set_servo_position (0, 1700);

	go (-50, -50);
	msleep(1500);
	go (-45, 45);
	msleep(1800);

	//wait for button press, that means we hit the PVC at the drop-off
	go(80, 80);
	move_to_drop_off();
	while (!digital(15))
	{
		msleep (10);
	}
		
	drop_off_cube();
	
	ao ();
}

int move_to_shelf()
{
	printf("Moving to shelf\n");
	
	//move forward towards the cubes
	move (45, 50, 10000);
	//try to get alligned with the board
	move (60, 45, 3000);
	
	return 1;
}

int move_to_shelf_w_camera_2()
{
	int lmpc = 0, rmpc = 0, left = 80, right = 80, i = 0;
	int current_rightmost_y = 0;
	int current_rightmost_x = 0;
	int current_rightmost = -1;
	int frame_number = 0;
	
	printf("Moving to shelf with camera\n");
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
	
	while(1) 
	{
		//printf("something like about to update camera\n");
		current_rightmost = -1;
		if (digital(8) == 1)
		{
			return 1;
		}
		
		camera_update();
		
		frame_number++;
		printf("Frame # %d\n", frame_number);
		if (frame_number < 12)
		{
			continue;
		}
		
		if (get_object_count(0) > 8 || get_object_count(0) == 0)
		{
			continue;
		}
		printf("number_of_objects %d \n", get_object_count(0));
		
		for (i = 0; i < get_object_count(0); i++)
		{
			if ((float)get_object_bbox(0,i).width/(float)get_object_bbox(0,i).height > 2.0 ||
				(float)get_object_bbox(0,i).width/(float)get_object_bbox(0,i).height < 0.5)
			{
//				if (get_object_center(0,i).y > 19)
				{
					printf("not square %d \n",i);
					continue;
				}
				
			}
			
			if (get_object_center(0,i).y > 60)
			{
				printf("too low %d \n",i);
				continue;
			}
			
			if ((float)get_object_area(0,i) < (float)get_object_area(0,0) *0.5)
			{
				printf("too small %d (%d vs %d)\n", i, get_object_area(0,i), get_object_area(0,0));
				continue;
			}
			
			if (get_object_center(0, i).x > current_rightmost_x || current_rightmost == -1)
			{
				current_rightmost_x = get_object_center(0, i).x;
				current_rightmost_y = get_object_center(0, i).y;
				current_rightmost = i;
			}
		}
		if (current_rightmost == -1)
		{
			continue;
		}
		printf("current_rightmost_y %d %d %d \n", current_rightmost,current_rightmost_x, current_rightmost_y);
		if (current_rightmost_x > 105)
		{
			//go(left, right*6/8);
			go(left, right/8);
		}
		
		else if (current_rightmost_x > 80)
		{
			//go(left, right*7/8);
			go(left, right/4);
		}
		
		else if (current_rightmost_x < 40)
		{
			//go(left*6/8, right);
			go(left/8, right);
		}
		
		else if (current_rightmost_x < 80)
		{
			//go(left*7/8, right);
			go(left/4, right);
		}
		
		if (current_rightmost_y < 30 && frame_number > 10)
		{
			//left = left/2;
			//right = right/2;
			motor (LEFT_MOTOR, left/2);
			motor (RIGHT_MOTOR, right/2);
		}
		if (current_rightmost_y < 25 && frame_number > 10)
		{
			printf("Found!!! Off you go\n");
			return(0);
		}
		
	}
	
	return 0;
}

int move_to_drop_off()
{
	int lmpc = 0, rmpc = 0, left = 80, right = 80, i = 0;
	int current_rightmost_y = 0;
	int current_rightmost_x = 0;
	int current_rightmost = -1;
	int frame_number = 0;
	
	printf("Moving to drop-off\n");
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
	
	while(1) 
	{
		//printf("something like about to update camera\n");
		current_rightmost = -1;
		if (digital(8) == 1)
		{
			return 1;
		}
		
		camera_update();
		
		frame_number++;
		printf("Frame # %d\n", frame_number);
		if (frame_number < 12)
		{
			continue;
		}
		
		if (get_object_count(0) > 8 || get_object_count(0) == 0)
		{
			continue;
		}
		printf("number_of_objects %d \n", get_object_count(0));
		
		for (i = 0; i < get_object_count(0); i++)
		{
			if ((float)get_object_bbox(0,i).width/(float)get_object_bbox(0,i).height > 2.0 ||
				(float)get_object_bbox(0,i).width/(float)get_object_bbox(0,i).height < 0.5)
			{
//				if (get_object_center(0,i).y > 19)
//				{
//					printf("not square %d \n",i);
//					continue;
//				}
				
			}
			
			if (get_object_center(0,i).y < 60)
			{
				printf("too high %d \n",i);
				continue;
			}
			
			if ((float)get_object_area(0,i) < (float)get_object_area(0,0) *0.5)
			{
				printf("too small %d (%d vs %d)\n", i, get_object_area(0,i), get_object_area(0,0));
				continue;
			}
			
			if (get_object_center(0, i).x > current_rightmost_x || current_rightmost == -1)
			{
				current_rightmost_x = get_object_center(0, i).x;
				current_rightmost_y = get_object_center(0, i).y;
				current_rightmost = i;
			}
		}
		if (current_rightmost == -1)
		{
			continue;
		}
		printf("current_rightmost_y %d %d %d \n", current_rightmost,current_rightmost_x, current_rightmost_y);
		if (current_rightmost_x > 105)
		{
			go(left, right/8);
			//motor (RIGHT_MOTOR, right/4);
		}
		
		else if (current_rightmost_x > 80)
		{
			go(left, right/4);
			//motor (RIGHT_MOTOR, right/2);
		}
		
		else if (current_rightmost_x < 40)
		{
			go(left/8, right);
			//motor (LEFT_MOTOR, left/4);
		}
		
		else if (current_rightmost_x < 80)
		{
			go(left/4, right);
			//motor (LEFT_MOTOR, left/2);
		}
		
		if (current_rightmost_y > 90 && frame_number > 10)
		{
			//left = left/2;
			//right = right/2;
			motor (LEFT_MOTOR, left/2);
			motor (RIGHT_MOTOR, right/2);
		}
		if (current_rightmost_y > 95 && frame_number > 10)
		{
			printf("Found!!! Off you go\n");
			return(0);
		}
		
	}

	return 0;
}

int move_to_shelf_w_camera()
{
	printf("Moving to shelf with camera\n");
	
	int objseen = 0;
	int lcube = 0;
	int rcube = 0;
	
	point2 cubecenter1;
	point2 cubecenter2;
	
	objseen = get_object_count(0);
	
	/**
	 *	shouldn't call get object center (0,0) if objseen == 0,
	 *	there is no object number 0 in this case.
	 *
	 *	shouldn't call get object center (0,1) if objseen < 2,
	 *	there is no object number 1 in this case.
	 */
	
	cubecenter1 = get_object_center(0,0);
	cubecenter2 = get_object_center(0,1);
	
	if(cubecenter1.x > cubecenter2.x)
	{
		rcube = cubecenter1.x;
		lcube = cubecenter2.x;
	}
	else 
	{
		lcube = cubecenter1.x;
		rcube = cubecenter2.x;
	}
	/**
	 *	above, the code checks for which of two objects is the left one, but
	 *	the idea of more than one object is not present inside this while loop.
	 *
	 *	can't call object get object center 0,0 unless you know you have an object
	 *	like above.
	 */

	while(cubecenter1.y <= CORRECT_HEIGHT)
	{
		camera_update();
		
		cubecenter1 = get_object_center(0,0);
		
		if(cubecenter1.x >= TOO_FAR_LEFT && cubecenter1.x <= TOO_FAR_RIGHT)
		{
			mav(RIGHT_MOTOR, 600);
			mav(LEFT_MOTOR, 600);
			
		}
		if(cubecenter1.x <= TOO_FAR_LEFT)
		{
			
			mav(RIGHT_MOTOR, 700);
			mav(LEFT_MOTOR, 300);
			
		}
		if(cubecenter1.x >= TOO_FAR_RIGHT)
		{
			
			mav(RIGHT_MOTOR, 300);
			mav(LEFT_MOTOR, 700);
			
		}
		/**
		 *	I think that the orange object is going to go off screen 
		 *	before it's going to be in range of the grabber.
		 */
	}
	return 1;
}

int move_across_board ()
{
	printf("Moving to bin\n");
	
	msleep (500);
	move (-50, -50, 1500);
	//backing up
	msleep (500);
	move (-45, 5, 1800);
	//turn 90 degrees
	move (80, 80, 22000);
	
	return 1;
}

int drop_off_cube()
{
	printf("Drop off cube\n");
	
	move (-50, 50, 1600);
	//turn to the drop-off zone
	move (30, 30, 1000);
	move (25, 25, 500);
	//scootch forward
	openarm ();
	finger_grab ();
	
	return 1;
}

int arm_to_shelf_height()
{
	set_servo_position (0, 1310);
	msleep (300);
}
int openarm()
{
	set_servo_position (0, 750);
	msleep (300);
}
int finger_wide_open()
{
	enable_servos ();
	set_servo_position (1, 0);
	msleep (300);
}
int finger_grab()
{
	set_servo_position (1, 550);
	msleep (300);
}

int abs(int x)
{
	if (x >= 0) {
		return x;
	}
	return -x; 
}

int move (int left, int right, int distance)
{
	int lmpc = 0, rmpc = 0;
	printf("move (int left, int right, int distance) %d %d %d\n", left, right, distance);
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	//move_at_velocity (1, left);
	motor (LEFT_MOTOR, left);
	//move_at_velocity (2, right);
	motor (RIGHT_MOTOR, right);

	while(1) {
		lmpc = get_motor_position_counter(LEFT_MOTOR);
		rmpc = get_motor_position_counter(RIGHT_MOTOR);
		if (abs(lmpc) + abs(rmpc) > abs(distance)) {
			break;
		}
	}
	
	return 0;
}

int go (int left, int right)
{
	printf("GO                                                       %d %d\n", left, right);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
}

int stop ()
{
	go (0,0);
}
