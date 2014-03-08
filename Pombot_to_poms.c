//This program asumes that the robot begins rear facing at the edge of the starting box.
//0 is object at top of screen; 140 is object at bottom of screen; 0 is left; 140 is right
//550 is back arm down - servo 1
//1000 is back arm up 
//850 is camera middle down - servo 2
//1200 is camera up
//750 is camera down
//1000 is camera middle up
//700 is claw open - servo 0
//350 is claw closed
//1650 is arm down - servo 3
//900 is arm up
#define CENTER 105
#define OPEN 0
#define CLOSE 1
#define UP 0
#define CENTER_UP 1
#define CENTER_DOWN 2
#define DOWN 3
int start_camera(void); //call to start camera
int verify(int checks,int range); //call when an accurate object is needed
point2 gcenter; //used for various get_object_center()'s
point2 gcenter2; //used for checking against gcenter
int arm(int up_down2); //sets front arm to either UP or DOWN
int claw(int open_close); //sets front claw to either OPEN or CLOSE
int turn_180(void);
int go(int right_motor_v, int left_motor_v, int duration);//basic driving function for dead reckoning
int pos = 0;//pos is camera servo state 0 - 3, 0 high, 3 low

int set_back_servo(int up_down); //UP or DOWN

int wait_light(void); //not yet implemented

int set_camera_servo(int pos); //UP DOWN or CENTER

int main()
{
	arm(DOWN);
	claw(CLOSE);
	set_camera_servo(UP);
	start_camera();
	verify(5,2); //sets gcenter to the center of the largest green object
	while(1){
		camera_update();
		gcenter = get_object_center(0,0); //if nothing is seen sit still and look
		if(get_object_count(0) == 0){
			ao();
			verify(3,2);
		}
		if(gcenter.y < 70){ //0 is top of screen 140 is bottom - while the center of the object is above the center(70):
			if(pos == UP){ //if camera servo is up go fast
				if(gcenter.x > CENTER){ //left of center
					motor(0,60); //right motor 60%
					motor(2,100); //left motor 100%
				}
				if(gcenter.x <= CENTER){ //right of center
					motor(0,100);
					motor(2,60);
				}
			}
			if(pos == CENTER_UP){ //if camera servo upper middle go medium speed
				if(gcenter.x > CENTER){ //left
					motor(0,30);//turn right
					motor(2,70);
				}
				if(gcenter.x <= CENTER){ //right
					motor(0,70);//turn left
					motor(2,30);
				}
			}
			else{ //includes camera pos lower middle and down go slow
				if(gcenter.x > CENTER){
					motor(0,10);
					motor(2,50);
				}
				if(gcenter.x <= CENTER){
					motor(0,50);
					motor(2,10);
				}
			}
			/*if(gcenter.x >= 7 && gcenter.x <= 80){
				motor(0,30);
				motor(2,30);
			}*/
		}
		if(gcenter.y >= 70){//this moves the camera angle down if the object is below the middle of the screen
			ao();
			verify(5,2); //make sure of the center of the object
			if(gcenter.y >= 70){//if still below center:
				if(pos != DOWN){//if camera isn't all the way down go down 1 step
					pos++;
					set_camera_servo(pos);
				}
				verify(3,2);
				if (pos == DOWN){//if camera is all the way down, finish the go to green loop
					break;
				}
			}
		}
		//msleep(50);
	}
	set_back_servo(UP);//pick up cage
	turn_180();
	set_back_servo(DOWN); //drops cage on poms
	go(100,100,1000); //should be replaced with a non dead reckoning method to reach other side
	
	//verify(5,2);
	/*arm(UP);
	motor(0,30);
	motor(2,20);
	msleep(600);
	ao();
	claw(OPEN);
	arm(DOWN);
	claw(CLOSE);
	arm(UP);*/
	
	/*while(1){
		set_camera_servo(UP);
		set_camera_servo(DOWN);
		set_camera_servo(CENTER);
		set_camera_servo(DOWN);
		
	//set_back_servo(UP);
	//set_back_servo(DOWN);
	}
	//go(-500,-500,300);*/
	
}
int turn_180(void){//to be calibrated
	motor(0,60);
	motor(2,-60);
	msleep(1200);
	ao();
}
/*functions set_back_servo, set_camera_servo, arm, and claw all work on the same principle - check the current position, if the inputted position if above that, go up, if the position is below, go up*/
int set_back_servo(int up_down)
{ 
	int tick1 = 0;
	enable_servo(1);
	while(1){
		tick1 = get_servo_position(1);
		if((tick1 <= 450 && up_down == DOWN) || (tick1 >= 1150 && up_down == UP)) {
			break;
		}
		if(up_down == UP){
			tick1 = tick1 + 10;
		}
		else{
			tick1 = tick1 - 10;
		}
		set_servo_position(1,tick1);
		msleep(10);
	}
	msleep(200);
}
int set_camera_servo(int pos)
{
	int tick2 = 0;
	enable_servo(2);
	while(1){
		tick2 = get_servo_position(2);
		if((pos == DOWN && tick2 <= 750) || (pos == UP && tick2 >= 1200) || (pos == CENTER_DOWN && (tick2 < 856 && tick2 > 844)) || (pos == CENTER_UP && (tick2 < 1006 && tick2 > 994))){
		break;
		}
		if((pos == UP && tick2 < 1200) || (pos == CENTER_DOWN && tick2 < 844) || (pos == CENTER_UP && tick2 < 994)) {
			tick2 = tick2 + 10;
		}
		if((pos == DOWN && tick2 > 750) || (pos == CENTER_DOWN && tick2 > 856) || (pos == CENTER_UP && tick2 > 1006)) {
			tick2 = tick2 - 10;
		}
		set_servo_position(2,tick2);
		msleep(10);
	}
	msleep(200);
	return pos;
	//disable_servo(2);
}	

