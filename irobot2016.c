

//#define SPIN 157
//#define FORWARD 145
#define ARC 	137
#define DRIVE 	145
#define WAIT 	156
//#define DISTANCE 156
char opcodes[1024];
char * opcodes_tail = NULL; //creates system to avoid having to count bytes

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
	short distance1 = -1500; 
	short distance2 = -400;
	short distance3 = -1530;
	short distance4 = -460;
	short distance5 = -1450;
	short distance6 = -100;
	short speed1 = -100; //Variable 'speed' equal to value
	short speed2 = -100;
	short angle1 = -70;
	short angle2 = -60;
	short angle3 = -20;
	short angle4 = -175;
	short angle5 = -90;
	opcodes_tail = opcodes;
	
	create_connect();
	msleep(2000);
	printf("Connected\n");
	
	write_byte(128); //the inital start command
	write_byte(131); //puts it in the "Safe" mode
	
	write_byte(158); //wait for:
	write_byte(7); //right bumb 1 byte
	
//movement begins
	write_byte(DRIVE); //go forward mm/s
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 
	write_byte(speed1>>8); 
	write_byte(speed1&0xff);	
	
	write_byte(WAIT);
	write_byte(distance1>>8); 
	write_byte(distance1&0xff);	
	
	goto END;
	
	write_byte(ARC); //left
	write_byte(angle1>>8);
	write_byte(angle1&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE);
	write_byte(speed1>>8);
	write_byte(speed1&0xff); 
	write_byte(speed1>>8); 
	write_byte(speed1&0xff);

	write_byte(WAIT);
	write_byte(distance2>>8);
	write_byte(distance2&0xff);
	
	write_byte(ARC); //spin right
	write_byte(angle2>>8);
	write_byte(angle2&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE);
	write_byte(speed1>>8);
	write_byte(speed1&0xff); 
	write_byte(distance2>>8); 
	write_byte(distance2&0xff);	
	
	write_byte(WAIT);
	write_byte(distance3>>8);
	write_byte(distance3&0xff);

	write_byte(ARC);//spin left
	write_byte(angle3>>8);
	write_byte(angle3&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE); //go forward mm/s
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(distance3>>8);
	write_byte(distance3&0xff);
	
	write_byte(ARC);//spin right
	write_byte(angle4>>8);
	write_byte(angle4&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE);//go foward mm/s
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(distance4>>8);
	write_byte(distance4&0xff);
	
	write_byte(ARC);//spin right
	write_byte(angle5>>8);
	write_byte(angle5&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE);//go forward mm/s
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(distance5>>8);
	write_byte(distance5&0xff);
	
	write_byte(ARC);//spin right
	write_byte(angle5>>8);
	write_byte(angle5&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	
	write_byte(DRIVE);//go forward
	write_byte(speed2>>8);
	write_byte(speed2&0xff);
	write_byte(distance6>>8);
	write_byte(distance6&0xff);
	
	END:
	
	write_byte(7); //reboot 1 byte
	
	printf("total bytes: %d\n", num_bytes());

	msleep(500);
	create_write_byte(152); //writes script
	create_write_byte(num_bytes()); //# bytes total
	for( i = 0; i < num_bytes(); i++)
	{
		create_write_byte(opcodes[i]);
	}
	
	msleep(500);
	create_write_byte(153);//can make it one program instead of two
	msleep(2000);
	/*for (i = 0; 1; i++)
	{
		printf("%d\n",get_create_distance());
		if (i>20){
			break;
		}
		msleep(500);
	}*/
	create_disconnect();
	printf("Done\n");
	
}

