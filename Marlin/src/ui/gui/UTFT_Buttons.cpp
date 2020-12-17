/*
  UTFT_Buttons.cpp - Add-on Library for UTFT: Buttons
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

#include "UTFT_Buttons.h"


UTFT_Buttons::UTFT_Buttons(UTFT *ptrUTFT, URTouch *ptrURTouch)
{
	_UTFT = ptrUTFT;
	_URTouch = ptrURTouch;
	deleteAllButtons();
	color_txt				= COLOR_VIOLET;
	color_txt_inactive	    = COLOR_GRAY;
	color_bgr	        	= COLOR_DARKGREY2;
	color_bline  			= COLOR_OLIVE;
	color_hilite			= COLOR_RED;
	_font_text				= NULL;
//	_font_symbol			= NULL;
}

int UTFT_Buttons::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, char *label, uint16_t flags, p_func func)
{
	int btcnt = 0;
  
	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) and (btcnt<MAX_BUTTONS))
		btcnt++;
  
	if (btcnt == MAX_BUTTONS)
		return -1;
	else
	{  
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags;
		buttons[btcnt].label  = label;
		buttons[btcnt].data   = data;
        buttons[btcnt].function   = func;
        buttons[btcnt].slindex   = -1;
    	return btcnt;
	}
}

int UTFT_Buttons::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max, float current, float step, char *label, uint16_t flags, p_func func)
{
	int btcnt = 0;
	uint8_t sindex = 0;
  
	while (((buttons[btcnt].flags & BUTTON_UNUSED) == 0) and (btcnt<MAX_BUTTONS))
	   { 
		 if (buttons[btcnt].flags & BUTTON_SLIDER)
		     sindex++;
		 btcnt++;
	   }
  
	if ((btcnt == MAX_BUTTONS) or (sindex == MAX_SLIDERS))
		return -1;
	else
	{
		buttons[btcnt].pos_x  = x;
		buttons[btcnt].pos_y  = y;
		buttons[btcnt].width  = width;
		buttons[btcnt].height = height;
		buttons[btcnt].flags  = flags | BUTTON_SLIDER ;
		buttons[btcnt].label  = label;
		buttons[btcnt].data   = NULL;
        buttons[btcnt].function   = func;
        buttons[btcnt].slindex   = sindex;
        sliders[sindex].min_v   = min;
        sliders[sindex].max_v   = max;
        sliders[sindex].cur_v   = current;
        sliders[sindex].step_v   = step;
		return btcnt;
	}
}

void UTFT_Buttons::drawButtons(int start)
{
	for (register int i=start;i<MAX_BUTTONS;i++)
	{
		if ((buttons[i].flags & BUTTON_UNUSED) == 0)
			drawButton(i);
	}
}

void UTFT_Buttons::drawButton(int buttonID)
{
	int		text_x;
    int     text_y;
	float       px;
	uint8_t	*_font_current = _UTFT->getFont();;
	word	_current_color = _UTFT->getColor();
	word	_current_back  = _UTFT->getBackColor();

    if (buttons[buttonID].flags & BUTTON_SLIDER)   //slider draw
	{       
       // calculate slider position from data value
	   px = buttons[buttonID].pos_x + buttons[buttonID].width - 2 * buttons[buttonID].height - ( buttons[buttonID].width - 3 * buttons[buttonID].height) * ((sliders[buttons[buttonID].slindex].max_v - sliders[buttons[buttonID].slindex].cur_v) / (sliders[buttons[buttonID].slindex].max_v - sliders[buttons[buttonID].slindex].min_v));
	   _UTFT->setColor(color_bline);
		if (buttons[buttonID].flags & BUTTON_ROUND)
           {
			_UTFT->drawRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x + buttons[buttonID].width, buttons[buttonID].pos_y + buttons[buttonID].height );
            _UTFT->setColor(color_bgr);
            _UTFT->fillRoundRect(buttons[buttonID].pos_x + 1, buttons[buttonID].pos_y + 1, buttons[buttonID].pos_x + buttons[buttonID].height - 1, buttons[buttonID].pos_y + buttons[buttonID].height - 1);
            _UTFT->fillRoundRect(buttons[buttonID].pos_x + buttons[buttonID].width - buttons[buttonID].height + 1, buttons[buttonID].pos_y + 1, buttons[buttonID].pos_x + buttons[buttonID].width -1, buttons[buttonID].pos_y + buttons[buttonID].height -1);
		    _UTFT->setColor(color_txt);
	        _UTFT->fillRoundRect(px + 1, buttons[buttonID].pos_y + 1, px + buttons[buttonID].height - 1, buttons[buttonID].pos_y + buttons[buttonID].height - 1);
		   }
		else  
		   {
			_UTFT->drawRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x + buttons[buttonID].width, buttons[buttonID].pos_y + buttons[buttonID].height );
            _UTFT->setColor(color_bgr);
            _UTFT->fillRect(buttons[buttonID].pos_x + 1, buttons[buttonID].pos_y + 1, buttons[buttonID].pos_x + buttons[buttonID].height - 1, buttons[buttonID].pos_y + buttons[buttonID].height - 1);
            _UTFT->fillRect(buttons[buttonID].pos_x + buttons[buttonID].width - buttons[buttonID].height + 1, buttons[buttonID].pos_y + 1, buttons[buttonID].pos_x + buttons[buttonID].width - 1, buttons[buttonID].pos_y + buttons[buttonID].height - 1);
		    _UTFT->setColor(color_txt);
	        _UTFT->fillRect(px + 1, buttons[buttonID].pos_y + 1, px + buttons[buttonID].height - 1, buttons[buttonID].pos_y + buttons[buttonID].height - 1);
		   }
		_UTFT->setColor(COLOR_WHITE);
		_UTFT->drawHLine(buttons[buttonID].pos_x + buttons[buttonID].height / 4, buttons[buttonID].pos_y + buttons[buttonID].height / 2, buttons[buttonID].height / 2);
        _UTFT->drawHLine(buttons[buttonID].pos_x + buttons[buttonID].width - buttons[buttonID].height * 0.75, buttons[buttonID].pos_y + buttons[buttonID].height / 2 , buttons[buttonID].height / 2);
        _UTFT->drawVLine(buttons[buttonID].pos_x + buttons[buttonID].width - buttons[buttonID].height / 2, buttons[buttonID].pos_y + buttons[buttonID].height / 4, buttons[buttonID].height / 2);	  

	}   
	else              // normal and bitmap draw
	{
        if (buttons[buttonID].data != NULL)   // is bitmap?
		{ 
			switch (buttons[buttonID].flags & (BITMAP_ROT90 | BITMAP_ROT180 | IS_OFF))
		       {
               case 0 :
				    _UTFT->drawBitmapR(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height, buttons[buttonID].data,0);
		            break;
		       case BITMAP_ROT90 :
                    _UTFT->drawBitmapR(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].height, buttons[buttonID].width,  buttons[buttonID].data, 1); // swaped heitht and width
		            break;
			   case BITMAP_ROT180 :
                    _UTFT->drawBitmapR(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].width, buttons[buttonID].height, buttons[buttonID].data, 2) ;
		            break;
               case (BITMAP_ROT90 | BITMAP_ROT180) :
                    _UTFT->drawBitmapR(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].height, buttons[buttonID].width, buttons[buttonID].data, 3); // swaped heitht and width
		            break;
   			   }			
		}
		else
        {   
            _UTFT->setColor(color_bgr);
			if  (buttons[buttonID].flags & BUTTON_ROUND)
		        _UTFT->fillRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
            else
		        _UTFT->fillRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
        } 
        if (buttons[buttonID].flags & HAS_BORDER)
		{
			if ((buttons[buttonID].flags & BUTTON_DISABLED))
				_UTFT->setColor(color_txt_inactive);
			else
				_UTFT->setColor(color_bline);

            if (buttons[buttonID].flags & BUTTON_ROUND)
			    _UTFT->drawRoundRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
			else
                _UTFT->drawRect(buttons[buttonID].pos_x, buttons[buttonID].pos_y, buttons[buttonID].pos_x+buttons[buttonID].width, buttons[buttonID].pos_y+buttons[buttonID].height);
        }
    }
    // label draw
    if (buttons[buttonID].label)
    {  
   		   if (buttons[buttonID].flags & BUTTON_DISABLED)
			  _UTFT->setColor(color_txt_inactive);
		   else
			  _UTFT->setColor(color_txt);
		   if (buttons[buttonID].flags & LABEL_DARK)
		      _UTFT->setColor(COLOR_BLACK);
		    

	//	   if (buttons[buttonID].flags & BUTTON_SYMBOL)
	//	      _UTFT->setFont(_font_symbol);
	//	   else	 
			  _UTFT->setFont(_font_text);

  /*        switch (buttons[buttonID].flags & (BUTTON_ONOFF | LABEL_OUTDOWN | LABEL_INUP | LABEL_TEXTVERT ))
               {
		       case BUTTON_ONOFF :
                    text_x = buttons[buttonID].pos_x - ((strlen(buttons[buttonID].label) + 1) * _UTFT->getFontXsize());
			        text_y = (buttons[buttonID].height/2) - (_UTFT->getFontYsize()/2) + buttons[buttonID].pos_y;
		            break;
			   case LABEL_OUTDOWN :
				    text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
                    text_y = buttons[buttonID].pos_y + buttons[buttonID].height + (_UTFT->getFontYsize()/2);
		            break;
               case LABEL_INUP :
                    text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
			        text_y = buttons[buttonID].pos_y + 1;
		            break;
               case LABEL_TEXTVERT :
				    char * pch;
		            int numspc=0;
                    pch=strchr(buttons[buttonID].label,' ');
                    while (pch!=NULL)    // calculate number of spaces in label
                     {
                      numspc++;
                      pch=strchr(pch+1,' ');
                     }
                   // char str[] ="- This, a sample string.";
	                if (numspc == 0)
                       _UTFT->print(buttons[buttonID].label, text_x, text_y);
	                else
		            {
			          int distspc = numspc + 1;
		              numspc= 0;
                      char* tok=buttons[buttonID].label; 
                      pch = strtok(tok," ");
                      _UTFT->printNumI(distspc, 10, 10,1);
                      _UTFT->printNumI(strlen(pch), 10, 30,2);
                      _UTFT->print(pch, 150, 30);
                      while (pch != NULL)
                       {
                       text_x = ((buttons[buttonID].width/2) - ((strlen(pch) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
                       text_y = (buttons[buttonID].height/2) - ((distspc + 2 * numspc) * _UTFT->getFontYsize())/2 + buttons[buttonID].pos_y;
                       _UTFT->print(pch, text_x, text_y);
                       numspc++;
                       pch = strtok(NULL," ");
                       }
		            }
				    break;
               default :
				    text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
				    text_y = (buttons[buttonID].height/2) - (_UTFT->getFontYsize()/2) + buttons[buttonID].pos_y;
		            break;
			   }			*/

		   // calculate position
           _UTFT->setBackColor(COLOR_TRANSPARENT); //TRANSPARENT
		   if (buttons[buttonID].flags & BUTTON_ONOFF)
			       text_x = buttons[buttonID].pos_x - ((strlen(buttons[buttonID].label) + 1) * _UTFT->getFontXsize());
		   else
                   text_x = ((buttons[buttonID].width/2) - ((strlen(buttons[buttonID].label) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
           if (buttons[buttonID].flags & LABEL_OUTDOWN)
			       text_y = buttons[buttonID].pos_y + buttons[buttonID].height + (_UTFT->getFontYsize()/2);
		   else
                   text_y = (buttons[buttonID].height/2) - (_UTFT->getFontYsize()/2) + buttons[buttonID].pos_y;
           if (buttons[buttonID].flags & LABEL_INUP)
			   text_y = buttons[buttonID].pos_y + 1;   
		   if (buttons[buttonID].flags & BUTTON_SLIDER)
			   text_y = buttons[buttonID].pos_y - _UTFT->getFontYsize() - 2;    
			 		      
		   
           if (buttons[buttonID].flags & LABEL_TEXTVERT)
		   {
		      char * pch;
		      int numspc=0;
              pch=strchr(buttons[buttonID].label,' ');
              while (pch!=NULL)    // calculate number of spaces in label
                 {
                 numspc++;
                 pch=strchr(pch+1,' ');
                 }
           // char str[] ="- This, a sample string.";
	          if (numspc == 0)
                 _UTFT->print(buttons[buttonID].label, text_x, text_y);
	          else
		      {
			     int distspc = numspc + 1;
		         numspc= 0;
                 char* tok=buttons[buttonID].label; 
                 pch = strtok(tok," ");
                 _UTFT->printNumI(distspc, 10, 10,1);
                 _UTFT->printNumI(strlen(pch), 10, 30,2);
                 _UTFT->print(pch, 150, 30);
                 while (pch != NULL)
                   {
                   text_x = ((buttons[buttonID].width/2) - ((strlen(pch) * _UTFT->getFontXsize())/2)) + buttons[buttonID].pos_x;
                   text_y = (buttons[buttonID].height/2) - ((distspc + 2 * numspc) * _UTFT->getFontYsize())/2 + buttons[buttonID].pos_y;
                   _UTFT->print(pch, text_x, text_y);
                   numspc++;
                   pch = strtok(NULL," ");
                   }
		       }
		   }
		   else 
			  _UTFT->print(buttons[buttonID].label, text_x, text_y); 
        
		//   if ((buttons[buttonID].flags & BUTTON_SYMBOL) and (buttons[buttonID].flags & BUTTON_SYMBOL_REP_3X))
		//   {
		//	_UTFT->print(buttons[buttonID].label, text_x-_UTFT->getFontXsize(), text_y);
		//	_UTFT->print(buttons[buttonID].label, text_x+_UTFT->getFontXsize(), text_y);
		//   }
          
	}
	_UTFT->setFont(_font_current);
	_UTFT->setColor(_current_color);
	_UTFT->setBackColor(_current_back);
}

void UTFT_Buttons::enableButton(int buttonID, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags &= ~BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

void UTFT_Buttons::disableButton(int buttonID, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].flags |= BUTTON_DISABLED;
		if (redraw)
			drawButton(buttonID);
	}
}

