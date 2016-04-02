int main()
{
	motor(0,-100);
	motor(1,-85);
	msleep(1000);
	
	motor(0,100);
	motor(1,85); //changed from 56
	msleep(6000);
	ao();
	return 0;
}
