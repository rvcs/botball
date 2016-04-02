// Created on Wed February 3 2016

int main()
{
	// initialize servo, camera, etc here?.
	// if you are using a Create you should uncomment the next line
	//create_connect();

	wait_for_light(0); // change the port number to match where your robot 

	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds
	// note that shut_down_in should immediately follow wait_for_light!!

	printf("My program should score more points than this template!\n");
	// replace printf above with your code

	//create_disconnect();
	return 0;
}
