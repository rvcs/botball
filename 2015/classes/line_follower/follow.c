// Created on Mon January 26 2015

// 0 - left
// 2 - right

void move(int left, int right);

int main()
{
	printf("Hello, World!\n");
	double stop_time = seconds() + 8.0;
		
	do {
		int blackness = analog(6);
		printf("%d\n", analog(6));
		if (blackness > 512) {
			move(10, 100);
		} else {
			move(100, 10);
		}
	} while (seconds() < stop_time);
	
	printf("Done\n");
	return 0;
}

void move(int left, int right)
{
	motor(0, left);
	motor(2, right);
}
