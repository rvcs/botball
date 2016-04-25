#include <kipr/botball.h>

#define CREATE_DRIVE_ARC		137
#define CREATE_DRIVE_DIRECT		145
#define CREATE_WAIT_SENSOR		142
#define CREATE_WAIT_TIME		155
#define CREATE_WAIT_DISTANCE	156
#define CREATE_WAIT_ANGLE		157
#define CREATE_WAIT_EVENT		158
#define CREATE_SCRIPT			152
#define PI						3.1415

//#define SPIN 157
//#define FORWARD 145
#define ARC 	157
#define DRIVE 	145
#define WAIT 	156
#define SONG	141
//#define DISTANCE 156
char opcodes[1024];
char * opcodes_tail = NULL; //creates system to avoid having to count bytes
void command(int drive,short speed1, short speed2, int wait, short distance);

void write_byte(int b)
{
  *opcodes_tail = b;
  opcodes_tail++;
}

int num_bytes()
{
  return opcodes_tail - opcodes;
}

int main()
{
	int i = 0;
	short speed1 = -300; //Variable 'speed' equal to value
	opcodes_tail = opcodes;

	create_connect();
	msleep(2000);
	printf("Connected\n");
	
	write_byte(128); //the inital start command
	write_byte(131); //puts it in the "Safe" mode
	
	write_byte(158); //wait for:
	write_byte(7); //right bumb 1 byte
	
	command(CREATE_DRIVE_DIRECT, 301, -267, CREATE_WAIT_DISTANCE, -2700);//movement begins 
  	//command(CREATE_DRIVE_DIRECT, 300, -300, CREATE_WAIT_DISTANCE, 50 );
  	command(CREATE_DRIVE_DIRECT, speed1,-295, CREATE_WAIT_DISTANCE, -2700);
	write_byte (7);//reboot 1 byte
	write_byte(173); 
	
	printf("total bytes: %d\n", num_bytes());

	msleep(500);
	//create_write_byte(152); //writes script
	//create_write_byte(num_bytes()); //# bytes total
	for( i = 0; i < num_bytes(); i++)
	{
		create_write_byte(opcodes[i]);
	}
	
	msleep(500);
	create_write_byte(153);//can make it one program instead of two
	msleep(2000);
	
	create_disconnect();
	printf("Done\n");
    return 0;
	
}
void command(int drive,short speed1, short speed2, int wait, short distance)
{
	write_byte(drive); //go forward mm/s
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 
	write_byte(speed2>>8); 
	write_byte(speed2&0xff);	
	
	write_byte(wait);//until distance1
	write_byte(distance>>8); 
	write_byte(distance&0xff);

}
