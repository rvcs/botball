// Created on Thu March 27 2014

int main()
{
	int arm_pos = get_servo_position(0);
//	for (; arm_pos > 300; arm_pos -= 25) {
//		set_servo_position(0, arm_pos);
//		msleep(10);
//	}
	disable_servos();
	return 0;
}
