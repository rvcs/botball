// Created on Mon March 16 2015
int main()
{
	double start = 0.0;
	// initialize servo, camera, etc here?.
	// if you are using a Create you should uncomment the next line
	//create_connect();
	enable_servos ();
	set_servo_position(3,1706);
	
	
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
	msleep(1000);
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
	  //go forwad 
	motor(0,85);
	motor(2,85);
	//msleep(6000);
	printf("before 3000 delay\n");
	msleep (3000);
	printf("after 3000 delay\n");
	printf("%d\n",analog(1));
	while ((a1 = analog(1)) <500) {
		printf("%d\n",a1);
		msleep(5);
	}
	printf("Found black %d\n", a1);
	start=seconds ();
	//turn to gointo middle
	motor(0,80);
	motor(2,0);
	msleep(1250);
	
//go forward	
	motor(0,85);
	motor(2,85);
	printf("go forward\n");
	//msleep(2000);
	while ((a1 = analog(1)) <500 || (a2 = analog(3)) <500) {
		printf("%4d %4d\n",a1, a2);
		msleep(5);
		if (seconds()-start >7.0) {
			break;
		}
	}
	printf("%4d %4d\n",a1, a2);
	//go to pick up cubes
	//motor(0,75);
	//motor(2,0);
	printf("turn right\n");
	//msleep(1500);
	
	
	
	//motor(0,85);
	//motor(2,85);
	//msleep(5500);
//put arm downto grab
	set_servo_position(3,633);	
	msleep(1000);
	
	motor(0,-75);
	motor(2,-75);
	msleep(1000);
	ao();
	return 0;
}
