/*==============================================================================================
    
    device_independent_bitmap.hpp
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

    Device Independent Bitmap Class
    4/6/17 - B.D.S.
    Purpose: Creates the image portion of the bitmap file.
    
==============================================================================================*/

#ifndef _DEVICE_BITMAP_HPP
#define _DEVICE_BITMAP_HPP

#include "binary_rw.hpp"
#include "raster_image.hpp"

class device_independent_bitmap
{
    private:
        word header_size;
        word bitmap_width;
        word bitmap_height;
        halfword color_plane_count;
        halfword bits_per_pixel;
        word compression_method;
        word bitmap_data_size;
        word hor_pixel_per_meter;
        word ver_pixel_per_meter;
        word palette_color_count;
        word important_color_count;
        raster_image* img;
    public:
        device_independent_bitmap(unsigned int width, unsigned int height);
        ~device_independent_bitmap();
        void save(std::ofstream* f);
        raster_image* get_image();
        int get_header_size();
        int get_image_size();
        int get_image_width();
        int get_image_height();
};

#endif
