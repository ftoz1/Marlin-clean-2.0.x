/*
  UTFT.cpp - Multi-Platform library support for Color TFT LCD Boards
  Copyright (C)2015-2018 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library is the continuation of my ITDB02_Graph, ITDB02_Graph16
  and RGB_GLCD libraries for Arduino and chipKit. As the number of 
  supported display modules and controllers started to increase I felt 
  it was time to make a single, universal library as it will be much 
  easier to maintain in the future.

  Basic functionality of this library was origianlly based on the 
  demo-code provided by ITead studio (for the ITDB02 modules) and 
  NKC Electronics (for the RGB GLCD module/shield).

  This library supports a number of 8bit, 16bit and serial graphic 
  displays, and will work with both Arduino, chipKit boards and select 
  TI LaunchPads. For a full list of tested display modules and controllers,
  see the document UTFT_Supported_display_modules_&_controllers.pdf.

  When using 8bit and 16bit display modules there are some 
  requirements you must adhere to. These requirements can be found 
  in the document UTFT_Requirements.pdf.
  There are no special requirements when using serial displays.

  You can find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#include "UTFT.h"
#include "../inc/MarlinConfig.h"

// Include hardware-specific functions for the correct MCU
#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#include "hardware/avr/HW_AVR.h"
	#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		#include "hardware/avr/HW_ATmega1280.h" 
	#elif defined(__AVR_ATmega328P__)
		#include "hardware/avr/HW_ATmega328P.h"
	#elif defined(__AVR_ATmega32U4__)
		#include "hardware/avr/HW_ATmega32U4.h"
	#elif defined(__AVR_ATmega168__)
		#error "ATmega168 MCUs are not supported because they have too little flash memory!"
	#elif defined(__AVR_ATmega1284P__)
		#include "hardware/avr/HW_ATmega1284P.h"
	#else
		#error "Unsupported AVR MCU!"
	#endif
#elif defined(__PIC32MX__)
  #include "hardware/pic32/HW_PIC32.h"
  #if defined(__32MX320F128H__)
    #pragma message("Compiling for chipKIT UNO32 (PIC32MX320F128H)")
	#include "hardware/pic32/HW_PIC32MX320F128H.h"
  #elif defined(__32MX340F512H__)
    #pragma message("Compiling for chipKIT uC32 (PIC32MX340F512H)")
	#include "hardware/pic32/HW_PIC32MX340F512H.h"
  #elif defined(__32MX795F512L__)
    #pragma message("Compiling for chipKIT MAX32 (PIC32MX795F512L)")
	#include "hardware/pic32/HW_PIC32MX795F512L.h"
  #else
    #error "Unsupported PIC32 MCU!"
  #endif  
#elif defined(__arm__)
	// #include "hardware/arm/HW_ARM.h"
	#if defined(__STM32F1__)
		#pragma message("Compiling for STM32F1")
		#include "hardware/arm/HW_ARM_defines.h"
	#elif defined(__MK20DX128__) || defined(__MK20DX256__)
		#pragma message("Compiling for Teensy 3.x (MK20DX128VLH7 / MK20DX256VLH7)...")
		#include "hardware/arm/HW_MX20DX256.h"
	#elif defined(__CC3200R1M1RGC__)
		#pragma message("Compiling for TI CC3200 LaunchPad...")
		#include "hardware/arm/HW_CC3200.h"
	#else
		#error "Unsupported ARM MCU!"
	#endif
#endif


/*UTFT::UTFT()
{
}  */

