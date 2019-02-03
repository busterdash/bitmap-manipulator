/*==============================================================================================
	
	main.cpp
	Copyright 2018 Buster Schrader
	
	This file is part of Bitmap Manipulator.
	
	Bitmap Manipulator is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any later version.
	
	Bitmap Manipulator is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with Bitmap Manipulator.  If not, see <https://www.gnu.org/licenses/>.
	
==============================================================================================*/

#include <iostream>
#include "bitmap-machine/windows_bitmap.hpp"
using namespace std;

int main(int argument_count, char* argument_value[])
{
	string in_file = "reference.bmp";
	string out_file = "modified.bmp";
	windows_bitmap* wb = new windows_bitmap(out_file, 128, 128);
	read::status rs = wb->import(in_file);
	
	switch (rs)
	{
		case read::success:
			cout << "Successfully imported " << in_file << endl;
			break;
		case read::bad_filename:
			cout << "ERROR: Could not find " << in_file << '!' << endl;
			break;
		case read::bad_header:
			cout << "ERROR: Input file does not have correct file header!" << endl;
			break;
		case read::bad_file_dimensions:
			cout << "ERROR: File is of unexpected file dimensions!" << endl;
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
	
	cout << "Operation performed, image saved as " << out_file << endl;
	wb->save();
	delete wb;
	return 0;
}