void UTFT_Buttons::relabelButton(int buttonID, char *label, boolean redraw)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
	{
		buttons[buttonID].label = label;
		if (redraw)
			drawButton(buttonID);
	}
}

boolean UTFT_Buttons::buttonEnabled(int buttonID)
{
	return !(buttons[buttonID].flags & BUTTON_DISABLED);
}
    
void UTFT_Buttons::deleteButton(int buttonID)
{
	if (!(buttons[buttonID].flags & BUTTON_UNUSED))
		buttons[buttonID].flags = BUTTON_UNUSED;
}

void UTFT_Buttons::deleteAllButtons()
{
	for (register int i=0; i < MAX_BUTTONS; i++)
	{
	buttons[i].flags=BUTTON_UNUSED;
	}	
}

boolean UTFT_Buttons::negateOnOff(int buttonID)
{
 //	if (!(buttons[buttonID].flags & BUTTON_ONOFF)) return -1;
    buttons[buttonID].flags ^= IS_OFF; // bit negate
	return	(buttons[buttonID].flags & IS_OFF);		
}

boolean UTFT_Buttons::getOnOffValue(int buttonID)
{
 //	if (!(buttons[buttonID].flags & BUTTON_ONOFF)) return -1;
	return	(buttons[buttonID].flags & IS_OFF);
		
}