UTFT::UTFT(TFT_FSMC *ptrIO, byte model, int RS, int WR, int CS, int RST, int SER)
{ 
	disp_x_size =			XRES-1 ;//dsx[model];  X-1
	disp_y_size =			YRES-1 ;//dsy[model];  Y-1 
	display_transfer_mode =	16 ;//dtm[model];   number of data wires
	display_model =			model;
	
    P_IO = ptrIO;   
	__p1 = RS;
	__p2 = WR;
	__p3 = CS;
	__p4 = RST;
	__p5 = SER;


	//	_set_direction_registers(display_transfer_mode);   // freeze when uncoment
		P_RS	= portOutputRegister(digitalPinToPort(RS));    //direct access to gpios like digital write.
		B_RS	= digitalPinToBitMask(RS);
		P_WR	= portOutputRegister(digitalPinToPort(WR));
		B_WR	= digitalPinToBitMask(WR);
		P_CS	= portOutputRegister(digitalPinToPort(CS));
		B_CS	= digitalPinToBitMask(CS);
		P_RST	= portOutputRegister(digitalPinToPort(RST));
		B_RST	= digitalPinToBitMask(RST);    
}

inline void UTFT::LCD_Write_COM(word com)  
{   	
	P_IO->WriteReg(com);
}

inline void UTFT::LCD_Write_DATA(word data)
{
	P_IO->WriteData(data);	
}

inline void UTFT::LCD_Write_COM_DATA(char com1,int dat1)
{
     P_IO->WriteReg(com1);
     P_IO->WriteData(dat1);
}

inline void UTFT::fast_fill_32(word color,long length)
{   
//	P_IO->WriteMultiple32((color<<16) | color, length/2 + length%2);
    P_IO->WriteMultiple(color, length);
}

inline void UTFT::fast_fill_16(word color,long length)
{
	P_IO->WriteMultiple(color, length);
}

