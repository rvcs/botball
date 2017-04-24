// Created on Wed January 27 2016



	
#if 1
#define ARM_DOWN    470
#define ARM_DOWNISH 550
#define ARM_UP_PEG  1706
#define ARM_UP	    1977

#else
#define ARM_DOWN    450
#define ARM_DOWNISH 633
#define ARM_UP_PEG  1706
#define ARM_UP	    1977
#endif
float factor=0.9, factor2=0.85;
void turn_right_into_cave()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(0);
	mtp(0, 1000, 950 ); 
	block
	_motor_done(0);

}
void turn_right()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(0);
	mtp(0, 1000, 850); // this is what got changed from 1050 to 950 to 850
	block_motor_done(0);

}
void turn_left()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(2);
	mtp(2, 1500, 1220*factor2);
	block_motor_done(2);

}

int go(int left, int right)
{
	motor(0, left);
	motor(2, right);
	return 1;
}
int go_for(int left,int right,int msec)
{
	go(left, right);
	msleep(msec * factor);
	return 1;
}

int main()
{
	double start = 0.0;
	// initialize servo, camera, etc here?.
	// if you are using a Create you should uncomment the next line
	//create_connect();
	enable_servos ();
	set_servo_position(3, ARM_UP);
	
	int a1;
	int a2;
//goto START_DOWN_CAVE;
	
//lights
#if 0
	wait_for_light(2); // change the port number to match where your robot 

	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds
	// note that shut_down_in should immediately follow wait_for_light!!

	printf("My program should score more points than this template!\n");
	// replace printf above with your code
#endif 
	//create_disconnect();
	
	
	
	
	//go forward to line follow
	motor(0,700);
	motor(2,700);
	msleep(1000);
	
	while ((a1 = analog(1)) <500 && (a2 = analog(3)) <500) {
		printf("%5d %5d\n",a1,a2);
		//msleep(5);
		if(seconds()-start>6.5){
			printf("time_out\n");
			break;
		}
	}
	printf("Found black %d\n", a1);

//
	//line follow
	start=seconds ();
	while(1){
		a1 =analog (1);
		a2 =analog (3);
		printf("cave%5d %5d\n",a1,a2);
		if(seconds()-start>4.5){
			break;
		}
		if ((a1<500 && a2<500) || (a1>500 && a2>500)) {
			motor(0,90 * factor);
			motor(2,56 * factor);
		} else if (a1<500) {
			motor(0,90 * 1.00 * factor);
			motor(2,75 * 0.80 * factor);
			
		}else {
			motor(0,90 * 0.80 * factor);
			motor(2,75 * 1.00 * factor);
		
		}
	}
	
	
	
	
	return 0;
}
