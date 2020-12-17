/*
  UTFT_Buttons.h - Add-on Library for UTFT: Buttons
  Copyright (C)2016 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library adds simple but easy to use buttons to extend the use
  of the UTFT and URTouch libraries.

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

#ifndef UTFT_Buttons_h
#define UTFT_Buttons_h

#define UTFT_BUTTONS_VERSION	104


#include "../UTFT.h"
#include "../touch/URTouch.h"


#if ((!defined(UTFT_VERSION)) || (UTFT_VERSION<241))
	#error : You will need UTFT v2.41 or higher to use this add-on library...
#endif

#define MAX_BUTTONS	21	// Maximum number of buttons available at one time
#define MAX_SLIDERS	3   // Maximum slider buttons at one time

// Define presets for button status
#define BUTTON_DISABLED			0x0001
//#define BUTTON_SYMBOL			0x0002
//#define BUTTON_SYMBOL_REP_3X	0x0004
#define LABEL_DARK			    0x0008	
#define HAS_BORDER		        0x0010
#define BUTTON_SLIDER	    	0x0020
#define BUTTON_ROUND	    	0x0040
#define BUTTON_ONOFF            0x0080
#define LABEL_INUP              0x0100
#define LABEL_OUTDOWN           0x0200
#define LABEL_TEXTVERT          0x0400
#define IS_OFF                  0x0800    //value for ON-OFF bitmap button
#define BITMAP_ROT90			0x1000
#define BITMAP_ROT180		    0x2000
#define BUTTON_UNUSED			0x8000

typedef void             (*p_func)(void);

typedef struct
{   
	            float			min_v, max_v, cur_v, step_v; 
} slider_type;

typedef struct
{
                 uint16_t			pos_x, pos_y, width, height;
	             uint16_t			flags;
                 char				*label;
                 bitmapdatatype	    data;
			     uint8_t            slindex;
                 p_func             function;
			  
} button_type ;

class UTFT_Buttons
{
	public:
		UTFT_Buttons(UTFT *ptrUTFT, URTouch *ptrURTouch);
   	    int		addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, char *label, uint16_t flags=0, p_func func=NULL);
		int		addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height , float min, float max, float cur, float step, char *label, uint16_t flags=0, p_func func=NULL);
	    void	drawButtons(int start=0);
	    void	drawButton(int buttonID);
		void	enableButton(int buttonID, boolean redraw=false);
		void	disableButton(int buttonID, boolean redraw=false);
		void	relabelButton(int buttonID, char *label, boolean redraw=false);
		boolean	buttonEnabled(int buttonID);
		void	deleteButton(int buttonID);
		void	deleteAllButtons();
        boolean negateOnOff(int buttonID);
        boolean getOnOffValue(int buttonID);
    	int	    checkButtons();
		void	setTextFont(uint8_t* font);
	//	void	setSymbolFont(uint8_t* font);
	//	void	setColors(word atxt, word iatxt, word brd, word brdhi, word back); 
        boolean isSlider(int buttonID);
        float   getSliderValue(int buttonID);
        p_func  getFunction(int buttonID);
        UTFT		*_UTFT;
		URTouch		*_URTouch;
        word		color_txt, color_txt_inactive, color_bgr, color_bline, color_hilite;
		
    protected:
   		button_type	buttons[MAX_BUTTONS];
		slider_type	sliders[MAX_SLIDERS];
		uint8_t		*_font_text;
};

extern UTFT_Buttons button;
#endif
