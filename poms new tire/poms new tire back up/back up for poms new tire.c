// Created on Mon March 16 2015
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
	block_motor_done(0);

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
	
	
//goto START_DOWN_CAVE;
	
//lights
#if 0
	wait_for_light(2); // change the port number to match where your robot 

	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds
	// note that shut_down_in should immediately follow wait_for_light!!

	printf("My program should score more points than this template!\n");
	// replace printf above with your code
#else 
	//create_disconnect();
	// Created on Mon March 2 2015
	int a1;
	int a2;
//turn on robot	
	motor(0,-700);
	motor(2,-700);
	msleep(750 * factor);
#if 0
//go forward	
	motor(0,400);
	motor(2,400); 
	msleep(1000 * factor);
//turn to aline 
	motor(0, -100);
	motor(2, 100);
	msleep(500 * factor);
//aline robot	
	motor(0,-100);
	motor(2,-100);
	msleep(2000 * factor);
	go(0, 0);
	msleep(1500 * factor);
#endif
//go forward	
	motor(0,400);
	motor(2,400);
	msleep(200 * factor);
//turn to aline 
	motor(0,0);
	motor(2,200);
	msleep(1100 * factor); //changed from 1300
//aline robot	
	motor(0,-100);
	motor(2,-100);
	msleep(2500 * factor);
	go_for(0, 0, 2000);
	
	printf("hello people!! Lets win gold!");
#endif
//	ao(); return 0;

	start=seconds ();
	  //go forwad 
	motor(0,90);
	motor(2,85);  //tweek if wheel goes sideways (was 77 6/11)
	//msleep(6000);
	printf("before 3000 delay\n");
	msleep (2600 * factor);
	
	//arm set
	//set_servo_position(3, ARM_UP_PEG);
	printf("after 3000 delay\n");
	msleep(1500 * factor);
	printf("%d\n",analog(1));
	

	while ((a1 = analog(1)) <500 && (a2 = analog(3)) <500) {
		printf("%5d %5d\n",a1,a2);
		//msleep(5);
		if(seconds()-start>6.5){
			printf("time_out\n");
			break;
		}
	}
	printf("Found black %d\n", a1);

	//turn to go into middle
	turn_right();
	
	printf("hello people!! Lets win gold!");
		
//go forward	
	motor(0,60 * factor);
	motor(2,55 * factor);
	printf("go forward\n");
	//msleep(2000);
	while ((a1 = analog(1)) <600 || (a2 = analog(3)) <600) {
		printf("looking_for_cave%5d %5d\n",a1,a2);
		//msleep(5);
		if (seconds()-start >10.5) {
			break;
		}
	}
	printf("Black tape: %4d %4d\n",a1, a2);

	//turn in cave
	motor(0,0);
	motor(2,0);
	turn_right_into_cave(); // this is where I changed
START_DOWN_CAVE:	
	set_servo_position(3, ARM_UP);
	//go to pick up cubes
	//motor(0,75);
	//motor(2,0);
	printf("turn right\n");
	//msleep(1500);
	
	
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
	
	//motor(0,85);
	//motor(2,85);
	//msleep(5500);
//put arm downto grab

