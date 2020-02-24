/*==============================================================================================
    
    windows_bitmap.hpp
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
    
    Windows Bitmap Class
    4/6/17 - B.D.S.
    Purpose: Creates a windows bitmap image.
    
==============================================================================================*/

#ifndef _WINDOWS_BITMAP_HPP
#define _WINDOWS_BITMAP_HPP

#include "device_independent_bitmap.hpp"
#include "binary_rw.hpp"
#include <string>

namespace read
{
    enum status { success, bad_filename, bad_header, bad_file_dimensions };
}

class windows_bitmap
{
    private:
        std::string filename;
        const static short wb_header_size = 14;
        const static halfword header = 0x4D42; //BM in the end, reversed initially for little-endian.
        word bmp_size;
        halfword reserved1;
        halfword reserved2;
        word image_data_offset;
        device_independent_bitmap* dib;
    public:
        windows_bitmap(std::string file, unsigned int width, unsigned int height);
        ~windows_bitmap();
        bool save();
        read::status import(std::string file);
        device_independent_bitmap* get_dib();
};

#endif