void UTFT::InitLCD(byte orientation)
{
	orient=orientation;
	//_hw_special_init();
	P_IO->Init();          // bus init (fsmc or spi)   
 //   FSMC_Init(__p3,__p1);
/*	pinMode(__p1,OUTPUT);
	pinMode(__p2,OUTPUT);
	pinMode(__p3,OUTPUT);
	if (__p4 != NOTINUSE)
		pinMode(__p4,OUTPUT);
	if ((display_transfer_mode==LATCHED_16) or ((display_transfer_mode==1) and (display_serial_mode==SERIAL_5PIN)))
		pinMode(__p5,OUTPUT);
	if (display_transfer_mode!=1)
		_set_direction_registers(display_transfer_mode);  */
    pinMode(__p4,OUTPUT);
	sbi(P_RST, B_RST);
	delay(5); 
	cbi(P_RST, B_RST);
	delay(15);
	sbi(P_RST, B_RST);
	delay(15);  

	cbi(P_CS, B_CS);  

//insert init sequences for specifis LCD

#ifdef ENABLE_RM68140
	#include "tft_drivers/rm68140/initlcd.h"
#endif
#ifdef ENABLE_HX8347A
	#include "tft_drivers/hx8347a/initlcd.h"
#endif
#ifdef ENABLE_ILI9327
	#include "tft_drivers/ili9327/initlcd.h"
#endif
#ifdef ENABLE_SSD1289
	#include "tft_drivers/ssd1289/initlcd.h"
#endif
#ifdef ENABLE_ILI9325C
	#include "tft_drivers/ili9325c/initlcd.h"
#endif
#ifdef ENABLE_ILI9325D
	#include "tft_drivers/ili9325d/default/initlcd.h"
#endif
#ifdef ENABLE_ILI9325D_ALT
	#include "tft_drivers/ili9325d/alt/initlcd.h"
#endif
#ifdef ENABLE_HX8340B_S
	#include "tft_drivers/hx8340b/s/initlcd.h"
#endif
#ifdef ENABLE_ST7735
	#include "tft_drivers/st7735/std/initlcd.h"
#endif
#ifdef ENABLE_PCF8833
	#include "tft_drivers/pcf8833/initlcd.h"
#endif
#ifdef ENABLE_S1D19122
	#include "tft_drivers/s1d19122/initlcd.h"
#endif
#ifdef ENABLE_HX8352A
	#include "tft_drivers/hx8352a/initlcd.h"
#endif
#ifdef ENABLE_SSD1963_480
	#include "tft_drivers/ssd1963/480/initlcd.h"
#endif
#ifdef ENABLE_SSD1963_800
	#include "tft_drivers/ssd1963/800/initlcd.h"
#endif
#ifdef ENABLE_SSD1963_800_ALT
	#include "tft_drivers/ssd1963/800alt/initlcd.h"
#endif
#ifdef ENABLE_S6D1121
	#include "tft_drivers/s6d1121/initlcd.h"
#endif
#ifdef ENABLE_ILI9481
	#include "tft_drivers/ili9481/initlcd.h"
#endif
#ifdef ENABLE_S6D0164
	#include "tft_drivers/s6d0164/initlcd.h"
#endif
#ifdef ENABLE_ILI9341_S5P
	#include "tft_drivers/ili9341/s5p/initlcd.h"
#endif
#ifdef ENABLE_ILI9341_16
	#include "tft_drivers/ili9341/16/initlcd.h"
#endif
#ifdef ENABLE_R61581
	#include "tft_drivers/r61581/initlcd.h"
#endif
#ifdef ENABLE_ILI9486
	#include "tft_drivers/ili9486/initlcd.h"
#endif
#ifdef ENABLE_CPLD
	#include "tft_drivers/cpld/initlcd.h"
#endif
#ifdef ENABLE_HX8353C
	#include "tft_drivers/hx8353c/initlcd.h"
#endif

// tilt screen
screenOrient(orientation);	

	sbi (P_CS, B_CS); 
	setColor(COLOR_WHITE);
	setBackColor(COLOR_BLACK);
	cfont.font=0;
	_transparent = false;
}

 void UTFT::setXY(word x1, word y1, word x2, word y2)   //set area to be written
{

#ifdef ENABLE_RM68140
	#include "tft_drivers/rm68140/setxy.h"
#endif
#ifdef ENABLE_HX8347A
	#include "tft_drivers/hx8347a/setxy.h"
#endif
#ifdef ENABLE_HX8352A
	#include "tft_drivers/hx8352a/setxy.h"
#endif
#ifdef ENABLE_ILI9327
	#include "tft_drivers/ili9327/setxy.h"
#endif
#ifdef ENABLE_SSD1289
	#include "tft_drivers/ssd1289/setxy.h"
#endif
#ifdef ENABLE_ILI9325C
	#include "tft_drivers/ili9325c/setxy.h"
#endif
#ifdef ENABLE_ILI9325D
	#include "tft_drivers/ili9325d/default/setxy.h"
#endif
#ifdef ENABLE_ILI9325D_ALT
	#include "tft_drivers/ili9325d/alt/setxy.h"
#endif
#ifdef ENABLE_HX8340B_S
	#include "tft_drivers/hx8340b/s/setxy.h"
#endif
#ifdef ENABLE_ST7735
	#include "tft_drivers/st7735/std/setxy.h"
#endif
#ifdef ENABLE_S1D19122
	#include "tft_drivers/s1d19122/setxy.h"
#endif
#ifdef ENABLE_PCF8833
	#include "tft_drivers/pcf8833/setxy.h"
#endif
#ifdef ENABLE_SSD1963_480
	#include "tft_drivers/ssd1963/480/setxy.h"
#endif
#ifdef ENABLE_SSD1963_800
	#include "tft_drivers/ssd1963/800/setxy.h"
#endif
#ifdef ENABLE_SSD1963_800_ALT
	#include "tft_drivers/ssd1963/800alt/setxy.h"
#endif
#ifdef ENABLE_S6D1121
	#include "tft_drivers/s6d1121/setxy.h"
#endif
#ifdef ENABLE_ILI9481
	#include "tft_drivers/ili9481/setxy.h"
#endif
#ifdef ENABLE_S6D0164
	#include "tft_drivers/s6d0164/setxy.h"
#endif
#ifdef ENABLE_ILI9341_S5P
	#include "tft_drivers/ili9341/s5p/setxy.h"
#endif
#ifdef ENABLE_ILI9341_16
	#include "tft_drivers/ili9341/16/setxy.h"
#endif
#ifdef ENABLE_R61581
	#include "tft_drivers/r61581/setxy.h"
#endif
#ifdef ENABLE_ILI9486
	#include "tft_drivers/ili9486/setxy.h"
#endif
#ifdef ENABLE_CPLD
	#include "tft_drivers/cpld/setxy.h"
#endif
#ifdef ENABLE_HX8353C
	#include "tft_drivers/hx8353c/setxy.h"
#endif
	
}

