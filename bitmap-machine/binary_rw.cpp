/*==============================================================================================
    
    binary_rw.xpp
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

#include "binary_rw.hpp"

int binary_rw::bytes_written = 0;

void binary_rw::write(std::ofstream* f, halfword hw)
{
    char byte1 = (char)(hw >> 8);
    char byte2 = (char)(hw & 255);
    f->put(byte2); //Reverse these for big-endian.
    f->put(byte1);
    bytes_written += 2;
}

void binary_rw::write(std::ofstream* f, word w)
{
    char byte1 = (char)(w >> 24);
    char byte2 = (char)((w >> 16) & 255);
    char byte3 = (char)((w >> 8) & 255);
    char byte4 = (char)(w & 255);
    f->put(byte4); //Reverse these for big-endian.
    f->put(byte3);
    f->put(byte2);
    f->put(byte1);
    bytes_written += 4;
}

word binary_rw::read_word(std::ifstream* f)
{
    word output = 0;
    char byte1, byte2, byte3, byte4;
    f->get(byte1);
    f->get(byte2);
    f->get(byte3);
    f->get(byte4);
    output = (output|(unsigned char)byte4)<<8;
    output = (output|(unsigned char)byte3)<<8;
    output = (output|(unsigned char)byte2)<<8;
    output = (output|(unsigned char)byte1);
    return output;
}

halfword binary_rw::read_halfword(std::ifstream* f)
{
    halfword output = 0;
    char byte1, byte2;
    f->get(byte1);
    f->get(byte2);
    output = (output|(unsigned char)byte2)<<8;
    output = (output|(unsigned char)byte1);
    return output;
}

void binary_rw::skip_words(std::ifstream* f, int words)
{
    f->seekg(words*4,std::ios_base::cur);
}

void binary_rw::skip_halfwords(std::ifstream* f, int halfwords)
{
    f->seekg(halfwords*2,std::ios_base::cur);
}