//GO_DOWN_CAVE:	
	go(0,0);
	set_servo_position(3, ARM_DOWN);	
	msleep(500 * factor);
	
	printf("hello people!! Lets win gold!");
	
	//begining of picking up poms
	
	go(75,75);
	msleep(2000 * factor);
	
	printf("hello people!! Lets win gold!");
	
	// back up/turn/pull pom-poms
	
	go_for(-50,-90, 1000);	//change for a tighter turn when needed	
	
	go_for(90, -90, 500);
	
	go_for(-100, -90, 600);
	
	set_servo_position(3, ARM_UP);
	
	go_for(90, 75, 2000); //change when ramming poms is not strait
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700 * factor);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100 * factor);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 150);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100* factor);	

	//set_servo_position(3, ARM_DOWN + 250);
	//msleep(100);	

	//set_servo_position(3, ARM_DOWN + 400);
	//msleep(100);
	//push the poms over the top of the PVC
	go_for(20, 20, 1000);
	//StOp
	go(0,0);
    //wiggle the arm up and down so the poms fall off
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250 * factor);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor);
	
	printf("hello people!! Lets win gold!");
	// Raise the arm
	set_servo_position(3, ARM_UP);
	msleep(300 * factor);
	
	go_for(0, -100, 1000);
	
	//line follow
	start=seconds ();
	while(1){
		if(seconds()-start>1.5){
			break;
		}
		if (analog(1)>500) {
			motor(0,50 * factor);
			motor(2,80 * factor);
		}else if (analog(3)>500) {
			motor(0,80 * factor);
			motor(2,50 * factor);
		}else {
			motor(0,80 * factor);   //why is this 60 and 80
			motor(2,60 * factor);
		}
	}
		//line follow
	start=seconds ();
	while(1){
		if(seconds()-start>6.1){ //9.1 1/6/16 //were here before alee had some harmless fun #printf
			break;
		}
		if (analog(1)>500) {
			motor(0,80 * factor );
			motor(2,100 * factor);
		}else if (analog(3)>500) {
			motor(0,100 * factor);
			motor(2,80 * factor);
		}else {
			motor(0,100 * factor);
			motor(2,100 * factor);
		}
	}
	
	set_servo_position(3,ARM_DOWN);
	go_for(100, 100, 3500);			// Ram into PVC at the end of the cave 
	
#if 1
	go_for(-50, -80, 1000);		// Back up with poms //(-50, -90, 1000)
	go_for(90, -90, 1000);
	set_servo_position(3, ARM_DOWNISH);
	
	// TODO: Run back across the cave to the good end
	start=seconds ();
	while(1){
		if(seconds()-start>1.5){
			break;
		}
		if (analog(1)>500) {
			motor(0,50 * factor);
			motor(2,80 * factor);
		}else if (analog(3)>500) {
			motor(0,80 * factor);
			motor(2,50 * factor);
		}else {
			motor(0,80 * factor);   //why is this 60 and 80
			motor(2,60 * factor);
		}
	}
	start=seconds ();
	while(1){
		if(seconds()-start>8.5){ // change from 8 sec
			break;
		}
		if (analog(1)>500) {
			motor(0,80 * factor);
			motor(2,100 * factor);
		}else if (analog(3)>500) {
			motor(0,100 * factor);
			motor(2,80 * factor);
		}else {
			motor(0,100 * factor);
			motor(2,100 * factor);
		}
	}
	set_servo_position(3, ARM_DOWN);
	go(75,75);
	msleep(2500 * factor);
	
	go_for(-50,-90, 1000);		// back up/turn/pull pom-poms
	
	go_for(90, -90, 500);
	
	go_for(-100, -90, 600);
	
	set_servo_position(3, ARM_UP);
	
	go_for(100, 100, 2000);
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700 * factor);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100 * factor);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100 * factor);	
	
	set_servo_position(3, ARM_DOWN + 150);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100 * factor);	

	//set_servo_position(3, ARM_DOWN + 250);
	//msleep(100);	

	//set_servo_position(3, ARM_DOWN + 400);
	//msleep(100);
	//push the poms over the top of the PVC
	go_for(20, 20, 1000);
	//StOp
	go(0,0);
    //wiggle the arm up and down so the poms fall off
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250 * factor);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor);
	//backs up to push poms second timeb
	set_servo_position(3, ARM_UP);
	go_for(-100, -100,2000);
//push poms second time
	go_for(100, 100, 2000);
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700 * factor);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100 * factor);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 150);
	msleep(100 * factor);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100 * factor);	

	//set_servo_position(3, ARM_DOWN + 250);
	//msleep(100);	

	//set_servo_position(3, ARM_DOWN + 400);
	//msleep(100);
	//push the poms over the top of the PVC
	go_for(20, 20, 1000);
	//StOp
	go(0,0);
    //wiggle the arm up and down so the poms fall off
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250 * factor);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250 * factor);

	//motor(0,-75);
	//motor(2,-75);
	//msleep(8500);
	
//turn_left();
	
	//go_for(100, 100, 1800);
	//turn_left();
	//go_for(100, 100, 5000);
	
#endif 

printf("hello people!! Lets win gold!");
	ao();
	return 0;
}
