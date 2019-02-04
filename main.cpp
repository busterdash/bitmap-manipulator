/*==============================================================================================
	
	main.cpp
	Copyright 2019 Buster Schrader
	
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
#include <string>
#include "bitmap-machine/windows_bitmap.hpp"
using namespace std;

void perform_negative(device_independent_bitmap* dib, int mask)
{
	color_component* img_red = dib->get_image()->get_image_red_array();
	color_component* img_green = dib->get_image()->get_image_green_array();
	color_component* img_blue = dib->get_image()->get_image_blue_array();
	unsigned int w = dib->get_image_width();
	unsigned int h = dib->get_image_height();
	unsigned int len = w * h;
	
	if ((mask >> 2) & 1)
	{
		for (unsigned int i = 0; i < len; i++)
		{
			img_red[i] = 255 - img_red[i];
		}
	}
	
	if ((mask >> 1) & 1)
	{
		for (unsigned int i = 0; i < len; i++)
		{
			img_green[i] = 255 - img_green[i];
		}
	}
	
	if (mask & 1)
	{
		for (unsigned int i = 0; i < len; i++)
		{
			img_blue[i] = 255 - img_blue[i];
		}
	}
}

void perform_threshold(device_independent_bitmap* dib, float apex)
{
	color_component* img_red = dib->get_image()->get_image_red_array();
	color_component* img_green = dib->get_image()->get_image_green_array();
	color_component* img_blue = dib->get_image()->get_image_blue_array();
	unsigned int w = dib->get_image_width();
	unsigned int h = dib->get_image_height();
	unsigned int len = w * h;
	
	for (unsigned int i = 0; i < len; i++)
	{
		float avg = (img_red[i] + img_blue[i] + img_green[i]) / 3.0f;
			
		if (avg > apex)
		{
			img_red[i] = 255;
			img_green[i] = 255;
			img_blue[i] = 255;
		}
		else
		{
			img_red[i] = 0;
			img_green[i] = 0;
			img_blue[i] = 0;
		}
	}
}

int main(int argument_count, char* argument_value[])
{
	string in_file = "reference.bmp";
	string out_file = "modified.bmp";
	string work_order = "";
	windows_bitmap* wb = new windows_bitmap(out_file, 128, 128);
	read::status rs = wb->import(in_file);
	
	switch (rs)
	{
		case read::success:
			cout << "Successfully imported " << in_file << endl; break;
		case read::bad_filename:
			cout << "ERROR: Could not find " << in_file << '!' << endl; break;
		case read::bad_header:
			cout << "ERROR: Input file does not have correct file header!" << endl; break;
		case read::bad_file_dimensions:
			cout << "ERROR: File is of unexpected file dimensions!" << endl; break;
	}
	
	if (rs != read::success)
	{
		delete wb;
		return 0;
	}
	
	cout << endl << "The following are operations to perform" << endl;
	cout << "on an image. Please input a string of" << endl;
	cout << "the corresponding letters to put together" << endl;
	cout << "a work order to be performed on the image." << endl;
	cout << "Operations are processed left to right." << endl;
	cout << "______________________________________________________________" << endl << endl;
	cout << "N\t(Image Negative) Follow with a number between" << endl;
	cout << "\t0 and 7 inclusively to specify which colors are" << endl;
	cout << "\taffected. For instance, 2 is 010 as a binary mask" << endl;
	cout << "\twhich affects only the green channel. 2 can be used" << endl;
	cout << "\tto flip normals between Blender and the Source Engine." << endl << endl;
	cout << "T\t(Image Threshold) Follow with a number between" << endl;
	cout << "\t0 and 6 inclusively to specify what brightness" << endl;
	cout << "\tshould decide which color to clamp the pixel to." << endl << endl;
	
	getline(cin,work_order);
	cout << endl;
	
	unsigned int i = 0;
	bool has_param = false;
	while(i < work_order.length()) //Go through input string.
	{
		//This boolean represents whether or not the following char is an argument.
		has_param = (i < work_order.length()-1 and
					((int)work_order[i+1] > 47 and (int)work_order[i+1] <= 57));
		
		switch(work_order[i])
		{
			case 'N':
			case 'n':
				if (has_param)
					perform_negative(wb->get_dib(),(int)work_order[i+1]-48);
				else
					perform_negative(wb->get_dib(),7);
				break;
			case 'T':
			case 't':
				if (has_param)
					perform_threshold(wb->get_dib(),((int)work_order[i+1]-48)*42.5f);
				else
					perform_threshold(wb->get_dib(),127.0f);
				break;
		}
		
		i++;
	}
	
	cout << "Operation performed, image saved as " << out_file << endl;
	wb->save();
	delete wb;
	return 0;
}
