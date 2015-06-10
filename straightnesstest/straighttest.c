// Created on Wed March 18 2015

void go(int left, int right)
{
	printf("l: %d r: %d\n", left, right);
	motor(0, left);
	motor(2, right);
}

int main()
{
	go(100, 90);
	msleep(5000);
	ao();
}
