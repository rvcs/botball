// Created on Mon January 26 2015

// 0 - left
// 2 - right

#define REFLECTANCE_SKEW (0.3)
#define REFLECTANCE_BIAS (550)

void move(int left, int right);
int fuzzy(int port);

int main()
{
	printf("Hello, World!\n");
	double stop_time = seconds() + 8.0;
		
	do {
		int blackness = fuzzy(6);
		printf("%d\n", blackness);
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

int fuzzy(int port)
{
	int result = (float)(analog(port) * REFLECTANCE_SKEW) + REFLECTANCE_BIAS;
	
	if (result > 1023) { result = 1023; }
	if (result < 0)    { result = 0; }
	
	return result;
}
