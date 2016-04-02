int main()
{ 
	motor (0, 100);
	motor (2, 100);
	msleep (1000);
	
	motor (0, 100);
	motor (2,25);
	msleep (1000);
	
	motor (0, 100);
	motor (2, 100);
	msleep (1000);
	
	motor (0, 100);
	motor (2,25);
	msleep (1000);
	
	
	ao ();
	return 0;
}
