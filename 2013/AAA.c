//connor's program
int turn_right

int main()
{
	printf("starting connor\n");
	enable_servo(1);
	set_servo_position(1,100);
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
		create_drive_direct(150, 150);
		}
	disable_servos();
}

int turn_right(double seconds) 
	{
	int initial_angle = get_create_total_angle(0);
	create_drive_direct(300,-300);
	msleep(seconds*1);
	create_stop();
	return(get_create_total_angle(0) - initial_angle);
	}
