// Created on Fri March 8 2013

int main()
{
	printf("Tryying to connect to the Create\nBattery: %d...\n", get_create_battery_capacity());
	create_connect();
	printf("Connected...");
	while (get_create_lbump() == 0 && get_create_rbump() == 0)
	{
		create_drive_direct(150,150);
	}
	create_disconnect();
	printf("All done");
	return 0;
}
