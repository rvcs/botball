// Created on Sun December 28 2014

int main()
{
	camera_open();
	camera_update();
	graphics_open(get_camera_width(), get_camera_height());
	
	while(!get_key_state('Q'))
	{
		camera_update();
		graphics_blit_enc(get_camera_frame(), BGR, 0, 0, get_camera_width(), get_camera_height());
		graphics_circle_fill(get_camera_width() / 2, get_camera_height() / 2, get_camera_height() / 20, 255, 0, 0);
		graphics_update();
	}
	
	camera_close();
	graphics_close();
	
	return 0;
}
