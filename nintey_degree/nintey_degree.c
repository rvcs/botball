float factor=0.9, factor2=0.85;

void turn_right()
{

	motor(0,0);
	motor(2,0);
	clear_motor_position_counter(0);
	mtp(0, 1500, 1220*factor2);
	block_motor_done(0);

}

int main()
{
	motor(0,-90);
	motor(2,-77);
	msleep(1000);
	motor(0,90);
	motor(2,77);
	msleep(3000);
	turn_right();
	ao();
	return 0;
}
