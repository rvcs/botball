// Created on Wed January 28 2015

int main()
{
	printf("Hello, Potato!\n");
	
	motor(0, 100);
	motor(2, 100);
	msleep(2000);
	
	motor(0, 0);
	motor(2, 100);
	msleep(2000);
	
	motor(0, 100);
	motor(2, 100);
	msleep(2000);
	
	motor(0, 0);
	motor(2, 100);
	msleep(2000);
	
	ao();
	return 0;
}
