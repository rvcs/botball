//connor's program

int main()
{
	printf("starting connor\n");
	enable_servo(1);
	set_servo_position(1,100);
	//disable_servo(1)
	create_connect(); 
	while (! digital(11))
	{
		printf("%d\n",  digital(11));
		create_drive_direct(-150,-150);
	}
	printf("starting connor\n");
	set_servo_position(1,1400);
	while (get_create_lbump() == 0 && get_create_rbump() == 0)
		{
		create_drive_direct(150, 150); // drive straight at 150mm/s
		}
	disable_servos();
}
