// Created on Sun March 24 2013

void main ()
{
	int loop_done = 0;
	int task_A_done = 0;
	int task_B_done = 0;
	
	
	//put specific commands to control robot in here
	
	while(! loop_done)
	{
		if (/*task A is not done*/)
		{
			//continue doing task A
		}
		else
		{
			task_A_done = 1;
		}
		if (/*task B is not done*/)
		{
			//continue doing task B
		}
		else
		{
			task_B_done = 1;
		}
		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
	}
	
	//put specific commands to control robot in here
	loop_done = 0;
	task_A_done = 0;
	task_B_done = 0;
	while(! loop_done)
	{
		if (/*task A is not done*/)
		{
			//continue doing task A
		}
		else
		{
			task_A_done = 1;
		}
		if (/*task B is not done*/)
		{
			//continue doing task B
		}
		else
		{
			task_B_done = 1;
		}
		if (task_A_done && task_B_done)
		{
			loop_done = 1;
		}
	}
}


