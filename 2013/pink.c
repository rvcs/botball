// Created on Mon March 18 2013
//this wil be the code for moving and picking up  the  booster sections
#include <stdio.h>
#define STARTINGPOSITION -280
#define UPPOSITION -1000
#define OPEN_POSITION 235
#define CLOSE_POSITION_FOR_BOOSTER_SECTIONS 1858
int find_item ();
int main()
{
	int stupid_int = 0;	
	int value = 0;
	int i = 0;
	int angle_of_pole = 90;
	camera_open(LOW_RES);
	camera_update();
	create_connect();	

	
	set_create_total_angle(0);
	value = get_create_total_angle();
	printf("Angle is %d\n", value);
	//------------------------
// part 1: spin until past all booster sections
	
	while(get_create_total_angle() > -85){
		create_spin_CW(75);
	}
	
	//---------------------
	//end part 1
	camera_update();
	sleep(2);
	point2 mcenter = get_object_center(1,0);
	set_servo_position(0,OPEN_POSITION); //this is opening the claw so it won't go to a random position when enabling the servos
	enable_servos();
//--------------------------------------
// part 2: find booster section using function i wrote at bottom of code then line up with B2(pole)
	
	find_item();
	printf("I saw a booster section!\n");
	while(digital(10) == 0) {	
		create_drive_straight(-50);
		if(digital(10) == 1){
			create_stop();
		}
	}
		
		while(stupid_int == 0) {
			if (digital(10) == 1){
					set_servo_position(0,CLOSE_POSITION_FOR_BOOSTER_SECTIONS);	
					stupid_int == 1;
					msleep(200);
				printf("I have grabbed a booster section!\n");
			}
		}
		move_to_position(0, -900, UPPOSITION);
		set_create_total_angle(0);
	while(get_create_total_angle() < angle_of_pole){
		create_spin_CCW(75);
	}
	
	//---------------------
	//end part 2
	
	set_create_total_angle(0);
// part 3: go forward until i find B2 (not complete)
	
	set_servo_position(1,OPEN_POSITION); 
	angle_of_pole = 60;
//end part 3
	
	//part 4: repeat everything
	/*while(get_create_total_angle() > -80){
		create_spin_CW(75);
	}
	
	//---------------------
	//end part 1
	camera_update();
	sleep(2);
	point2 mcenter = get_object_center(0,0);
	set_servo_position(0,OPEN_POSITION); //this is opening the claw so it won't go to a random position when enabling the servos
//--------------------------------------
// part 2: find booster section using function i wrote at bottom of code then line up with B2(pole)
	
	find_item();
	printf("I saw a booster section!\n");
	while(digital(10) == 0) {	
		create_drive_straight(-50);
		if(digital(10) == 1){
			create_stop();
		}
	}
		
		while(stupid_int == 0) {
			if (digital(10) == 1){
					set_servo_position(0,CLOSE_POSITION_FOR_BOOSTER_SECTIONS);	
					stupid_int == 1;
					msleep(200);
				printf("I have grabbed a booster section!\n");
			}
		}
		move_to_position(0, -900, UPPOSITION);
		set_create_total_angle(0);
	while(get_create_total_angle() < angle_of_pole){
		create_spin_CCW(75);
	}
	
	//---------------------
	//end part 2
	
	set_create_total_angle(0);
// part 3: go forward until i find B2 (not complete)
	
	set_servo_position(1,OPEN_POSITION); 
	angle_of pole = 50;
//end part 3
	while(get_create_total_angle() > -70){
		create_spin_CW(75);
	}
	
	//---------------------
	//end part 1
	camera_update();
	sleep(2);
	point2 mcenter = get_object_center(0,0);
	set_servo_position(0,OPEN_POSITION); //this is opening the claw so it won't go to a random position when enabling the servos
//--------------------------------------
// part 2: find booster section using function i wrote at bottom of code then line up with B2(pole)
	
	find_item();
	printf("I saw a booster section!\n");
	while(digital(10) == 0) {	
		create_drive_straight(-50);
		if(digital(10) == 1){
			create_stop();
		}
	}
		
		while(stupid_int == 0) {
			if (digital(10) == 1){
					set_servo_position(0,CLOSE_POSITION_FOR_BOOSTER_SECTIONS);	
					stupid_int == 1;
					msleep(200);
				printf("I have grabbed a booster section!\n");
			}
		}
		move_to_position(0, -900, UPPOSITION);
		set_create_total_angle(0);
	while(get_create_total_angle() < angle_of_pole){
		create_spin_CCW(75);
	}
	
	//---------------------
	//end part 2
	
	set_create_total_angle(0);
// part 3: go forward until i find B2 (not complete)
	
	set_servo_position(1,OPEN_POSITION); 
	angle_of pole = 50;
//end part 3
	while(get_create_total_angle() > -100){
		create_spin_CW(75);
	}
	
	//---------------------
	//end part 1
	camera_update();
	sleep(2);
	point2 mcenter = get_object_center(0,0);
	set_servo_position(0,OPEN_POSITION); //this is opening the claw so it won't go to a random position when enabling the servos
//--------------------------------------
// part 2: find booster section using function i wrote at bottom of code then line up with B2(pole)
	
	find_item();
	printf("I saw a booster section!\n");
	while(digital(10) == 0) {	
		create_drive_straight(-50);
		if(digital(10) == 1){
			create_stop();
		}
	}
		
		while(stupid_int == 0) {
			if (digital(10) == 1){
					set_servo_position(0,CLOSE_POSITION_FOR_BOOSTER_SECTIONS);	
					stupid_int == 1;
					msleep(200);
				printf("I have grabbed a booster section!\n");
			}
		}
		move_to_position(0, -900, UPPOSITION);
		set_create_total_angle(0);
	while(get_create_total_angle() < angle_of_pole){
		create_spin_CCW(75);
	}
	
	//---------------------
	//end part 2
	
	set_create_total_angle(0);
// part 3: go forward until i find B2 (not complete)
	
	set_servo_position(1,OPEN_POSITION); 
	angle_of pole = 40;
//end part 3
	while(get_create_total_angle() > -60){
		create_spin_CW(75);
	}
	
	//---------------------
	//end part 1
	camera_update();
	sleep(2);
	point2 mcenter = get_object_center(0,0);
	set_servo_position(0,OPEN_POSITION); //this is opening the claw so it won't go to a random position when enabling the servos
//--------------------------------------
// part 2: find booster section using function i wrote at bottom of code then line up with B2(pole)
	
	find_item();
	printf("I saw a booster section!\n");
	while(digital(10) == 0) {	
		create_drive_straight(-50);
		if(digital(10) == 1){
			create_stop();
		}
	}
		
		while(stupid_int == 0) {
			if (digital(10) == 1){
					set_servo_position(0,CLOSE_POSITION_FOR_BOOSTER_SECTIONS);	
					stupid_int == 1;
					msleep(200);
				printf("I have grabbed a booster section!\n");
			}
		}
		move_to_position(0, -900, UPPOSITION);
		set_create_total_angle(0);
	while(get_create_total_angle() < angle_of_pole){
		create_spin_CCW(75);
	}
	
	//---------------------
	//end part 2
	
	set_create_total_angle(0);
// part 3: go forward until i find B2 (not complete)
	
	set_servo_position(1,OPEN_POSITION); 
	angle_of pole = 60;
//end part 3*/
//end part 4
}

int find_item()
{
	camera_update();
	point2 mcenter = get_object_center(1,0);
	set_servo_position (0 ,400);
	while(get_object_count(1) == 0){
		camera_update();
		create_spin_CCW(25);
	}
	create_stop();
	sleep(1);
	create_spin_CW(15);
	msleep(100);
	while(mcenter.x < 70 || mcenter.x > 100){
		camera_update();
		mcenter = get_object_center(1,0);
		if(mcenter.x < 70){
			create_spin_CCW(15);
			camera_update();
			mcenter = get_object_center(1,0);
		}
		if(mcenter.x < 100){
			create_spin_CW(15);
			camera_update();
			mcenter = get_object_center(1,0);
		}
		if(mcenter.x > 70 && mcenter.x < 100){
			create_stop();
		}
	}
	beep();
	
}
