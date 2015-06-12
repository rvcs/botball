// Created on Mon March 16 2015
#if 1
#define ARM_DOWN    470
#define ARM_DOWNIS H 550
#define ARM_UP_PEG  1706
#define ARM_UP	    1977

#else
#define ARM_DOWN    450
#define ARM_DOWNISH 633
#define ARM_UP_PEG  1706
#define ARM_UP	    1977
#endif

void turn_right()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(0);
	mtp(0, 1500, 1300);
	block_motor_done(0);

}
void turn_left()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(2);
	mtp(2, 1500, 1300);
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
	msleep(msec);
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
	
//goto	GO_DOWN_CAVE;
	
	
	wait_for_light(2); // change the port number to match where your robot 

	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds
	// note that shut_down_in should immediately follow wait_for_light!!

	printf("My program should score more points than this template!\n");
	// replace printf above with your code

	//create_disconnect();
	// Created on Mon March 2 2015
	int a1;
	int a2;
//turn on robot	
	motor(0,-700);
	motor(2,-700);
	msleep(700);
#if 0
//go forward	
	motor(0,400);
	motor(2,400); 
	msleep(1000);
//turn to aline 
	motor(0, -100);
	motor(2, 100);
	msleep(500);
//aline robot	
	motor(0,-100);
	motor(2,-100);
	msleep(2000);
	go(0, 0);
	msleep(1500);
#else
//go forward	
	motor(0,400);
	motor(2,400);
	msleep(400);
//turn to aline 
	motor(0,0);
	motor(2,200);
	msleep(1300);
//aline robot	
	motor(0,-100);
	motor(2,-100);
	msleep(2000);
#endif
//	ao(); return 0;

	
	  //go forwad 
	motor(0,85);
	motor(2,85);
	//msleep(6000);
	printf("before 3000 delay\n");
	msleep (2600);
	set_servo_position(3, ARM_UP_PEG);
	printf("after 3000 delay\n");
	msleep(400);
	printf("%d\n",analog(1));
	start=seconds ();

	while ((a1 = analog(1)) <500) {
	//	printf("%d\n",a1);
		//msleep(5);
		if(seconds()-start>3.5){
		printf("time_out\n");
			break;
		}
	}
	printf("Found black %d\n", a1);

	//turn to go into middle
	turn_right();
	
		
//go forward	
	motor(0,60);
	motor(2,60);
	printf("go forward\n");
	//msleep(2000);
	while ((a1 = analog(1)) <600 || (a2 = analog(3)) <600) {
	//	printf("%4d %4d\n",a1, a2);
		//msleep(5);
		if (seconds()-start >10.5) {
			break;
		}
	}
	printf("%4d %4d\n",a1, a2);

	//turn in cave
	motor(0,0);
	motor(2,0);
	turn_right();
	
	set_servo_position(3, ARM_UP);
	//go to pick up cubes
	//motor(0,75);
	//motor(2,0);
	printf("turn right\n");
	//msleep(1500);
	
	
	//line follow
	start=seconds ();
	while(1){
		if(seconds()-start>4.9){
			break;
		}
		if (analog(1)>500) {
			motor(0,80);
			motor(2,100);
		}else if (analog(3)>500) {
			motor(0,100);
			motor(2,80);
		}else {
			motor(0,100);
			motor(2,100);
		}
	}
	
	//motor(0,85);
	//motor(2,85);
	//msleep(5500);
//put arm downto grab

GO_DOWN_CAVE:	
	go(0,0);
	set_servo_position(3, ARM_DOWN);	
	msleep(500);
	
	//begining of picking up poms
	
	go(75,75);
	msleep(2500);
	
	go_for(-50,-90, 1000);		// back up/turn/pull pom-poms
	
	go_for(90, -90, 500);
	
	go_for(-100, -90, 600);
	
	set_servo_position(3, ARM_UP);
	
	go_for(100, 100, 2000);
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 150);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100);	

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
	msleep(250); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250);
	
	// Raise the arm
	set_servo_position(3, ARM_UP);
	msleep(300);
	
	go_for(0, -100, 1000);
	
	//line follow
	start=seconds ();
	while(1){
		if(seconds()-start>1.5){
			break;
		}
		if (analog(1)>500) {
			motor(0,50);
			motor(2,80);
		}else if (analog(3)>500) {
			motor(0,80);
			motor(2,50);
		}else {
			motor(0,80);   //why is this 60 and 80
			motor(2,60);
		}
	}
		//line follow
	start=seconds ();
	while(1){
		if(seconds()-start>9.1){
			break;
		}
		if (analog(1)>500) {
			motor(0,80);
			motor(2,100);
		}else if (analog(3)>500) {
			motor(0,100);
			motor(2,80);
		}else {
			motor(0,100);
			motor(2,100);
		}
	}
	
	set_servo_position(3,ARM_DOWN);
	go_for(100, 100, 3500);			// Ram into PVC at the end of the cave
	
#if 1
	go_for(-50, -90, 1000);		// Back up with poms
	go_for(90, -90, 1000);
	set_servo_position(3, ARM_DOWNISH);
	
	// TODO: Run back across the cave to the good end
	start=seconds ();
	while(1){
		if(seconds()-start>1.5){
			break;
		}
		if (analog(1)>500) {
			motor(0,50);
			motor(2,80);
		}else if (analog(3)>500) {
			motor(0,80);
			motor(2,50);
		}else {
			motor(0,80);   //why is this 60 and 80
			motor(2,60);
		}
	}
	start=seconds ();
	while(1){
		if(seconds()-start>8){
			break;
		}
		if (analog(1)>500) {
			motor(0,80);
			motor(2,100);
		}else if (analog(3)>500) {
			motor(0,100);
			motor(2,80);
		}else {
			motor(0,100);
			motor(2,100);
		}
	}
	set_servo_position(3, ARM_DOWN);
	go(75,75);
	msleep(2500);
	
	go_for(-50,-90, 1000);		// back up/turn/pull pom-poms
	
	go_for(90, -90, 500);
	
	go_for(-100, -90, 600);
	
	set_servo_position(3, ARM_UP);
	
	go_for(100, 100, 2000);
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 150);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100);	

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
	msleep(250); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250);
	//backs up to push poms second timeb
	set_servo_position(3, ARM_UP);
	go_for(-100, -100,2000);
//push poms second time
	go_for(100, 100, 2000);
	
	go_for(-100, -100,2000);
	
	set_servo_position(3, ARM_DOWN);
	msleep(700);
	
	go_for(100,100,1000);
	
	go(-10, -10);
	set_servo_position(3, ARM_DOWN);
	msleep(100);
	
	set_servo_position(3, ARM_DOWN + 50);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 100);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 150);
	msleep(100);	

	set_servo_position(3, ARM_DOWN + 200);
	msleep(100);	

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
	msleep(250); 
	set_servo_position(3, ARM_DOWN+300);
	msleep(250);
	set_servo_position(3, ARM_DOWN+350);
	msleep(250);

	//motor(0,-75);
	//motor(2,-75);
	//msleep(8500);
	
//turn_left();
	
	//go_for(100, 100, 1800);
	//turn_left();
	//go_for(100, 100, 5000);
	
#endif 

	ao();
	return 0;
}
