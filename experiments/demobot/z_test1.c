// Created on Sat March 9 2013

/*******************************************************************
Drive the simulated robot forward at half power till it bumps
********************************************************************
*/
int main()
{
	printf("Drive Straight till bump\n"); // announce the program
	msleep(1000); // wait 1 second

	while (digital(9)==0 && digital(8)==0) // check bumpers
	{
		motor(0,60); // Drive left wheel forward at 55% power
		motor(2,68); // Drive right motor forward at half power
	}
	ao(); // Stop motors
	printf("All Done\n"); // Tell user program has finished
	return 0;
}




