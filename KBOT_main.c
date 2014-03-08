// Created on Sat March 8 2014
// KBot_main is main program for Cube Bot
// use camera and scanner

#define MOVE_FORWARD 900
#define 90_DEGREE_TURN 950
#define MOVE_BACKWARD -900
#define MOTOR_0 0
#define MOTOR_3 3
/* clear otor pos ctr and move to new pos */
void clr_and_move(int motor, int speed, int ticks)
{
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
}

int main()
{
	printf("Hello, World!\n");
	
	// find the cubes
	//mav(0, MOVE_FORWARD);
	//mav(3, MOVE_FORWARD);
	//msleep(3500);
	//ao();
	// Moves bot forward for 3.5 seconds then stops
	//mav(3, 90_DEGREE_TURN);
	//msleep(2500);
	//ao();
	// Bot moves right for 2.5 seconds then stops
	//mav(0, MOVE_FORWARD);
	//mav(3, MOVE_FORWARD);
	//msleep(1500);
	//ao();
	// Moves forward once more for 1.5 seconds
		
	// grab one
	
	// put it somewhere
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	mav(0, 90_DEGREE_TURN);
	get_motor_position_counter(1100);
	mav(3, 90_DEGREE_TURN);
	// Moves bot forward to cubes getting ready to grab them
	mav(0, MOVE_BACKWARD);
	mav(3, MOVE_BACKWARD);
	msleep(2000);
	ao();
	//Moves bot backwards to get ready to move again
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	clear_motor_position_counter(0);
	move_relative_position(0, 900, 1000);
	move_relative_position(1, 900, 1000);
	mav(3, 90_DEGREE_TURN);
	msleep(2000);
	ao();
	// Moves bot to cylinders to drop off cubes
	return 0;
}
