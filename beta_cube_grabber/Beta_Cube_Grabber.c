// Created on Sat March 15 2014

int main()
{
	enable_servos ();
	closearm ();
	elbowdrop ();
	//move forward towards the cubes
	move (450, 480, 10000);
	//try to get alligned with the board
	move (600, 450, 3000);
	//insert cube finding protocall
	msleep (500);
	move (-500, -500, 1500);
	//backing up
	msleep (500);
	move (-450, 50, 1800);
	//turn 90 degrees
	//move (-200, 400, 1000);
	move (800, 800, 22000);
	//move across the board
	move (-500, 500, 1600);
	//turn to the drop-off zone
	move (300, 300, 1000);
	move (250, 250, 500);
	//scootch forward
	openarm ();
	elbowdrop ();
	ao ();
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
