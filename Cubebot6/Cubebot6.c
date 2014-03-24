// Created on Sat March 15 2014

#if 0
int total_objects;
int object;
int objects_seen;
int cubes_seen;
int cubex = 0;
int cubey = 0;

//for camera purposes (0,0) is in the top left corner and (140,140) is the bottom right corner


point2 cubecenter1;
point2 cubecenter2;
int verify(int checks,int range); //vision verify
#endif

#define RIGHT_MOTOR 1
#define LEFT_MOTOR 0
#define ARM_UP 900
#define ARM 0
#define TOO_FAR_LEFT 55
#define TOO_FAR_RIGHT 85
#define CORRECT_HEIGHT 90
#define CLAW 1
#define CLAW_OPEN 700
#define CLAW_CLOSED 200

int main()
{
	int objseen = 0;
	int objcounter = 0;
	int lcube = 0;
	int rcube = 0;
	
	point2 cubecenter1;
	point2 cubecenter2;
	
	printf("Hello, World!\n");
	camera_open();
	camera_update();
	msleep(300);
	
	enable_servos();
	set_servo_position(ARM, ARM_UP);
	msleep(500);
	mav(RIGHT_MOTOR, 500);
	mav(LEFT_MOTOR, 500);
	msleep(1000);
	

	objseen = get_object_count(0);
	/*objcounter = objseen;
	while(objcounter != 0)
	{
		get_object_center(0, objcounter);
		objcounter--;
	)
	*/
	
	cubecenter1 = get_object_center(0,0);
	
	cubecenter2 = get_object_center(0,1);
	
	if(cubecenter1.x > cubecenter2.x)
	{
		rcube = cubecenter1.x;
		lcube = cubecenter2.x;
	}
	else 
	{
		lcube = cubecenter1.x;
		rcube = cubecenter2.x;
	}
	
	while(cubecenter1.y <= CORRECT_HEIGHT)
	{
		camera_update();
		
		cubecenter1 = get_object_center(0,0);
		
		if(cubecenter1.x >= TOO_FAR_LEFT && cubecenter1.x <= TOO_FAR_RIGHT)
		{
			mav(RIGHT_MOTOR, 600);
			mav(LEFT_MOTOR, 600);
			
		}
		if(cubecenter1.x <= TOO_FAR_LEFT)
		{
			
			mav(RIGHT_MOTOR, 700);
			mav(LEFT_MOTOR, 300);
			
		}
		if(cubecenter1.x >= TOO_FAR_RIGHT)
		{
			
			mav(RIGHT_MOTOR, 300);
			mav(LEFT_MOTOR, 700);
			
		}
		//add cube pick up program
		//bring cube to cup
		//turn around
		//grab second cube
		//bring it back to the cup
		//celebrate!
		
	}
	
	set_servo_position(CLAW, CLAW_OPEN);
	
	
	

}

#if 0
int verify(int checks,int range)
{
	camera_update();
	int first_check = 1;
	int nothing_seen = 0;
	int obj_count = 0;
	int counter1 = checks; //counter1 changes, checks stays to keep track of what the originial input was
	while(counter1 > 0){
		if(first_check == 1){//sets and prints initial gcenter, only enters this once per verify call
			gcenter = get_object_center(0,1);
			first_check = 0;
			printf("Program beginning - intitial object center at %d and %d\n",gcenter.x,gcenter.y);
		}
		msleep(100);
		camera_update();
		gcenter2 = get_object_center(0,1);//it sets gcenter2 to what it sees every iteration then checks if gcenter is within range of it
		if(gcenter.x >= (gcenter2.x - range) && gcenter.x <= (gcenter2.x + range)  && gcenter.y >= (gcenter2.y - range) && gcenter.y <= (gcenter2.y + range)){
			counter1--;//if gcenter2 is within the range of gcenter, tick one down
			printf("There are %d remaining checks\n",counter1);
		}
		else{//if it isn't within the range, reset counter1 to checks
			gcenter = get_object_center(0,1);
			counter1 = checks;
			printf("Different object - Counter reset\n");
		}
		camera_update();
		if(get_object_count(0) == 0){//this should probably have a separate counter, and if it reaches three, it makes the bot move a bit. as it is, it just resets if it doesn't see anything
			msleep(200);
			camera_update();
			gcenter = get_object_center(0,1);
			counter1 = checks;	
			printf("No objects - Counter reset\n");
			if(get_object_count(0) == 0){
				nothing_seen++;
			}
		}	
		if(nothing_seen > 3){ //if it goes through 3 iterations and sees no objects jerk to one side, look, and if it doesn't see anything, jerk to the other side and look
			motor(0,50);
			motor(2,-50);
			msleep(200);
			ao();
			camera_update();
			msleep(100);
			if(get_object_count(0) == 0){
				motor(0,-50);
				motor(2,50);
				msleep(400);
				ao();
				camera_update();
				msleep(100);
			}
			nothing_seen = 0;
	}
	if(counter1 == 0){ //if the counter has reached 0 print the final x and y coords
		camera_update();
		gcenter = get_object_center(0,0);
		printf("X-coord is at %d, Y-coord is at %d\n",gcenter.x,gcenter.y);
	}
}
#endif
	
	

