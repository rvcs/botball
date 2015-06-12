int main()
{
	motor(0,-90);
	motor(2,-77);
	msleep(1000);
	motor(0,90);
	motor(2,77);
	msleep(6000);
	ao();
	return 0;
}
