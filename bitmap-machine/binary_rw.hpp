/*==============================================================================================
    
    binary_rw.hpp
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
    
    Binary Reader/Writer Struct
    4/6/17 - B.D.S.
    Purpose: Provides an interface to R&W binary data easier.
    
==============================================================================================*/

#ifndef _BINARY_RW_HPP
#define _BINARY_RW_HPP

#include <fstream>
typedef unsigned short int halfword;
typedef unsigned long int word;

struct binary_rw
{
    static int bytes_written;
    static void write(std::ofstream* f, halfword hw);
    static void write(std::ofstream* f, word w);
    static word read_word(std::ifstream* f);
    static halfword read_halfword(std::ifstream* f);
    static void skip_words(std::ifstream* f, int words);
    static void skip_halfwords(std::ifstream* f, int halfwords);
};

#endif
