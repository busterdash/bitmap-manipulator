# The Bitmap Machine

* Read and write to 24-bit Windows Bitmap files in C++.
* This is not very well tested yet, use at your own risk.

## Components
* ```binary_rw``` - A layer between cold hard C++ file components and my heartwarming love components.
* ```device_independent_bitmap``` - Standard bitmap which encapsulates the ```raster_image```.
* ```raster_image``` - Structure which contains three pixel arrays (RGB.)
* ```windows_bitmap``` - Represents the file and encapsulates the D.I.B.

## The Bitmaps
* ```BITMAPINFOHEADER``` type file format.
* Images compatible with Windows 3.1 and above.
* 24-bit only as of right now.

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)