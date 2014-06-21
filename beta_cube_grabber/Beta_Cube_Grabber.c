// Created on Sat March 15 2014

// Motor port numbers
#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0

// Servo port numbers
#define ARM 0
#define CLAW 1
#define CAMERA 3

// Arm positions
#define ARM_SHELF_HEIGHT 550
#define ARM_UP 900

#define TOO_FAR_LEFT 55
#define TOO_FAR_RIGHT 85
#define CORRECT_HEIGHT 90
#define CLAW_OPEN 700
#define CLAW_CLOSED 200
#define CAMERA_CENTER_X 110

void arm_to_shelf_height();
void go (int left, int right);
int move (int left, int right, int distance);
int abs(int x);
void finger_grab();
void finger_wide_open();
void openarm();
void stop();
int drop_off_cube();
int move_across_board();
int move_to_shelf_w_camera();
int move_to_shelf_w_camera_2();
int move_to_shelf();
int move_to_drop_off();

int main(int argc, char * argv[])
{
//	int i = 0;
	
	//initalise sensors and servos and stuff
	printf("Hello, World!\n");
	enable_servos ();
	
	camera_open();
	camera_update();
	msleep(300);
	printf("initialised hardware... Waiting for light %d\n", argc);

	//if (argc == 1)
	//{
		while (analog(0) > 700)
		{
			msleep(10);
		}
		shut_down_in(118.0);
	//}

	for (;;)
	{
		set_servo_position(CAMERA, 100);
		arm_to_shelf_height ();
		set_servo_position(CLAW, 0);

		if (move_to_shelf_w_camera_2() != 1)
		{
			//wait for button press, that means we hit a cube
			while (1)
			{
				printf(".");
				if (digital(15))
				{
					printf("-----------Hit wall.\n");
					break;
				}
				else if (digital(8))
				{
					printf("-----------Claw hit.\n");

					//stop, back up
					stop ();
					go (-40, -5);
					msleep(500);
					go (-20, 0);
					msleep(500);
					stop ();

					msleep (300);

					go (10, 10);
				}
				
				msleep (10);
			}
		}
		printf("Hit the cube\n");

#else
//					msleep(2000);
	
#endif
		// Grab cube
		finger_grab ();

		// Backup and turn to drop-off corner
		
		// THIS IS THE MOST UNRELIABLE THING
		go (-50, -50);
		msleep(2200);
		stop();
		msleep(200);
		
		go (-45, 45);
		msleep(2000);
		stop();
		msleep(200);

		// Point camera down
		set_servo_position(CAMERA, 35);
		
		// Run across the board toward the drop-off zone
		if (move_to_drop_off() == 99)
		{
			return 99;
		}
		
		//wait for button press, that means we hit the PVC at the drop-off
		while (!digital(15) && !digital(14))
		{
			msleep (10);
		}

		// Drop off the cube
		// TEST THIS!!!!!!!!!!!!+
		
//		set_servo_position(ARM, 1050);
//		msleep(500);
		set_servo_position(ARM, 1150);
		msleep(1700);
		set_servo_position(CLAW, 0);
		msleep(2000);
		
		//break;
		
		// Reverse and look for another orange cube
//		set_servo_position(ARM, 1600);
		//go(-10, -10);
		//msleep(1000);
		//go(100, -100);
		//msleep(500);
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++arm_to_shelf_height ();
	}
	
	ao ();
}

int move_to_drop_off()
{
	int /*lmpc = 0, rmpc = 0,*/ left = 80, right = 80, i = 0;
	int current_rightmost_y = 0;
	int current_rightmost_x = 0;
	int current_rightmost = -1;
	int frame_number = 0;
	
	printf("Moving to drop-off\n");
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
	
	set_servo_position(CAMERA, 360);
	
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
		
		if (get_object_count(2) > 8 || get_object_count(2) == 0)
		{
			continue;
		}
		printf("number_of_objects %d \n", get_object_count(2));
		
		for (i = 0; i < get_object_count(2); i++)
		{
			if ((float)get_object_bbox(2,i).width/(float)get_object_bbox(2,i).height > 2.0 ||
				(float)get_object_bbox(2,i).width/(float)get_object_bbox(2,i).height < 0.5)
			{
//				if (get_object_center(0,i).y > 19)
//				{
//					printf("not square %d \n",i);
//					continue;
//				}
				
			}
			
			if (get_object_center(2,i).y < 20)
			{
				printf("too high %d \n",i);
				continue;
			}
			
			if ((float)get_object_area(2,i) < (float)get_object_area(2,0) *0.5)
			{
				printf("too small %d (%d vs %d)\n", i, get_object_area(2,i), get_object_area(2,0));
				continue;
			}
			
			if (get_object_center(2, i).x > current_rightmost_x || current_rightmost == -1)
			{
				current_rightmost_x = get_object_center(2, i).x;
				current_rightmost_y = get_object_center(2, i).y;
				current_rightmost = i;
			}
		}
		if (current_rightmost == -1)
		{
			continue;
		}
		printf("current_rightmost_y %d %d %d \n", current_rightmost,current_rightmost_x, current_rightmost_y);
		if (current_rightmost_x > 140)
		{
			go(left, right/8);
		}
		
		else if (current_rightmost_x > 120)
		{
			go(left, right/4);
		}
		
		else if (current_rightmost_x > CAMERA_CENTER_X)
		{
			go(left, right/2);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X/2)
		{
			go(left/8, right);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X*3/8)
		{
			go(left/4, right);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X)
		{
			go(left/2, right);
		}
		
		if (current_rightmost_y > 90 && frame_number > 10)
		{
			motor (LEFT_MOTOR, left/2);
			motor (RIGHT_MOTOR, right/2);
		}
		if (current_rightmost_y > 95 && frame_number > 10)
		{
			printf("Found!!! Off you go\n");
			return 0;
		}
		
	}

	return 0;
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
	int /*lmpc = 0, rmpc = 0,*/ left = 80, right = 80, i = 0;
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
		if (digital(8) || digital(15))
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
		if (current_rightmost_x > 140)
		{
			//go(left, right*6/8);
			go(left, right/8);
		}
		
		else if (current_rightmost_x > 120)
		{
			//go(left, right*7/8);
			go(left, right/4);
		}
		
		else if (current_rightmost_x > CAMERA_CENTER_X)
		{
			//go(left, right*7/8);
			go(left, right/2);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X/2)
		{
			//go(left*6/8, right);
			go(left/8, right);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X*3/8)
		{
			//go(left*6/8, right);
			go(left/4, right);
		}
		
		else if (current_rightmost_x < CAMERA_CENTER_X)
		{
			//go(left*7/8, right);
			go(left/2, right);
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

#if 0
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
#endif

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

void arm_to_shelf_height()
{
	set_servo_position(ARM, ARM_SHELF_HEIGHT);
}

void openarm()
{
	set_servo_position(ARM, 750);
	msleep (300);
}
void finger_wide_open()
{
	enable_servos ();
	set_servo_position(CLAW, 0);
	msleep (300);
}

void finger_grab()
{
	set_servo_position(CLAW, 650);
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

void go (int left, int right)
{
	printf("GO                                                       %d %d\n", left, right);
	motor (LEFT_MOTOR, left);
	motor (RIGHT_MOTOR, right);
}

void stop ()
{
	go (0,0);
}