/*void UTFT::clrXY()
{

		setXY(0,0,disp_x_size,disp_y_size);
	else
		setXY(0,0,disp_y_size,disp_x_size);
}*/

void UTFT::drawRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(register int, x1, x2);
	}
	if (y1>y2)
	{
		swap(register int, y1, y2);
	} 

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1);
}

void UTFT::drawRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(register int, x1, x2);
	}
	if (y1>y2)
	{
		swap(register int, y1, y2);
	}  
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		drawPixel(x1+1,y1+1);
		drawPixel(x2-1,y1+1);
		drawPixel(x1+1,y2-1);
		drawPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
	}
}

void UTFT::fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(register int, x1, x2);
	}
	if (y1>y2)
	{
		swap(register int, y1, y2);
	}   
	
		cbi(P_CS, B_CS);
		setXY(x1, y1, x2, y2);
		sbi(P_RS, B_RS);
		fast_fill_32(fcolor,(x2-x1+1)*(y2-y1+1));
		sbi(P_CS, B_CS);
				
}

 void UTFT::fillRoundRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(register int, x1, x2);
	}
	if (y1>y2)
	{
		swap(register int, y1, y2);
	}  

	if ((x2-x1)>4 && (y2-y1)>4)
	{ 
        drawHLine(x1+2, y1, x2-x1-4);
		drawHLine(x1+2, y2, x2-x1-4);
		drawVLine(x1, y1+2, y2-y1-4);
		drawVLine(x2, y1+2, y2-y1-4);
        cbi(P_CS, B_CS);
		setXY(x1+1, y1+1, x2-1, y2-1);
		sbi(P_RS, B_RS);
		fast_fill_32(fcolor,(x2-x1-1)*(y2-y1-1));
		sbi(P_CS, B_CS);	
	}
}

void UTFT::drawCircle(int x, int y, int radius)
{
register int f = 1 - radius;
register int ddF_x = 1;
register int ddF_y = -2 * radius;
register int x1 = 0;
register int y1 = radius;
 
	cbi(P_CS, B_CS);
	setXY(x, y + radius, x, y + radius);
	LCD_Write_DATA(fcolor);
	setXY(x, y - radius, x, y - radius);
	LCD_Write_DATA(fcolor);
	setXY(x + radius, y, x + radius, y);
	LCD_Write_DATA(fcolor);
	setXY(x - radius, y, x - radius, y);
	LCD_Write_DATA(fcolor);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setXY(x + x1, y + y1, x + x1, y + y1);
		LCD_Write_DATA(fcolor);
		setXY(x - x1, y + y1, x - x1, y + y1);
		LCD_Write_DATA(fcolor);
		setXY(x + x1, y - y1, x + x1, y - y1);
		LCD_Write_DATA(fcolor);
		setXY(x - x1, y - y1, x - x1, y - y1);
		LCD_Write_DATA(fcolor);
		setXY(x + y1, y + x1, x + y1, y + x1);
		LCD_Write_DATA(fcolor);
		setXY(x - y1, y + x1, x - y1, y + x1);
		LCD_Write_DATA(fcolor);
		setXY(x + y1, y - x1, x + y1, y - x1);
		LCD_Write_DATA(fcolor);
		setXY(x - y1, y - x1, x - y1, y - x1);
		LCD_Write_DATA(fcolor);
	}
	sbi(P_CS, B_CS);
	//clrXY();
}

 void UTFT::fillCircle(int x, int y, int radius)
{
	for(register int y1=-radius; y1<=0; y1++) 
		for(register int x1=-radius; x1<=0; x1++)
			if(x1*x1+y1*y1 <= radius*radius) 
			{
				drawHLine(x+x1, y+y1, 2*(-x1));
				drawHLine(x+x1, y-y1, 2*(-x1));
				break;
			}
}

