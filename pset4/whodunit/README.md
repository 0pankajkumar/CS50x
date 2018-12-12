# Questions

## What's `stdint.h`?

It helps in defining data types like int & char with constant size irrepective of architecture of CPU.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

We can fill exact amount of data to a file essential for bmp type of file without padding. uint16_t has 16bits or 2 bytes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte
DWORD = 4 bytes
LONG = 4 bytes
WORD = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfSize is size of file in bytes
biSize is number of bytes required by the structure

## What does it mean if `biHeight` is negative?

If negative, it represents top down structure of bmp file starting at top-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount does that.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

It might do so when it doesn't encounter a file with specified name or that file is read/ write protected.

## Why is the third argument to `fread` always `1` in our code?

Because it speifies to read only one unit at a time of data type specified before.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

1

## What does `fseek` do?

It places the file position of the cursor at the given offest.

## What is `SEEK_CUR`?

Tells the current position of the file pointer.
