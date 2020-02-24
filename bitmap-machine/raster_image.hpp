/*==============================================================================================
    
    raster_image.hpp
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
    
==============================================================================================

    Raster Image Class
    4/6/17 - B.D.S.
    Purpose: An uncompressed 24-bit bitmap image in memory.
    
==============================================================================================*/

#ifndef _RASTER_IMAGE_HPP
#define _RASTER_IMAGE_HPP

typedef unsigned char color_component;
typedef unsigned int color;

class raster_image
{
    private:
        unsigned int image_width;
        unsigned int image_height;
        color_component* image_red_array;
        color_component* image_green_array;
        color_component* image_blue_array;
        color_component color_get_red(color c);
        color_component color_get_green(color c);
        color_component color_get_blue(color c);
    public:
        raster_image(unsigned int width, unsigned int height, color c);
        raster_image(unsigned int width, unsigned int height);
        ~raster_image();
        color_component* get_image_red_array();
        color_component* get_image_green_array();
        color_component* get_image_blue_array();
        void set_pixel(unsigned int x, unsigned int y, color c);
        void clear_to_color(color c);
};

#endif
