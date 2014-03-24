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
	//move forward towards the cubes
	move (450, 500, 10000);
	//try to get alligned with the board
	move (600, 450, 3000);
	
	return 1;
}

int move_to_shelf_w_camera()
{
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
	msleep (500);
	move (-500, -500, 1500);
	//backing up
	msleep (500);
	move (-450, 50, 1800);
	//turn 90 degrees
	move (800, 800, 22000);
	
	return 1;
}

int drop_off_cube()
{
	move (-500, 500, 1600);
	//turn to the drop-off zone
	move (300, 300, 1000);
	move (250, 250, 500);
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

int move (int left, int right, int delay)
{
	//move_at_velocity (1, left);
	motor (1, left * 0.1);
	//move_at_velocity (2, right);
	motor (2, right * 0.1);
	msleep (delay * 0.5);
}
