// Created on Sat March 15 2014

#include <string.h>

#define TRUE 1
#define FALSE 0

// MOVEMENT == 0 to make the motor commands inert
#define MOVEMENT 1
#define LEFT_MOTOR_PORT 0
#define RIGHT_MOTOR_PORT 1

int left = 0, delta_left = 0;			// Power to the left wheel
int right = 0, delta_right = 0;			// Power to the right wheel

char message[1025];
char * msg;
int diag()
{
	msg = message + strlen(message);
	return 0;
}
//	sprintf(msg, fmt, arg);
//	msg = message + strlen(message);

int main()
{
	// Constants
	int width = 160;
	int hcenter = width / 2;
	int height = 120;
	int vcenter = height / 2;

	// Variables
	point2 center;
	int blob_count = 0;

	int no_blob_count = 0;			// Count of number of times through the loop where we saw zero blobs
	
	camera_open();
	camera_update();
	msleep(300);
	
	while (1) {
		// Top of the loop -- initialize
		delta_left = delta_right = 0;
		msg = &message[0];
		*msg = 0;
		
		// Top of the loop -- read values
		camera_update();
		blob_count = get_object_count(0);
		sprintf(msg, "%5d", blob_count);
		diag();

		//if (FALSE) {
		if (blob_count == 0) {
			no_blob_count++;
			if (no_blob_count > 10 && left == right && left == 0) {
				no_blob_count = 0;
				delta_left = delta_right = 5;
				sprintf(msg, "Creeping forward");
				diag();
				goto do_actions;
			}
		}
		else if (blob_count > 0) {
			center = get_object_center(0, 0);
			
			// Diagnostic
			show_xy(center.x, center.y);
			
			if (center.x < hcenter-5) {
				sprintf(msg, " left");
				diag();
				small_left(2);
			}
			else if (center.x > hcenter+5) {
				sprintf(msg, " right");
				diag();
				small_right(2);
			}
			else {
				left = right = current_average_power();
				delta_left = delta_right = 0;
				sprintf(msg, " 0");
				diag();
				goto do_actions;
			}
		}
//		msleep(300);

do_actions:
		left += delta_left;
		right += delta_right;
		
		if (left > 100)   { left = 100; }
		if (left < -100)  { left = -100; }
		if (right > 100)  { right = 100; }
		if (right < -100) { right = -100; }
		
		printf(" |%3d %4d <-> %4d %3d|  %s\n", delta_left, left, right, delta_right, message);
		message[0] = 0;
		diag();
		
		if (MOVEMENT) {
			motor(LEFT_MOTOR_PORT, left);
			motor(RIGHT_MOTOR_PORT, right);
		}
	}
	
	printf("Done!\n");
	return 0;
}

/**
 *	Increase power to the left wheel, but not a lot
 */
int small_left(int x)
{
	int l, r;
	int rfix = 0, lfix = 0, average;
	
	l = left + x;
	r = right;
	
	// Are we going to end up with too much power?
	if ((average = average_power(l, r)) > 25) {
		split_power(average - 25, &lfix, &rfix);
	}
	
	l = l - lfix;
	r = r - rfix;
	
	delta_left = l - left;
	delta_right = r - right;
}

/**
 *	Increase power to the right wheel, but not a lot
 */
int small_right(int x)
{
	int l, r;
	int rfix = 0, lfix = 0, average;
	
	l = left;
	r = right + x;
	
	// Are we going to end up with too much power?
	if ((average = average_power(l, r)) > 25) {
		split_power(average - 25, &lfix, &rfix);
	}
	
	l = l - lfix;
	r = r - rfix;
	
	delta_left = l - left;
	delta_right = r - right;
}

/**
 *	Increase power to the left wheel, but not a lot
 */
int small_left1(int x)
{
	int l, r, dr, dl;
	int starting_power, too_much, rfix, lfix;
	
	starting_power = current_average_power();
	
	split_power(x, &dl, &dr);
	l = left + dl;
	r = right - dr;
	
	// Are we going to end up with too much power?
	split_power(average_power(l, r) - starting_power, &lfix, &rfix);
	
	l = l - lfix;
	r = r - rfix;
	
	delta_left = left - l;
	delta_right = right - r;
}

/**
 *	Increase power to the right wheel, but not a lot
 */
int small_right1(int x)
{
	int l, r, dr, dl;
	int starting_power, too_much, rfix, lfix;
	
	starting_power = current_average_power();
	
	split_power(x, &dl, &dr);
	l = left - dl;
	r = right + dr;
	
	// Are we going to end up with too much power?
	split_power(average_power(l, r) - starting_power, &lfix, &rfix);
	
	l = l - lfix;
	r = r - rfix;
	
	delta_left = left - l;
	delta_right = right - r;
}

int split_power(int p, int * a, int * b)
{
	*a = p / 2, *b = p - *a;
}

int total_power(l, r)
{
	return l + r;
}

int average_power(l, r)
{
	return total_power(l, r) / 2;
}

int current_total_power()
{
	return total_power(left, right);
}

int current_average_power()
{
	return current_total_power() / 2;
}

#define MAX_WIDTH 160
#define SHOW_WIDTH 64

int show_xy(int x, int y)
{
	static char disp[SHOW_WIDTH + 2];
	int char_pos = (int)((float)x * (float)SHOW_WIDTH / (float)MAX_WIDTH);
	memset(disp, ' ', SHOW_WIDTH + 1);
	disp[SHOW_WIDTH] = '|';
	disp[SHOW_WIDTH + 1] = 0;
	disp[char_pos] = '*';
	sprintf(msg, "%5d %5d %s", x, y, disp);
	diag();
}

int move_right(int dist)
{
	if (!MOVEMENT) {
		return 0;
	}
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	move_relative_position(1, 1000, dist);
	move_relative_position(2, 1000, -dist);
	block_motor_done(1);
	block_motor_done(2);
}

int move_left(int dist)
{
	if (!MOVEMENT) {
		return 0;
	}
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	move_relative_position(1, 1000, -dist);
	move_relative_position(2, 1000, dist);
	block_motor_done(1);
	block_motor_done(2);
}

int back(int dist)
{
	if (!MOVEMENT) {
		return 0;
	}
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	move_relative_position(1, 1000, -dist);
	move_relative_position(2, 1000, -dist);
	block_motor_done(1);
	block_motor_done(2);
}

int forward(int dist)
{
	if (!MOVEMENT) {
		return 0;
	}
	clear_motor_position_counter(1);
	clear_motor_position_counter(2);
	move_relative_position(1, 1000, dist);
	move_relative_position(2, 1000, dist);
	block_motor_done(1);
	block_motor_done(2);
}



