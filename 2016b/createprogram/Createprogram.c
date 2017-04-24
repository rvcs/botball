// Created on Sat March 14 2015

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
	short distance1 = -575; 
	short distance2 = -400;
	short distance3 = -900;
	short speed1 = -300; //Variable 'speed' equal to value
	short speed2 = 300;
	short speed3 = -200;
	short speed4 = 200;
	short speed5 = -250;
	short speed6 = 250;
	short angle1 = -125;
	short angle2 = 70;
	short angle3 = -20;
	opcodes_tail = opcodes;
	
	printf("BACON!\n");
	create_connect();
	msleep(2000);
	printf("Connected\n");
	
	write_byte(128); //the inital start command
	write_byte(131); //puts it in the "Safe" mode
	
	write_byte(158); //wait for:
	write_byte(7); //right bumb 1 byte
	
	write_byte(145);// spin
	write_byte(speed1>>8);
	write_byte(speed1&0xff);
	write_byte(speed2>>8);
	write_byte(speed2&0xff);

	write_byte(157); //wait for angle
	write_byte(angle1>>8);
	write_byte(angle1&0xff);

	write_byte(145); //go forward mm/s
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 

	write_byte(156); //count distance for [distance1]
	write_byte(distance1>>8); 
	write_byte(distance1&0xff);	
	
	write_byte(145);// spin to the left
	write_byte(speed4>>8);
	write_byte(speed4&0xff);
	write_byte(speed3>>8);
	write_byte(speed3&0xff);

	write_byte(157); 
	write_byte(angle2>>8);
	write_byte(angle2&0xff);
	
	write_byte(145); //go forward mm/s
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 

	write_byte(156); //count distance for [distance1]
	write_byte(distance3>>8); 
	write_byte(distance3&0xff);	
	
	write_byte(145);// spin to the right
	write_byte(speed5>>8);
	write_byte(speed5&0xff);
	write_byte(speed6>>8);
	write_byte(speed6&0xff);

	write_byte(157); 
	write_byte(angle3>>8);
	write_byte(angle3&0xff);
	
	write_byte(145); //go forward mm/s
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 
	write_byte(speed1>>8); 
	write_byte(speed1&0xff); 

	write_byte(156); //count distance for [distance2]
	write_byte(distance2>>8); 
	write_byte(distance2&0xff);	

	write_byte(7); //reboot 1 byte

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
