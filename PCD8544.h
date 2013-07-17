/*
=================================================================================
 Name        : PCD8544.h
 Version     : 0.1

 Copyright (C) 2010 Limor Fried, Adafruit Industries
 CORTEX-M3 version by Le Dang Dung, 2011 LeeDangDung@gmail.com (tested on LPC1769)
 Raspberry Pi version by Andre Wussow, 2012, desk@binerry.de

 Description : PCD8544 LCD library!

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */
#include <stdint.h>

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 84
#define LCDHEIGHT 48

#define PCD8544_POWERDOWN 0x04
#define PCD8544_ENTRYMODE 0x02
#define PCD8544_EXTENDEDINSTRUCTION 0x01

#define PCD8544_DISPLAYBLANK 0x0
#define PCD8544_DISPLAYNORMAL 0x4
#define PCD8544_DISPLAYALLON 0x1
#define PCD8544_DISPLAYINVERTED 0x5

// H = 0
#define PCD8544_FUNCTIONSET 0x20
#define PCD8544_DISPLAYCONTROL 0x08
#define PCD8544_SETYADDR 0x40
#define PCD8544_SETXADDR 0x80

// H = 1
#define PCD8544_SETTEMP 0x04
#define PCD8544_SETBIAS 0x10
#define PCD8544_SETVOP 0x80

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

 // calibrate clock constants
#define CLKCONST_1  8000
#define CLKCONST_2  400  // 400 is a good tested value for Raspberry Pi

// keywords
#define LSBFIRST  0
#define MSBFIRST  1

typedef struct _PCDstruct{
  uint8_t _din;
  uint8_t _sclk;
  uint8_t _dc;
  uint8_t _rst;
  uint8_t _cs;

  uint8_t cursor_x;
  uint8_t cursor_y;
  uint8_t textsize;
  uint8_t textcolor;
  uint8_t contrast;
  // the memory buffer for the LCD
  uint8_t pcd8544_buffer[LCDWIDTH * LCDHEIGHT / 8]; // = {0,};
} pcdstruct;

typedef pcdstruct * pcdstruct_ptr;


 void LCDInit(pcdstruct_ptr pcd, uint8_t SCLK, uint8_t DIN, uint8_t DC, uint8_t CS, uint8_t RST, uint8_t contrast);
 void LCDcommand(pcdstruct_ptr pcd, uint8_t c);
 void LCDdata(pcdstruct_ptr pcd, uint8_t c);
 void LCDsetContrast(pcdstruct_ptr pcd, uint8_t val);
 void LCDclear(pcdstruct_ptr pcd);
 void LCDdisplay(pcdstruct_ptr pcd);
 void LCDsetPixel(pcdstruct_ptr pcd, uint8_t x, uint8_t y, uint8_t color);
 uint8_t LCDgetPixel(pcdstruct_ptr pcd, uint8_t x, uint8_t y);
 void LCDfillcircle(pcdstruct_ptr pcd, uint8_t x0, uint8_t y0, uint8_t r,uint8_t color);
 void LCDdrawcircle(pcdstruct_ptr pcd, uint8_t x0, uint8_t y0, uint8_t r,uint8_t color);
 void LCDdrawrect(pcdstruct_ptr pcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
 void LCDfillrect(pcdstruct_ptr pcd, uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
 void LCDdrawline(pcdstruct_ptr pcd, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
 void LCDsetCursor(pcdstruct_ptr pcd, uint8_t x, uint8_t y);
 void LCDsetTextSize(pcdstruct_ptr pcd, uint8_t s);
 void LCDsetTextColor(pcdstruct_ptr pcd, uint8_t c);
 void LCDwrite(pcdstruct_ptr pcd, uint8_t c);
 void LCDshowLogo(pcdstruct_ptr pcd);
 void LCDdrawchar(pcdstruct_ptr pcd, uint8_t x, uint8_t line, char c);
 void LCDdrawstring(pcdstruct_ptr pcd, uint8_t x, uint8_t line, char *c);
 void LCDdrawstring_P(pcdstruct_ptr pcd, uint8_t x, uint8_t line, const char *c);
 void LCDdrawbitmap(pcdstruct_ptr pcd, uint8_t x, uint8_t y,  const uint8_t *bitmap, uint8_t w, uint8_t h,  uint8_t color);
 void LCDspiwrite(pcdstruct_ptr pcd, uint8_t c);
 void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
 void _delay_ms(uint32_t t);
