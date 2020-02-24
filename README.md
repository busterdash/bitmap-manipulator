# Bitmap Manipulator
Apply mathematical operations on images. An usage example of my bitmap library.

## Usage

On starting the application, the user is introduced to a prompt for a work order. From here a string can be typed into to instruct the program what to do to the image. At the moment, the program is hard-coded to modify the included reference.bmp file. 

Right now there are four operations the program can perform.
* Negative - Invert the colors of an image.
* Threshold - Clamps pixels to fully black or white.
* Addition - Adds a color to every pixel.
* Subtraction - Subtracts a color from every pixel.

A work order consists of one or more operations which are denoted by the first letter of their name. Operations may or may not be followed with a parameter. This can be a single digit like 5, or can be a longer value like ($f245d8). Non single digit parameters are always contained within parentheses; they are usually for specifying colors or other files. Single digit parameters are typically for bit flags allowing an operation to be configurable three ways; usually for turning off specific color channels as is the case with the negative operation. Otherwise, they are useful as a single scalar value. 

As an example: N7A(#7f0000)T3 loads up the original image, performs the negative on all color channels, then performs the addition operation on the image. In this case it adds 127 to the pixels' red channel. Lastly, it performs the threshold operation on the image using a brightness in the very middle to decide whether the pixel should be fully black or white. 

## Compiling
* For simplicity, I use Orwell Dev-C++ to compile on Windows.
* On Linux, a makefile is provided for compiling with the GNU C++ Compiler. 

### The Bitmap Machine:
* Writes windows bitmaps of type ```BITMAPINFOHEADER```.
* Images compatible with Windows 3.1 and above.

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)
