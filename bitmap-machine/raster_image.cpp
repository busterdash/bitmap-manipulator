/*==============================================================================================
    
    raster_image.cpp
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

#include "raster_image.hpp"

raster_image::raster_image(unsigned int width, unsigned int height, color c)
{
    image_red_array = new color_component[width*height];
    image_green_array = new color_component[width*height];
    image_blue_array = new color_component[width*height];
    
    image_width = width;
    image_height = height;
    
    clear_to_color(c);
}

raster_image::raster_image(unsigned int width, unsigned int height)
{
    image_red_array = new color_component[width*height];
    image_green_array = new color_component[width*height];
    image_blue_array = new color_component[width*height];
    
    image_width = width;
    image_height = height;
    
    clear_to_color(0xffffff);
}

void raster_image::clear_to_color(color c)
{
    for (unsigned int y = 0; y < image_height; y++)
    {
        for (unsigned int x = 0; x < image_width; x++)
        {
            image_red_array[y*image_width+x] = color_get_red(c);
            image_green_array[y*image_width+x] = color_get_green(c);
            image_blue_array[y*image_width+x] = color_get_blue(c);
        }
    }
}

raster_image::~raster_image()
{
    delete[] image_red_array;
    delete[] image_green_array;
    delete[] image_blue_array;
}

color_component* raster_image::get_image_red_array()
{
    return image_red_array;
}

color_component* raster_image::get_image_green_array()
{
    return image_green_array;    
}

color_component* raster_image::get_image_blue_array()
{
    return image_blue_array;
}

color_component raster_image::color_get_red(color c)
{
    return (color_component)((c >> 16) & 255);
}

color_component raster_image::color_get_green(color c)
{
    return (color_component)((c >> 8) & 255);
}

color_component raster_image::color_get_blue(color c)
{
    return (color_component)(c & 255);
}

void raster_image::set_pixel(unsigned int x, unsigned int y, color c)
{
    int index = y * image_width + x;
    image_red_array[index] = color_get_red(c);
    image_green_array[index] = color_get_green(c);
    image_blue_array[index] = color_get_blue(c);
}
