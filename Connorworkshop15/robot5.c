// Created on Sat January 17 2015

void forward(int power);
void right(int power);


int main()
{
	printf("Hello, World!\n");
	msleep(2500);
	printf("Botguy\n");
	forward(100);
	right(100);
	forward(100);
	right(100);
	forward(100);
	right(100);
	forward(100);
	return 0;
}

void forward(int power)
{
	motor(0, power);
	motor(1, power);
	msleep(500);
	ao();
	msleep(500);
}

void right(int power)
{
	motor(1, power);
	msleep(500);
	ao();
	msleep(500);
}
