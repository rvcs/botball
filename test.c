
int main()
{
	printf("Trying to connect to Create...\n");
	create_connect(); // Program waits till it connects...
	printf("Connected. Drive straight until bumper hits\n");
	while (get_create_lbump() == 0 && get_create_rbump() == 0)
	{
		create_drive_direct(150, 150); // drive straight at 150mm/s
	}
	create_disconnect(); // stops communication
	printf("All Done\n"); // tell user program has finished
	return 0;
}
