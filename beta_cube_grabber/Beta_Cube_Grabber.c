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
	
	closearm ();
	elbowdrop ();
	
	move_to_shelf();
	
	//move_to_shelf_w_camera();
	
	//insert cube finding protocall
	
	move_across_board();
	
	//move across the board
	
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
	int current_rightmost = 0;
	
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	//move_at_velocity (1, left);
	motor (LEFT_MOTOR, left);
	//move_at_velocity (2, right);
	motor (RIGHT_MOTOR, right);
	
	while(1) 
	{
		camera_update();
		for (i = 0; i < get_object_count(0); i++)
		{
			if (get_object_center(0, i).x> current_rightmost_x)
			{
				current_rightmost_x = get_object_center(0, i).x;
				current_rightmost_y = get_object_center(0, i).y;
				current_rightmost = i;
			}
		}
		if (current_rightmost_x > 84)
		{
			motor (RIGHT_MOTOR, right/2);
		}
		
		else if (current_rightmost_x < 76)
		{
			motor (LEFT_MOTOR, left/2);
		}
		
		if (current_rightmost_y < 18)
		{
			motor (LEFT_MOTOR, 40);
			motor (RIGHT_MOTOR, 40);
			return (0);
		}
		
		//lmpc = get_motor_position_counter(LEFT_MOTOR);
		//rmpc = get_motor_position_counter(RIGHT_MOTOR);
		//if (abs(lmpc) + abs(rmpc) > abs(distance))
		//{
			//break;
		//}
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
	elbowdrop ();
	
	return 1;
}

int closearm()
{
	set_servo_position (0, 1000);
	msleep (300);
}
int openarm()
{
	set_servo_position (0, 750);
	msleep (300);
}
int elbowup()
{
	enable_servos ();
	set_servo_position (1, 890);
	msleep (300);
}
int elbowdrop()
{
	set_servo_position (1, 100);
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
