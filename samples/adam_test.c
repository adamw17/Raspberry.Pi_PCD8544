/*
=================================================================================
 Name        : pcd8544_test.c
 Version     : 0.1

 Copyright (C) 2010 Limor Fried, Adafruit Industries
 Raspberry Pi version by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple PCD8544 LCD (Nokia3310/5110) test for Raspberry PI PCD8544 Library. 
	 Based on Limor Fried's PCD8544 Arduino samples 
	 (https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/blob/master/examples/pcdtest/pcdtest.pde)
	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 LCD pins      Raspberry Pi
	 LCD1 - GND    P06  - GND
	 LCD2 - VCC    P01 - 3.3V
	 LCD3 - CLK    P11 - GPIO0
	 LCD4 - Din    P12 - GPIO1
	 LCD5 - D/C    P13 - GPIO2
	 LCD6 - CS     P15 - GPIO3
	 LCD7 - RST    P16 - GPIO4
	 LCD8 - LED    P01 - 3.3V 

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
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "PCD8544.h"

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs1 = 3;
int _cs2 = 5;
  
// lcd contrast 
int contrast = 50;
  
int main (void)
{
  //pcdstruct _screen1 = {0};
  //pcdstruct _screen2 = {0};

  pcdstruct_ptr screen1 = NULL;
  pcdstruct_ptr screen2 = NULL;

  LCDNew(&screen1);
  LCDNew(&screen2);
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }

  // init and clear lcd
  LCDInit(screen1,_sclk, _din, _dc, _cs1, _rst, contrast);
  // init and clear lcd
  LCDcommand(screen1,PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYALLON);
delay(1000);
  LCDInit(screen2,_sclk, _din, _dc, _cs2, _rst, contrast-25);

  // turn all the pixels on (a handy test)
  printf("Test: All pixels on.\n");
  LCDcommand(screen1,PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYALLON);
  LCDdisplay(screen1);
  delay(1000);

  // turn all the pixels on (a handy test)
  printf("Test: All pixels on.\n");
  LCDcommand(screen2,PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYALLON);
  LCDdisplay(screen2);
  delay(1000);

  // back to normal
  printf("Test: All pixels off.\n");
  LCDcommand(screen1,PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
  LCDclear(screen1);
  LCDdisplay(screen1);

  // back to normal
  printf("Test: All pixels off.\n");
  LCDcommand(screen2,PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // display logo
  printf("Test: Display logo.\n");
  LCDshowLogo(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);
  
  // display logo
  printf("Test: Display logo.\n");
  LCDshowLogo(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw a single pixel
  printf("Test: Display single pixel.\n");
  LCDsetPixel(screen1,10, 10, BLACK);
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);
  
  // draw a single pixel
  printf("Test: Display single pixel.\n");
  LCDsetPixel(screen2,10, 10, BLACK);
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw many lines
  printf("Test: Draw many lines.\n");
  int i;
  for (i=0; i<84; i+=4) {
    LCDdrawline(screen1,0, 0, i, 47, BLACK);
  }  
  for (i=0; i<48; i+=4) {
    LCDdrawline(screen1,0, 0, 83, i, BLACK);
  }
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);

  // draw many lines
  printf("Test: Draw many lines.\n");
  for (i=0; i<84; i+=4) {
    LCDdrawline(screen2,0, 0, i, 47, BLACK);
  }  
  for (i=0; i<48; i+=4) {
    LCDdrawline(screen2,0, 0, 83, i, BLACK);
  }
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw rectangles
  printf("Test: Draw rectangles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawrect(screen1,i, i, 96-i, 48-i, BLACK);
  }
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);
  
  // draw rectangles
  printf("Test: Draw rectangles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawrect(screen2,i, i, 96-i, 48-i, BLACK);
  }
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw multiple rectangles
  printf("Test: Draw multiple rectangles.\n");
  for (i=0; i<48; i++) {
    // alternate colors for moire effect
    LCDfillrect(screen1,i, i, 84-i, 48-i, i%2);
  }
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);
  
  // draw multiple rectangles
  printf("Test: Draw multiple rectangles.\n");
  for (i=0; i<48; i++) {
    // alternate colors for moire effect
    LCDfillrect(screen2,i, i, 84-i, 48-i, i%2);
  }
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw mulitple circles
  printf("Test: Draw multiple circles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawcircle(screen1,41, 23, i, BLACK);
  }
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);

  // draw mulitple circles
  printf("Test: Draw multiple circles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawcircle(screen2,41, 23, i, BLACK);
  }
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);
  
  // draw the first ~120 characters in the font
  printf("Test: Draw the first ~120 chars.\n");
  for (i=0; i < 64; i++) {
    LCDdrawchar(screen1,(i % 14) * 6, (i/14) * 8, i);
  }    
  LCDdisplay(screen1);
  delay(2000);
  for (i=0; i < 64; i++) {
    LCDdrawchar(screen1,(i % 14) * 6, (i/14) * 8, i + 64);
  }
  LCDdisplay(screen1);
  delay(2000);
  LCDclear(screen1);
  LCDdisplay(screen1);

  // draw the first ~120 characters in the font
  printf("Test: Draw the first ~120 chars.\n");
  for (i=0; i < 64; i++) {
    LCDdrawchar(screen2,(i % 14) * 6, (i/14) * 8, i);
  }    
  LCDdisplay(screen2);
  delay(2000);
  for (i=0; i < 64; i++) {
    LCDdrawchar(screen2,(i % 14) * 6, (i/14) * 8, i + 64);
  }
  LCDdisplay(screen2);
  delay(2000);
  LCDclear(screen2);
  LCDdisplay(screen2);

  LCDFree(screen1);
  LCDFree(screen2);
  
  return 0;
}
