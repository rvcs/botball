

int right_is_black()
{
  return analog(3) <500; //changed from >500
}

int left_is_white()
{
  return analog(1) >500; //changed from <500
}

int right_is_white()
{
  return analog(3) >500; //changed from <500
}

int main()
{
  //left wheel is: 2
  //right wheel is: 0
  
  //important for line follow
    double start = 0.0;
   int a1;
  int a2;
  float factor=0.9;
  
  // starting the robot
    printf("Hello World\n");
  
  //finding out if the "1" is left or right
  mav(0,1000);
  mav(2,1000);
  msleep (5000);
  
  //linefollow:
  //add in the line follow later, after we know wht wheel is what
  //dont forget the info at the beginning of the program
  //using the line follow from: CLOSE RAMP
  
  start=seconds ();
  while(1){
    a1 =analog (1);
    a2 =analog (3);
    printf("cave%5d %5d ",a1,a2);
    if(seconds()-start>8.5){ 
              //used to be 4.5 2/3/16 //was14 (keep comment)
      break;
    }
    
    if ((left_is_white() && right_is_white()) || (left_is_black() && right_is_black())) { 
              //a1=500 both // was if ((a1<400 && a2<500) || (a1>700 && a2>500)) (keep comment)
      mav(LEFT_MOTOR,1500 * factor); 
              //was 0,90 2/3/16 //was900 (keep comment)
      mav(RIGHT_MOTOR,1500 * factor); 
              //was 2,56 2/3/16 (keep comment)
      printf("straight\n");
    } else if (left_is_black()) { 
              //was else if (a1<500) 2/17/16 #LOL day (keep comment)
        // Turn left (keep comment)
      mav(LEFT_MOTOR,500 * factor); 
              //left is 0 right is 2 (keep comment)
      mav(RIGHT_MOTOR,900 * factor);
      printf("left\n");
    } else if (right_is_black()) {        
              //was just "}else {" (keep comment)
        //turn right (keep comment)
      mav(LEFT_MOTOR,900 * factor);
      mav(RIGHT_MOTOR,500 * factor); //750
      printf("right\n");
        }
    }
    ao();
    return 0;
}


