// Created on Sat January 17 2015

void forward();
void right();

int main()
{
	printf("Hello, World!\n");
	msleep(2500);
	printf("Botguy\n");
	forward();
	right();
	forward();
	right();
	forward();
	right();
	forward();
	return 0;
}

void forward()
{
	motor(0, 100);
	motor(1, 100);
	msleep(500);
	ao();
}

void right()
{
	motor(1, 100);
	msleep(500);
	ao();
}
