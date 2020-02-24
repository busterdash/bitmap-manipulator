/*==============================================================================================
    
    device_independent_bitmap.cpp
    Copyright 2019 Buster Schrader
    
    This file is part of The Bitmap Manipulator.
    
    The Bitmap Manipulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    
    The Bitmap Manipulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with The Bitmap Manipulator.  If not, see <https://www.gnu.org/licenses/>.
    
==============================================================================================*/

#include "device_independent_bitmap.hpp"
#include <math.h>

device_independent_bitmap::device_independent_bitmap(unsigned int width, unsigned int height)
{
    header_size = 40;
    bitmap_width = width;
    bitmap_height = height;
    color_plane_count = 1;
    bits_per_pixel = 24;
    compression_method = 0; //BI_RGB (no compression.)
    bitmap_data_size = 0; //Dummy of zero can be give for BI_RGB.
    hor_pixel_per_meter = 0;
    ver_pixel_per_meter = 0;
    palette_color_count = 0;
    important_color_count = 0;
    img = new raster_image(bitmap_width, bitmap_height);
}

device_independent_bitmap::~device_independent_bitmap()
{
    delete img;
}

void device_independent_bitmap::save(std::ofstream* f)
{
    binary_rw::write(f, header_size);
    binary_rw::write(f, bitmap_width);
    binary_rw::write(f, bitmap_height);
    binary_rw::write(f, color_plane_count);
    binary_rw::write(f, bits_per_pixel);
    binary_rw::write(f, compression_method);
    binary_rw::write(f, bitmap_data_size);
    binary_rw::write(f, hor_pixel_per_meter);
    binary_rw::write(f, ver_pixel_per_meter);
    binary_rw::write(f, palette_color_count);
    binary_rw::write(f, important_color_count);
    
    color_component* r = img->get_image_red_array();
    color_component* g = img->get_image_green_array();
    color_component* b = img->get_image_blue_array();
    
    unsigned int index = 0;
    unsigned int padding = bitmap_width % 4;

    for (unsigned int y = 0; y < bitmap_height; y++) 
    {
        for (int x = 0; x < bitmap_width; x++)
        {
            index = (bitmap_height - y - 1) * bitmap_width + x;
            f->put((char)b[index]);
            f->put((char)g[index]);
            f->put((char)r[index]);
        }
        
        f->write("\0\0\0\0",padding);
    }
}

raster_image* device_independent_bitmap::get_image()
{
    return img;
}

int device_independent_bitmap::get_header_size()
{
    return header_size;    
}

int device_independent_bitmap::get_image_size()
{
    return bitmap_height*(int)floor((double)(bits_per_pixel*bitmap_width+31)/32.0)*4;
}

int device_independent_bitmap::get_image_width()
{
    return (int)bitmap_width;
}

int device_independent_bitmap::get_image_height()
{
    return (int)bitmap_height;
}
