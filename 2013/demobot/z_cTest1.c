int main()
{	printf("Drive Straight till bump\n"); // announce the program
	msleep(1000); // wait 1 second
	do
	{
		int left_dist = analog(0);
		int right_dist = analog(2);
		int front_dist = analog(1);
		if (left_dist<=200) 
			motor(0,85);
		if(right_dist<=200)
			motor(2,85);
		if(left_dist>=200)
			motor(0,65);
		if(right_dist>=200)
			motor(2,65);
		if(front_dist<=200)
		{
			motor(0,-100);
			motor(2,40);
		}
	}while (digital(9)==0 && digital(8)==0); // check bumpers
	
	while (digital(9)==0 && digital(8)==0) // check bumpers
	{
		motor(0,65); // Drive left wheel forward at 55% power
		motor(2,50); // Drive right motor forward at half power
	}
	while (digital(9)!=0 || digital(8)!=0) // check bumpers
	{
		motor(0,-65); // Drive left wheel forward at 55% power
		motor(2,-50); // Drive right motor forward at half power
	}

	
	ao(); // Stop motors
	printf("All Done\n"); // Tell user program has finished
	return 0;
}