int UTFT_Buttons::checkButtons()
{
    if (_URTouch->dataAvailable() == true)
    {
		_URTouch->read();
        float    px, lx;
	    int	                result = -1;
		register int	    touch_x = _URTouch->getX();
		register int	    touch_y = _URTouch->getY();
		word	_current_color = _UTFT->getColor();
  
		for (register int i=0;i<MAX_BUTTONS;i++)
		{
			if (((buttons[i].flags & BUTTON_UNUSED) == 0) && ((buttons[i].flags & BUTTON_DISABLED) == 0) && (result == -1))
			{
				if ((touch_x >= buttons[i].pos_x) and (touch_x <= (buttons[i].pos_x + buttons[i].width)) and (touch_y >= buttons[i].pos_y) and (touch_y <= (buttons[i].pos_y + buttons[i].height)))
					result = i;
			}
		}
		if (result != -1) 
		{
             if (buttons[result].flags & BUTTON_SLIDER)   // check slider button
			 {    
					// calculate old position from inner value
					lx = buttons[result].pos_x + buttons[result].width - 2 * buttons[result].height - ( buttons[result].width - 3 * buttons[result].height) * ((sliders[buttons[result].slindex].max_v - sliders[buttons[result].slindex].cur_v) / (sliders[buttons[result].slindex].max_v - sliders[buttons[result].slindex].min_v));
					
					if ((touch_x >= buttons[result].pos_x) and (touch_x <= (buttons[result].pos_x +  buttons[result].height)))     // touch sign -
				        {				
                        if   ((sliders[buttons[result].slindex].cur_v - sliders[buttons[result].slindex].step_v) >= sliders[buttons[result].slindex].min_v)
						        sliders[buttons[result].slindex].cur_v -= sliders[buttons[result].slindex].step_v;
                        while (_URTouch->dataAvailable() == true) {}; // wait for untouch
						}
					   
                    if ((touch_x >= (buttons[result].pos_x + buttons[result].width - buttons[result].height)) and (touch_x <= (buttons[result].pos_x +  buttons[result].width))) // touch sign +
				        {                 
                        if   ((sliders[buttons[result].slindex].cur_v + sliders[buttons[result].slindex].step_v) <= sliders[buttons[result].slindex].max_v)
						        sliders[buttons[result].slindex].cur_v += sliders[buttons[result].slindex].step_v;
                        while (_URTouch->dataAvailable() == true) {}; // wait for untouch
						}					   
				
				    if ((touch_x >= (buttons[result].pos_x + 1.5 * buttons[result].height)) and (touch_x <= (buttons[result].pos_x + buttons[result].width - 1.5 * buttons[result].height))) // touch slider
				        {
						sliders[buttons[result].slindex].cur_v = sliders[buttons[result].slindex].max_v - (buttons[result].pos_x + buttons[result].width - 1.5 * buttons[result].height - touch_x) / (buttons[result].width - 3 * buttons[result].height) * (sliders[buttons[result].slindex].max_v - sliders[buttons[result].slindex].min_v);
                        sliders[buttons[result].slindex].cur_v =((int)((sliders[buttons[result].slindex].cur_v - sliders[buttons[result].slindex].min_v) / (sliders[buttons[result].slindex].step_v))) * (sliders[buttons[result].slindex].step_v) + sliders[buttons[result].slindex].min_v;	   
					    }
					// if new position change then draw
				    px = buttons[result].pos_x + buttons[result].width - 2 * buttons[result].height - ( buttons[result].width - 3 * buttons[result].height) * ((sliders[buttons[result].slindex].max_v - sliders[buttons[result].slindex].cur_v) / (sliders[buttons[result].slindex].max_v - sliders[buttons[result].slindex].min_v));
					if ((int)px != (int)lx)
					{
					_UTFT->setColor(COLOR_BLACK);
                    if (buttons[result].flags & BUTTON_ROUND)
						{
					    _UTFT->fillRoundRect( lx + 1, buttons[result].pos_y + 1, lx + buttons[result].height - 1, buttons[result].pos_y + buttons[result].height - 1);
					    _UTFT->setColor(color_txt);
					    _UTFT->fillRoundRect( px + 1, buttons[result].pos_y + 1, px + buttons[result].height - 1, buttons[result].pos_y + buttons[result].height - 1);
				        }
                    else 
						{
					    _UTFT->fillRect( lx + 1, buttons[result].pos_y + 1, lx + buttons[result].height - 1, buttons[result].pos_y + buttons[result].height - 1);
					    _UTFT->setColor(color_txt);
					    _UTFT->fillRect( px + 1, buttons[result].pos_y + 1, px + buttons[result].height - 1, buttons[result].pos_y + buttons[result].height - 1);
				        }
					}
			}	
			else                                             // check bitmap or normal button  
		    {
				 if (buttons[result].flags & HAS_BORDER)
			     {     
                        if (buttons[result].flags & BUTTON_ONOFF)
					       { 
						   if (negateOnOff(result))
						   {
                               _UTFT->setColor(COLOR_BLACK);
                               _UTFT->fillRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
						   }  
                           else
							   _UTFT->drawBitmap(buttons[result].pos_x, buttons[result].pos_y, buttons[result].width, buttons[result].height, buttons[result].data);
							   
						   }
			    	   _UTFT->setColor(color_hilite);
				       if (buttons[result].flags & BUTTON_ROUND)   
				          _UTFT->drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
                       else 
						  _UTFT->drawRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
					  
                       while (_URTouch->dataAvailable() == true) {}; // wait for untouch
                       
					   _UTFT->setColor(color_bline);
                       if (buttons[result].flags & BUTTON_ROUND)   
				          _UTFT->drawRoundRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
                       else 
						  _UTFT->drawRect(buttons[result].pos_x, buttons[result].pos_y, buttons[result].pos_x+buttons[result].width, buttons[result].pos_y+buttons[result].height);
				 }
				 else
                     while (_URTouch->dataAvailable() == true) {}; // wait for untouch
			}
		}
		_UTFT->setColor(_current_color);
		return result;	
	}
	else
		return -1;	
}

void UTFT_Buttons::setTextFont(uint8_t* font)
{
	_font_text = font;
}

/*void UTFT_Buttons::setSymbolFont(uint8_t* font)
{
	_font_symbol = font;
}  */

/*void UTFT_Buttons::setButtonColors(word atxt, word iatxt, word brd, word brdhi, word back)
{
	_color_text				= atxt;
	_color_text_inactive	= iatxt;
	_color_background		= back;
	_color_border			= brd;
	_color_hilite			= brdhi;
}*/

boolean UTFT_Buttons::isSlider(int buttonID)
{
	return	(buttons[buttonID].flags & BUTTON_SLIDER);		
}

float UTFT_Buttons::getSliderValue(int buttonID)
{
	if (!(buttons[buttonID].flags & BUTTON_SLIDER)) return -1;
	return	sliders[buttons[buttonID].slindex].cur_v;
		
}

p_func UTFT_Buttons::getFunction(int buttonID)
{
	return buttons[buttonID].function;		
}