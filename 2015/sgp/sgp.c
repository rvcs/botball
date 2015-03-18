// Created on Tue March 17 2015

int go(int left, int right)
{
	motor(0, left);
	motor(2, right);
	
	return 1;
}

int go_for(int left, int right, int msec)
{
	go(left, right);
	msleep(msec);
	return 1;
}

int main()
{
	double start = 0.0;
	int left = 100;
	int right = 100;
	
	// initialize servo, camera, etc here?.
	// if you are using a Create you should uncomment the next line
	//create_connect();
	enable_servos ();
	set_servo_position(3, 1977);
	
//	wait_for_light(2); // change the port number to match where your robot 
	double very_start = seconds();

	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds
	// note that shut_down_in should immediately follow wait_for_light!!

	int a1;
	int a2;
	
	goto THAT_SPOT;
	
	// Hit the vacuum bot
	go_for(-100, -100, 1000);

	// Back up
	go_for(100, 100, 400);

	// Rotate before the alignment
	go_for(0, 100, 1300);

	// Back up and align robot
	go_for(-100, -100, 2000);
	
	// Move out of the starting box
	double starting_out_of_box = seconds();
		
	printf("before 3000 delay\n");
	go_for(85, 85, 3000);
	printf("after 3000 delay\n");
	
	// Put arm in right pos, so it might catch the divider
	set_servo_position(3, 1703);
	msleep(750);	// The jiggle may throw the reflectance sensors off

	// Loop and read reflectance sensors
	a1 = analog(1);
	a2 = analog(3);
	printf("%4d %4d %5.2lf\n", a1, a2, seconds() - starting_out_of_box);
	
	// Trigger on one sensor
	while (a1 < 400 && a2 < 400) {
		a1 = analog(1);
		a2 = analog(3);
		printf("%4d %4d %5.2lf\n", a1, a2, seconds() - starting_out_of_box);
		
		// Dead reconing -- don't drive forward longer than this
		if (seconds() - starting_out_of_box > 6.5) {
			printf("Timeout\n");
			break;
		}
	}
	printf("Found black, turning\n");

	start=seconds ();
	// turn to go toward the middle
	//go_for(80, 0, 1250);
	go(0, 0);
	clear_motor_position_counter(0);
	mtp(0, 1500, 1300);
	block_motor_done(0);
	
	// move under the mesa
	printf("go forward\n");
	go_for(85, 85, 1500);
	
	// Loop and read reflectance sensors
	a1 = analog(1);
	a2 = analog(3);
	printf("%4d %4d %5.2lf ===\n", a1, a2, seconds() - very_start);
	
	// Trigger on two sensors
	while (a1 < 600 || a2 < 600) {
		a1 = analog(1);
		a2 = analog(3);
		printf("%4d %4d %5.2lf ---\n", a1, a2, seconds() - very_start);
	}

	printf("turn right\n");
	//go_for(80, 0, 1250);
	go(0, 0);
	clear_motor_position_counter(0);
	mtp(0, 1500, 1300);
	block_motor_done(0);
	

THAT_SPOT:
	
	printf("run down cave\n");
	set_servo_position(3, 1977);	// No guide
	
	// Loop and read reflectance sensors
	a1 = analog(1);
	a2 = analog(3);
	printf("%4d %4d %5.2lf ===\n", a1, a2, seconds() - very_start);

	// Run for a handful of seconds
	start = seconds();
	while (seconds() - start < 3.5) {		// 5.5 seems good for normal program
		a1 = analog(1);
		a2 = analog(3);
		
		left = right = 80;
		if (a1 > 500) {			// left sensor is over the black
			right += 20;
		}
		if (a2 > 500) {			// right sensor is over the black
			left += 20;
		}
		printf("go: %4d %4d : %4d %4d %5.2lf \n", a1, left, a2, right, seconds() - very_start);
		go(left, right);
	}

	set_servo_position(3,633);		// Down
	msleep(1000);
//	go_for(-75, -75, 5500);
	
	// Back up a little -- pulling poms back
	go_for(-60, -100, 1500);
	
	// Rotate in place
	go_for(100, -100, 600);
	
	// Back up to align
	go_for(-100, -100, 400);
	
	// Lift arm
	set_servo_position(3, 1977);	// High ----
	
	// Ram poms against PVC
	go_for(100, 100, 2000);
	
	// Back up
	go_for(-100, -100, 2000);
	
	// Put arm down
	set_servo_position(3, 450);		// Way Down
	msleep(700);

	// Ram poms against PVC
	go_for(100, 100, 1500);
	
	set_servo_position(3, 700);
	go_for(-100, -100, 100);

	set_servo_position(3, 750);
	go_for(-100, -100, 100);

	set_servo_position(3, 800);
	go_for(-100, -100, 100);

	go(0, 0); ao(); return 0;			// die -----------------------------------
	

	

	ao();
	return 0;
}