int arm(int up_down2)
{ 
	int tick3 = 0;
	enable_servo(3);
	while(1){
		tick3 = get_servo_position(3);
		if((tick3 <= 900 && up_down2 == UP) || (tick3 >= 1650 && up_down2 == DOWN)) {
			break;
		}
		if(up_down2 == UP){
			tick3 = tick3 - 10;
		}
		else{
			tick3 = tick3 + 10;
		}
		set_servo_position(3,tick3);
		msleep(10);
	}
	msleep(200);
}
int claw(int open_close)
{ 
	int tick4 = 0;
	enable_servo(0);
	while(1){
		tick4 = get_servo_position(0);
		if((tick4 <= 350 && open_close == CLOSE)|| (tick4 >= 700 && open_close == OPEN)) {
			break;
		}
		if(open_close == OPEN){
			tick4 = tick4 + 10;
		}
		else{
			tick4 = tick4 - 10;
		}
		set_servo_position(0,tick4);
		msleep(10);
	}
	msleep(200);
}
int start_camera(void)
{
	camera_open();
	camera_update();
	msleep(300);
}
int verify(int checks,int range)
{
	camera_update();
	int first_check = 1;
	int counter1 = checks; //counter1 changes, checks stays to keep track of what the originial input was
	while(counter1 > 0){
		if(first_check == 1){//sets and prints initial gcenter, only enters this once per verify call
			gcenter = get_object_center(0,0);
			first_check = 0;
			printf("Program beginning - intitial object center at %d and %d\n",gcenter.x,gcenter.y);
		}
		msleep(100);
		camera_update();
		gcenter2 = get_object_center(0,0);//it sets gcenter2 to what it sees every iteration then checks if gcenter is within range of it
		if(gcenter.x >= (gcenter2.x - range) && gcenter.x <= (gcenter2.x + range)  && gcenter.y >= (gcenter2.y - range) && gcenter.y <= (gcenter2.y + range)){
			counter1--;//if gcenter2 is within the range of gcenter, tick one down
			printf("There are %d remaining checks\n",counter1);
		}
		else{//if it isn't within the range, reset counter1 to checks
			gcenter = get_object_center(0,0);
			counter1 = checks;
			printf("Different object - Counter reset\n");
		}
		camera_update();
		if(get_object_count(0) == 0){//this should probably have a separate counter, and if it reaches three, it makes the bot move a bit. as it is, it just resets if it doesn't see anything
			gcenter = get_object_center(0,0);
			counter1 = checks;
			printf("No objects - Counter reset\n");
		}		
	}
	if(counter1 == 0){ //if the counter has reached 0 print the final x and y coords
		camera_update();
		gcenter = get_object_center(0,0);
		printf("X-coord is at %d, Y-coord is at %d\n",gcenter.x,gcenter.y);
	}
}
		
int go(int right_motor_v, int left_motor_v, int duration)
{
	//calls function drive with parameters speed of right motor, speed of left motor, length of drive
	mav(0,right_motor_v);
	mav(2,left_motor_v);
	msleep(duration);
}
	


	
		
