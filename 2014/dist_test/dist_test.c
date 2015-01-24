// Created on Mon March 10 2014

// Created on Sat March 8 2014
// KBot_main is main program for Cube Bot
// use camera and scanner

#define MOTOR_0 0
#define MOTOR_3 3
/* clear motor pos ctr and move to new pos */
#define KILO_TICK 1000
//Approx. 2.5 inches
/*
void clr_and_move(int motor, int speed, int ticks)
{
	//clear_motor_position_counter(0);
	move_to_position(0, 900, 1000);
	move_to_position(3, 900, 1000);
}
*/

int main()
{
	int distance = 0;
	
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	// moves bot from cubes to cylinders
	move_relative_position(1, 1000, 12000);
	move_relative_position(2, 1000, 12000);
	// wait to be sure the move has time to finish
	block_motor_done(1);
	block_motor_done(2);
	// now check if we have moved correct amount
	distance = get_motor_position_counter(1);
	printf("motor moved %d\n", distance);
	distance = get_motor_position_counter(2);
	printf("motor moved 2 %d\n", distance);
	// reset, for next move 
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	ao();
	return 0;
}



