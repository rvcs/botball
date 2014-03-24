// Created on Sat March 15 2014

int main()
{
	enable_servos ();
	closearm ();
	elbowdrop ();
	
	move_to_shelf();
	
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