void UTFT::clrScr()
{
	fillScr(0);
}

void UTFT::fillScr(byte r, byte g, byte b)
{
	word color = ((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
	fillScr(color);
}

void UTFT::fillScr(word color)
{
	cbi(P_CS, B_CS);
	setXY(0,0,disp_x_size,disp_y_size);
	sbi(P_RS, B_RS);
	fast_fill_32(color,(disp_x_size+1)*(disp_y_size+1));
	sbi(P_CS, B_CS);
}

void UTFT::setColor(byte r, byte g, byte b)
{
	fcolor=((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
}

void UTFT::setColor(word color)
{
	fcolor=color;	
}

word UTFT::getColor()
{
	return fcolor ;
}

void UTFT::setBackColor(byte r, byte g, byte b)
{
	bcolor=((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
	_transparent=false;
}

void UTFT::setBackColor(uint32_t color)
{
	if (color==COLOR_TRANSPARENT)
		_transparent=true;
	else
	{
		bcolor=color;
		_transparent=false;
	}
}

word UTFT::getBackColor()
{
	return bcolor;
}

 void UTFT::drawPixel(int x, int y)
{
	cbi(P_CS, B_CS);
	setXY(x, y, x, y);
	LCD_Write_DATA(fcolor);
	sbi(P_CS, B_CS);
//	clrXY();
}

 void UTFT::drawLine(int x1, int y1, int x2, int y2)
{
	if (y1==y2)
		drawHLine(x1, y1, x2-x1);
	else if (x1==x2)
		drawVLine(x1, y1, y2-y1);
	else
	{
register unsigned int	dx = (x2 > x1 ? x2 - x1 : x1 - x2);
register short			xstep =  x2 > x1 ? 1 : -1;
register unsigned int	dy = (y2 > y1 ? y2 - y1 : y1 - y2);
register short			ystep =  y2 > y1 ? 1 : -1;
register int				col = x1; 
register int   row = y1;

		cbi(P_CS, B_CS);
		if (dx < dy)
		{
register int t = - (dy >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fcolor);
				if (row == y2)
					return;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
register int t = - (dx >> 1);
			while (true)
			{
				setXY (col, row, col, row);
				LCD_Write_DATA (fcolor);
				if (col == x2)
					return;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}
		sbi(P_CS, B_CS);
	}
	//clrXY();
}

 void UTFT::drawHLine(int x,int y,int l)
{
/*	if (l<0)
	{
		l = -l;
		x -= l;
	} */
	cbi(P_CS, B_CS);
	setXY(x, y, x+l, y);
	sbi(P_RS, B_RS);
	fast_fill_32(fcolor,l);
	sbi(P_CS, B_CS);
//	clrXY();
}

 void UTFT::drawVLine(int x,int y,int l)
{
/*	if (l<0)
	{
		l = -l;
		y -= l;
	}  */
	cbi(P_CS, B_CS);
	setXY(x, y, x, y+l);
	sbi(P_RS, B_RS);
	fast_fill_32(fcolor,l);
	sbi(P_CS, B_CS);
//	clrXY();
}

void UTFT::printChar(byte c, int x, int y)
{
	byte ch;
	word temp; 

	cbi(P_CS, B_CS);
  
	if (!_transparent)
	{
		
			setXY(x,y,x+cfont.x_size-1,y+cfont.y_size-1);
	  
			temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
			for(register word j=0;j<((cfont.x_size/8)*cfont.y_size);j++)
			{
				ch= *(&cfont.font[temp]);
				for(register byte i=0;i<8;i++)
				{   
					if((ch&(1<<(7-i)))!=0)   
					{
						LCD_Write_DATA(fcolor);
					} 
					else
					{
						LCD_Write_DATA(bcolor);
					}   
				}
				temp++;
			}	
	}
	else
	{
		temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
		for(register word j=0;j<cfont.y_size;j++) 
		{
			for (register int zz=0; zz<(cfont.x_size/8); zz++)
			{
				ch= *(&cfont.font[temp+zz]); 
				for(register byte i=0;i<8;i++)
				{   
				
					if((ch&(1<<(7-i)))!=0)   
					{
						setXY(x+i+(zz*8),y+j,x+i+(zz*8)+1,y+j+1);
						LCD_Write_DATA(fcolor);
					} 
				}
			}
			temp+=(cfont.x_size/8);
		}
	}

	sbi(P_CS, B_CS);
//	clrXY();
}

void UTFT::rotateChar(byte c, int x, int y, int pos, int deg)
{
	byte i,j,ch;
	word temp; 
	int newx,newy;
	double radian;
	radian=deg*0.0175;  

	cbi(P_CS, B_CS);

	temp=((c-cfont.offset)*((cfont.x_size/8)*cfont.y_size))+4;
	for(j=0;j<cfont.y_size;j++) 
	{
		for (int zz=0; zz<(cfont.x_size/8); zz++)
		{
			ch= *(&cfont.font[temp+zz]); 
			for(i=0;i<8;i++)
			{   
				newx=x+(((i+(zz*8)+(pos*cfont.x_size))*cos(radian))-((j)*sin(radian)));
				newy=y+(((j)*cos(radian))+((i+(zz*8)+(pos*cfont.x_size))*sin(radian)));

				setXY(newx,newy,newx+1,newy+1);
				
				if((ch&(1<<(7-i)))!=0)   
				{
					LCD_Write_DATA(fcolor);
				} 
				else  
				{
					if (!_transparent)
						LCD_Write_DATA(bcolor);
				}   
			}
		}
		temp+=(cfont.x_size/8);
	}
	sbi(P_CS, B_CS);
//	clrXY();
}

void UTFT::print( char *st, int x, int y, int deg)
{
	int stl;

	stl = strlen(st);

	if (x==RIGHT)
		x=(disp_x_size+1)-(stl*cfont.x_size);
	if (x==CENTER)
		x=((disp_x_size+1)-(stl*cfont.x_size))/2;
	


	for (register int i=0; i<stl; i++)
		if (deg==0)
			printChar(*st++, x + (i*(cfont.x_size)), y);
		else
			rotateChar(*st++, x, y, i, deg);
}

void UTFT::print(String st, int x, int y, int deg)
{
	char buf[st.length()+1];

	st.toCharArray(buf, st.length()+1);
	print(buf, x, y, deg);
}


byte UTFT::printNumI(long num, int x, int y, int length, char filler)
{
	char st[27];
    st[26]=0;
	boolean neg=false;
	int c=0;
    
	if (num==0)
	{   
        c++;
	    st[25]=48;
	}
	else
	{   
   		if (num<0)
		{
			neg=true;
			num=-num;            
		}
	  
		while (num>0)
		{   
            c++;        
			st[26-c]=48+(num % 10);			
			num=(num-(num % 10))/10;
		}
	  
		if (neg)
		{
			c++;
            st[26-c]=45;
		}
	}  
	while (length>c)
	{			
		c++;
        st[26-c]=filler;
	}

	print(&st[26-c],x,y);
	return c;
}

void UTFT::printNumF(double num, byte dec, int x, int y, char divider, int length, char filler)
{
	char st[27];
	boolean neg=false;

	if (dec<1)
		dec=1;
	else if (dec>5)
		dec=5;

	if (num<0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.')
	{
		for (unsigned int i=0; i<sizeof(st); i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
			for (unsigned int i=1; i<sizeof(st); i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
			for (unsigned int i=0; i<sizeof(st); i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y);
}

void UTFT::setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
}

uint8_t* UTFT::getFont()
{
	return cfont.font;
}

uint8_t UTFT::getFontXsize()
{
	return cfont.x_size;
}

uint8_t UTFT::getFontYsize()
{
	return cfont.y_size;
}


void UTFT::drawBitmapToDark(int x, int y, int sx, int sy, bitmapdatatype data, int iterance, int scale)
{
byte r,g,b; 
word c;	
	    cbi(P_CS, B_CS);
		for (register int i=0;i<iterance ;i++)
		{	
			setXY(x, y, x + sx*scale - 1, y + sy*scale - 1);
		    for (register int ty=0; ty<sy; ty++)
			{
				for (register int tsy=0; tsy<scale; tsy++)
					for (register int tx=0; tx<sx; tx++)
					{   
					    c=*(&data[(ty*sx)+tx]);
				        if ((c&(0x001F)) > (i*32/iterance))
				            b=(c&(0x001F)) - (i*32/iterance);
			          	else
					        b = 0;
				        if (((c&(0x07E0))>>5) > (i*64/iterance))
				            g=((c&(0x07E0))>>5) - (i*64/iterance);
				        else
					        g = 0;
                        if (((c&(0xF800))>>11) > (i*32/iterance))
				            r=((c&(0xF800))>>11) - (i*32/iterance);
				        else
					        r = 0;
				        c=((r&248)<<8 | (g&252)<<3 | (b&248)>>3);
                        P_IO->WriteMultiple(c, scale);
					//	for (register int tsx=0; tsx<scale; tsx++)
						//	LCD_Write_DATA(c);
					}
			}
           
	    //	delay(200);
		}
		sbi(P_CS, B_CS);
}

void UTFT::drawBitmapR(int x, int y, int sx, int sy, bitmapdatatype data, int rot) // only 0,90,189,270 with fast lcd hw reg 0x36h rotation, need check that register for specific lcd
{
    cbi(P_CS, B_CS);
	switch (rot)
	{
     case 0:
			setXY(x, y, x+sx-1, y+sy-1);
            P_IO->WriteSequence(data, sx * sy);
			break;
     case 1:		    
            LCD_Write_COM_DATA(0x36,0x5C);
            setXY(y,480-x-sy, y+sx-1,480-x-1);
            P_IO->WriteSequence(data, sx * sy);
            LCD_Write_COM_DATA(0x36,0xFC);
			break;
     case 2:			
			LCD_Write_COM_DATA(0x36,0x3C);
            setXY(480-x-sx,320-y-sy,480-x-1,320-y-1);
            P_IO->WriteSequence(data, sx * sy);
            LCD_Write_COM_DATA(0x36,0xFC);
			break;
	 case 3:
			LCD_Write_COM_DATA(0x36,0x9C);
            setXY(320-y-sx, x, 320-y-1, x+sy-1);
            P_IO->WriteSequence(data, sx * sy);
            LCD_Write_COM_DATA(0x36,0xFC);
			break;	
	}
    sbi(P_CS, B_CS);
}

void UTFT::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
    cbi(P_CS, B_CS);
	if (scale==1)
	{
			setXY(x, y, x+sx-1, y+sy-1);
           // P_IO->WriteSequence32(data, (sx * sy)/2 + (sx * sy)%2 );
			P_IO->WriteSequence(data, sx * sy);
	/*		for (tc=0; tc<(sx*sy); tc++)
			{
				LCD_Write_DATA(*(&data[tc]));
			}*/	
	}
	else
	{       
		    setXY(x, y, x + sx*scale - 1, y + sy*scale - 1);
			for (register int ty=0; ty<sy; ty++)
			{
				for (register int tsy=0; tsy<scale; tsy++)
					for (register int tx=0; tx<sx; tx++)
					{   
					    P_IO->WriteMultiple(*(&data[(ty*sx)+tx]), scale);
					//	for (register int tsx=0; tsx<scale; tsx++)
					//		LCD_Write_DATA(*(&data[(ty*sx)+tx]));
					}
			}
			
	}
    sbi(P_CS, B_CS);
	//clrXY();
}

void UTFT::drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
	int newx, newy;
	double radian;
	if (deg==0)
		drawBitmap(x, y, sx, sy, data);
	else
	{
        radian=deg*0.0175;
		cbi(P_CS, B_CS);
		for (register int ty=0; ty<sy; ty++)
			for (register int tx=0; tx<sx; tx++)
			{
				newx=x+rox+(((tx-rox)*cos(radian))-((ty-roy)*sin(radian)));
				newy=y+roy+(((ty-roy)*cos(radian))+((tx-rox)*sin(radian)));
				setXY(newx, newy, newx, newy);
				LCD_Write_DATA(*(&data[(ty*sx)+tx]));
			}
		sbi(P_CS, B_CS);
	}
//	clrXY();
}
void UTFT::screenOrient(byte ort)    //hw oritation by 36h lcd register
{
  cbi(P_CS, B_CS);
	switch (ort)
	{
     case 0:
			LCD_Write_COM_DATA(0x36,0x5C);
			break;
     case 1:		    
            LCD_Write_COM_DATA(0x36,0x3C);
   			break;
     case 2:			
			LCD_Write_COM_DATA(0x36,0x9C);
   			break;
	 case 3:
			LCD_Write_COM_DATA(0x36,0xFC);
	        break; 
	}
    sbi(P_CS, B_CS);
}

void UTFT::lcdOff()
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		LCD_Write_COM(0x28);
		break;
	case CPLD:
		LCD_Write_COM_DATA(0x01,0x0000);
		LCD_Write_COM(0x0F);   
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::lcdOn()
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		LCD_Write_COM(0x29);
		break;
	case CPLD:
		LCD_Write_COM_DATA(0x01,0x0010);
		LCD_Write_COM(0x0F);   
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::setContrast(char c)
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case PCF8833:
		if (c>64) c=64;
		LCD_Write_COM(0x25);
		LCD_Write_DATA(c);
		break;
	}
	sbi(P_CS, B_CS);
}

int UTFT::getDisplayXSize()
{
	return disp_x_size+1;
}

int UTFT::getDisplayYSize()
{	
	return disp_y_size+1;	
}

void UTFT::setBrightness(byte br)
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case CPLD:
		if (br>16) br=16;
		LCD_Write_COM_DATA(0x01,br);
		LCD_Write_COM(0x0F);   
		break;
	case 28:
	//	if (br>16) br=16;
	    LCD_Write_COM_DATA(0x51,br);
        LCD_Write_COM_DATA(0x55,0x01);
        LCD_Write_COM_DATA(0x53,0x2C);
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::setDisplayPage(byte page)
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case CPLD:
		if (page>7) page=7;
		LCD_Write_COM_DATA(0x04,page);
		LCD_Write_COM(0x0F);   
		break;
	}
	sbi(P_CS, B_CS);
}

void UTFT::setWritePage(byte page)
{
	cbi(P_CS, B_CS);
	switch (display_model)
	{
	case CPLD:
		if (page>7) page=7;
		LCD_Write_COM_DATA(0x05,page);
		LCD_Write_COM(0x0F);   
		break;
	}
	sbi(P_CS, B_CS);
}
/*
void UTFT::_convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];
	
	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}
*/
