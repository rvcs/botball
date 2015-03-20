// Created on Thu March 19 2015
void turn_right()
{
	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(0);
	mtp(0, 1500, 1300);
	block_motor_done(0);

}
int main()
{
	printf("Hello, World!\n");
	
	turn_right();
	ao();
return 0;
}
