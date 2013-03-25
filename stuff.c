int main()
{
	
create_connect();
create_drive_straight(343);
msleep(1);
create_spin_CW(195.3);
msleep(1);
create_drive_straight(355.6);
msleep(1);	
create_spin_CW(195.3);
msleep(1);
if(digital(10)){
create_drive_straight(-300);
msleep(10);
}
else{
	create_drive_straight(300);
}
//nap time
}
