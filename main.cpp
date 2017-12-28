#include <iostream>
#include "basic-bitmap-fileio/windows_bitmap.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	windows_bitmap* wb = new windows_bitmap("modified.bmp", 128, 128);
	read::status rs = wb->import("reference.bmp");
	
	switch (rs)
	{
		case read::success:
			cout << "SUCCESSFUL IMPORT" << endl;
			break;
		case read::bad_filename:
			cout << "BAD FILENAME" << endl;
			break;
		case read::bad_header:
			cout << "BAD HEADER" << endl;
			break;
		case read::bad_file_dimensions:
			cout << "BAD FILE DIMENSIONS" << endl;
			break;
	}
	
	if (rs != read::success)
	{
		delete wb;
		return 0;
	}
	
	device_independent_bitmap* dib = wb->get_dib();
	color_component* img_red = dib->get_image()->get_image_red_array();
	color_component* img_green = dib->get_image()->get_image_green_array();
	color_component* img_blue = dib->get_image()->get_image_blue_array();
	unsigned int w = dib->get_image_width();
	unsigned int h = dib->get_image_height();
	
	for (unsigned int y = 0; y < h; y++)
	{
		for (unsigned int x = 0; x < w; x++)
		{
			unsigned int ind = y * w + x;
			
			//Negative
			img_red[ind] = 255 - img_red[ind];
			img_green[ind] = 255 - img_green[ind];
			img_blue[ind] = 255 - img_blue[ind];
			
			//Threshold
			/*float avg = (img_red[ind] + img_blue[ind] + img_green[ind]) / 3;
			
			if (avg > 127)
			{
				img_red[ind] = 255; img_green[ind] = 255; img_blue[ind] = 255;
			}
			else
			{
				img_red[ind] = 0; img_green[ind] = 0; img_blue[ind] = 0;
			}*/
		}
	}
	
	wb->save();
	
	delete wb;
	return 0;
}
