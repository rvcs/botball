int main()
{
	motor(0,-90);
	motor(2,-60);
	msleep(1000);
	
	motor(0,90);
	motor(2,60);
	msleep(4000);
	ao();
	return 0;
}
