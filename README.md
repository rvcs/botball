botball
=======

Botball team code

char opcodes[1024];
char * opcodes_tail = NULL; //creates system to avoid having to count bytes

void write_byte(b)
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
	short distance1 = -500; 
	short distance2 = -400;
	short distance3 = -550;
	short speed1 = -300; //Variable 'speed1' equal to value
	short speed2 = 300;
	short angle1 = 90;
	short angle2 = -90;
	opcodes_tail = opcodes;
	
	printf("Hello, World!\n");
	create_connect();
	msleep(2000);
	printf("Connected\n");
	write_byte(158); //wait for:
	write_byte(5); //front bumb 1 byte
	write_byte(145); //go forward mm/s
	write_byte(speed1>>8); // -256 mm/s 1 byte
	write_byte(speed1&0xff); //-44 mm/s + -256 mm/s = -300 mm/s right wheel 2 byte 
	//also can use 'speed' b/c >>8 makes value into 4 digit number and 0xff makes sure it sees that value as 4 digits so any number between 9999 and 0000 can equal speed1 and this will work
	write_byte(speed1>>8); //256 3 byte
	write_byte(speed1&0xff); //44 300 mm/s left wheel 4 byte
	write_byte(156); //count distance for:
	write_byte(distance1>>8); // same principle as for speed1
	write_byte(distance1&0xff);	// 2 byte
	write_byte(145);// spin CCW...
	write_byte(speed2>>8);
	write_byte(speed2&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(157); //...90 degrees
	write_byte(angle1>>8);
	write_byte(angle1&0xff);
	write_byte(145); //go forward...(backward)
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(156);//...250 mm
	write_byte(distance2>>8);
	write_byte(distance2&0xff);
	write_byte(145);//spin CW
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(speed2>>8);
	write_byte(speed2&0xff);
	write_byte(157);//for 90 degrees
	write_byte(angle2>>8);
	write_byte(angle2&0xff);
	write_byte(145); //go forward... (backward)
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(156); //until hung
	write_byte(distance3>>8);
	write_byte(distance3&0xff);
	write_byte(7); //reboot 1 byte
	create_write_byte(152); //writes script
	create_write_byte(num_bytes()); //# bytes total
	for( i = 0; i < num_bytes(); i++)
	{
		create_write_byte(opcodes[i]);
	}
	create_write_byte(153);//can make it one program instead of two
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
