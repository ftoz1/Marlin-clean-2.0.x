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


#include "UTFT_Menu.h"

void UTFT_Menu::addWinItems()
{
 int k = 0;
 int l = 0;

//  add submenu buttons to window buffer array
 
   for (int j=0; j < nb_y ; j++ )
   {  
	  for (int i=0; i < nb_x ; i++ )
	  {
        if ((p_item[curr1_idx + k].flag & ITEM_FIRST)  || (p_item[curr1_idx + k].function == NULL))
			l++;
        if (l < 2) 
	    {
   	      _UTFT_Buttons->addButton(p_size[1].x + pos_space + i * (p_size[1].x1 -p_size[1].x) / nb_x, p_size[1].y + pos_space + j * (p_size[1].y1 - p_size[1].y) / nb_y, (p_size[1].x1 - p_size[1].x) / nb_x - 2 * pos_space, (p_size[1].y1 - p_size[1].y) / nb_y - 2 * pos_space,NULL, p_item[curr1_idx + k].label, (buttons_flag | HAS_BORDER) , p_item[curr1_idx + k].function);
          k++;
	    }
	  }                
   }

}

UTFT_Menu::UTFT_Menu(UTFT_Buttons *ptrUTFT_Buttons, size_type *ptrsize, drive_type *ptrdrive, slot_type *ptrslot, item_type *ptrmenu, byte nbx, byte nby, boolean ort)
{
	_UTFT_Buttons = ptrUTFT_Buttons;
    _font1				    = NULL;
    _font2				    = NULL;
    
	scr_orient              = ort;
	nb_x                    = nbx;
	nb_y                    = nby;
	text_x                  = 0;
	text_y                  = 0;
	path_x                  = 0;
	textorder               = LEFT;
	buttons_flag            = BUTTON_ROUND ;    
	p_size                  = ptrsize;
	p_drive                 = ptrdrive;
    p_slot                  = ptrslot;
	p_item                  = ptrmenu;
	pos_space               = BUT_SPACE;
    in_menu                 = true;
    press_slider            = false;
	press_idx               = -1;      // index of current button pressed
    deep1_idx               = 1;      // index of first item with current deep -- main item has special function so skip
    curr1_idx               = 1;      // index of first item in current menu   -- main item has special function so skip
	bdrive_cnt              = 0;
    bshort_cnt              = 0;
    deep                    = 0;


  // fill drive button
  for ( int i = 0 ; p_drive[i].function != NULL ; i++ )
	{ 
	 _UTFT_Buttons->addButton( p_drive[i].x, p_drive[i].y, p_drive[i].width, p_drive[i].height, p_drive[i].data, NULL, buttons_flag, p_drive[i].function);
	 bdrive_cnt++;
	}
  bshort_cnt = bdrive_cnt;
  // fill slot button
  for ( int i = 0 ; p_slot[i].function != NULL ; i++ )
	{ 	  
     _UTFT_Buttons->addButton(((i - (i/4)*4)*(XRES/4-10) + 20), ((i/4)*50 + 10), p_slot[i].width, p_slot[i].height, p_slot[i].data, p_slot[i].label, (p_slot[i].flag | buttons_flag), p_slot[i].function);
	 bshort_cnt++;
	}
  // fill windows items
   addWinItems();
}

void UTFT_Menu::setTextXY(byte tx, byte ty)   // if ty not specify, it only set text_x param
{
  text_x = p_size[1].x + 5 + tx*(_UTFT_Buttons->_UTFT->getFontXsize());
  if (ty != 255)
    text_y = p_size[1].y + 3 + ty*(_UTFT_Buttons->_UTFT->getFontYsize());
}

void UTFT_Menu::drawSlotVal(int slt, int val, word textcol, boolean type)
{	         
	    int x,y;
		y= (slt/4)*50 + 7 + 26*type;
        x= (slt - (slt/4)*4)*(XRES/4-10) + 65;
        _UTFT_Buttons->_UTFT->setColor(textcol);
        _UTFT_Buttons->_UTFT->setFont(_font1);
        _UTFT_Buttons->_UTFT->printNumI(val,x,y,3);		
}

void UTFT_Menu::clrWinItems()  // delete all buttons from window buffer array
{
     for (int i=bshort_cnt; i < MAX_BUTTONS; i++)
		 _UTFT_Buttons->deleteButton(i);
}

void UTFT_Menu::drawPage()
{
    _UTFT_Buttons->_UTFT->setColor(COLOR_BLACK);
    _UTFT_Buttons->_UTFT->clrScr();
    _UTFT_Buttons->drawButtons();
     drawPathFrame();
	 for ( int i = 0 ; p_slot[i].function != NULL ; i++ )
	{ 
	 drawSlotVal(i, p_slot[i].val1, p_slot[i].col1, 0);
     drawSlotVal(i, p_slot[i].val2, p_slot[i].col2, 1);
	}
}

void UTFT_Menu::drawWin()
{
 //   _UTFT_Buttons->setColors(color_txt, word iatxt, word brd, word brdhi, color_bgr);
    _UTFT_Buttons->drawButtons(bshort_cnt);
	
}

void UTFT_Menu::drawWinFrame()
{   
    _UTFT_Buttons->_UTFT->setColor(_UTFT_Buttons->color_bline);
	if (buttons_flag & BUTTON_ROUND)
     _UTFT_Buttons->_UTFT->drawRoundRect(p_size[1].x, p_size[1].y, p_size[1].x1, p_size[1].y1);  
	else    
     _UTFT_Buttons->_UTFT->drawRect(p_size[1].x, p_size[1].y, p_size[1].x1, p_size[1].y1);     	
}

void UTFT_Menu::drawPathFrame()
{
   _UTFT_Buttons->_UTFT->setColor(_UTFT_Buttons->color_bline);
   if (buttons_flag & BUTTON_ROUND)
     _UTFT_Buttons->_UTFT->drawRoundRect(p_size[1].x, p_size[1].y1 + 1, p_size[1].x1, p_size[1].y1 + 27);  
   else        	
     _UTFT_Buttons->_UTFT->drawRect(p_size[1].x, p_size[1].y1 + 1, p_size[1].x1, p_size[1].y1 + 27);	
}

void UTFT_Menu::clrWin()
{      
	  setTextXY(0,0);
      _UTFT_Buttons->_UTFT->setColor(COLOR_BLACK);
      _UTFT_Buttons->_UTFT->fillRect(p_size[1].x, p_size[1].y, p_size[1].x1, p_size[1].y1);     
}


boolean UTFT_Menu::nextWinItems()
 {      
    if (!in_menu) return false;
    int j = curr1_idx + press_idx - bshort_cnt;   // j = press item index in menu table 
 //   if    !(p_item[curr1_idx + press_idx - bshort_cnt].flag & ITEM_SUBMENU
	path[deep] = j;
    deep++;

 // find number of non Func in current deep
    int  num_subm = 0;
    for (int i=deep1_idx; i < j; i++ )
		  if (p_item[i].flag & ITEM_SUBMENU)
		         num_subm++ ;

  // find first index (deep1_idx) with new deep
    deep1_idx=curr1_idx;
    for (int i=curr1_idx; (p_item[i].flag & ITEM_DEEP) == deep; i++ )
		  deep1_idx++ ;
    

  // jump  num_subm * ITEM_FIRST  in new deep and find new current index (curr1_idx)
    for (int i=deep1_idx; num_subm > -1; i++ )
	 {  if (p_item[i].flag & ITEM_FIRST)
		         num_subm-- ;
	    curr1_idx = i ;
	 }
      
    return true;
 }
            
boolean UTFT_Menu::backWinItems()
 {
  if (deep == 0) return false;
  deep--;
  curr1_idx = path[deep];
  int j = 0;
  // find first item in lower deep, first item in menu and put index there
   for (int i=curr1_idx; (p_item[i].flag & ITEM_DEEP) == (deep + 1); i-- )
	   { 
	    deep1_idx  = i ;
	    if ((p_item[i].flag & ITEM_FIRST) && (j == 0))
	        {
	         curr1_idx = i;
             j++;
	        }
	   }
   
  return true;
 }

void UTFT_Menu::goBack()
{ 
	 if (in_menu) 
	    {
		if (!backWinItems()) return;
	    }
	 in_menu= true;
     clrWinItems();
     addWinItems();
     clrWin();
     drawPath();
     drawWin();
     
/*    _UTFT_Buttons->_UTFT->setColor(COLOR_WHITE);
    _UTFT_Buttons->_UTFT->printNumI(press_idx,420,100,3);
    _UTFT_Buttons->_UTFT->printNumI(curr1_idx,420,130,3);
    _UTFT_Buttons->_UTFT->printNumI(deep1_idx,420,160,3);
    _UTFT_Buttons->_UTFT->printNumI(path_deep,420,190,3);
    _UTFT_Buttons->_UTFT->printNumI(in_menu,420,220,3);*/
}

void UTFT_Menu::goNext()
{    
	if (!nextWinItems()) return;
     clrWinItems();
     addWinItems();
     clrWin();
     drawPath();
     drawWin();
     
 /*   _UTFT_Buttons->_UTFT->setColor(COLOR_WHITE);
    _UTFT_Buttons->_UTFT->printNumI(press_idx,420,100,3);
    _UTFT_Buttons->_UTFT->printNumI(curr1_idx,420,130,3);
    _UTFT_Buttons->_UTFT->printNumI(deep1_idx,420,160,3);
    _UTFT_Buttons->_UTFT->printNumI(path_deep,420,190,3);
    _UTFT_Buttons->_UTFT->printNumI(in_menu,420,220,3);*/
}

void UTFT_Menu::goHome()
{ 
     if ((deep == 0) && (in_menu)) return;
     deep = 0;
     deep1_idx = 1;      
     curr1_idx = 1;
     in_menu= true;
     clrWinItems();
     addWinItems();
     clrWin();
     drawPath();
     drawWin();
     
}

p_func UTFT_Menu::checkPage()     // return pointer to press button function
{ 
   press_idx = _UTFT_Buttons->checkButtons();
   if (press_idx == -1) return NULL;
   if ((press_idx >= bdrive_cnt) && (press_idx < bshort_cnt)) 
	    in_menu = false;
   if ((in_menu) && (press_idx >= bshort_cnt)) 
	  {  if    (!(p_item[curr1_idx + press_idx - bshort_cnt].flag & ITEM_SUBMENU))
	         in_menu = false;
	  }
   
   press_slider = _UTFT_Buttons->isSlider(press_idx);
   
  /*  _UTFT_Buttons->_UTFT->setColor(COLOR_WHITE);
    _UTFT_Buttons->_UTFT->printNumI(press_idx,420,100,3);
    _UTFT_Buttons->_UTFT->printNumI(curr1_idx,420,130,3);
    _UTFT_Buttons->_UTFT->printNumI(deep1_idx,420,160,3);
    _UTFT_Buttons->_UTFT->printNumI(path_deep,420,190,3);
    _UTFT_Buttons->_UTFT->printNumI(press_slider,420,220,3);  */
   return _UTFT_Buttons->getFunction(press_idx);  
} 

void UTFT_Menu::drawPath()
{
   int pst_idx = -1;
   int numch;

  //check number of path chars from start to end of the path-string and roll and recalculate if long
  
   do
   {
	  numch =0;
      pst_idx++;
      for ( int i=pst_idx; i < deep ;i++ )
	     {  
		   numch += strlen(p_item[path[i]].label) + 1;	
	     }
   } while (numch > 27);

  // draw path

    _UTFT_Buttons->_UTFT->setColor(COLOR_WHITE);
    _UTFT_Buttons->_UTFT->setFont(_font1);
	textorder = LEFT;
	text_y=p_size[1].y1 + 3;
	text_x=p_size[1].x + 5;
    for (int i=pst_idx; i < deep ;i++ )
	    {  
        print(p_item[path[i]].label);
        print(">");
		}
    path_x = text_x;
   // delete space after last char
    for (int i=numch; i < 27 ;i++ )
	    {  
        print(" ");
		}
}

void UTFT_Menu::setFont(uint8_t* font1, uint8_t* font2)
{	 
	_font1 = font1;
    _font2 = font2;   
}
  	   
float UTFT_Menu::getSliderValue()
{	 
  return _UTFT_Buttons->getSliderValue(press_idx);
}

boolean UTFT_Menu::getOnOffValue()
{	 
  return _UTFT_Buttons->getOnOffValue(press_idx);
}

void UTFT_Menu::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, char *label, uint16_t flags, p_func func)
{	         
	 
       _UTFT_Buttons->addButton(x, y, width, height, data, label, (flags | buttons_flag), func);
}

void UTFT_Menu::addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max, float current, float step, char *label, uint16_t flags, p_func func)
{	         
	   
       _UTFT_Buttons->addButton(x, y, width, height, min, max, current, step, label, (flags | buttons_flag), func);
}


/*
void UTFT_Menu::setMenuColors(word atxt, word iatxt, word brd, word brdhi, word back)
{
	_color_text				= atxt;
	_color_text_inactive	= iatxt;
	_color_background		= back;
	_color_border			= brd;
	_color_hilite			= brdhi;
}
  */
void UTFT_Menu::setEnv(byte nbx , byte nby, byte spc , uint16_t flag)
{	 
	nb_x                    = nbx;
	nb_y                    = nby;
	pos_space               = spc;
	buttons_flag            = flag ;        
}

// printing text into window

void UTFT_Menu::setText(word t_order, word color, boolean font)
{	 
	if (font == 0)
	   _UTFT_Buttons->_UTFT->setFont(_font1);
    else
       _UTFT_Buttons->_UTFT->setFont(_font2);
    _UTFT_Buttons->_UTFT->setColor(color);
	textorder = t_order;    
}


void UTFT_Menu::ln()
{
  text_x = p_size[1].x + 5;
  text_y += _UTFT_Buttons->_UTFT->getFontYsize();
}

void UTFT_Menu::print(char *st)
{	   
    if (textorder==CENTER) 
	{
		_UTFT_Buttons->_UTFT->print(st, CENTER, text_y);
		text_x=((p_size[1].x1 - p_size[1].x)+((strlen(st))*(_UTFT_Buttons->_UTFT->getFontYsize())))/2;
    }
    else
    {
       _UTFT_Buttons->_UTFT->print(st, text_x, text_y);
        text_x += (strlen(st))*(_UTFT_Buttons->_UTFT->getFontXsize());
    }	  
}
void UTFT_Menu::printLn(char *st)
{	
	print(st);
	ln();	  
}

void UTFT_Menu::printPair(char *st, int value, char *ch, byte length)
{	 
	print(st);
    print(ch);
    printNum(value, length); 
//	if (text_x > p_size[1].x1)
	 //   ln();
}

void UTFT_Menu::printPairLn(char *st, int value, char *ch, byte length)
{
   printPair(st, value, ch, length);
   ln();
}
void UTFT_Menu::printNum(int value, byte length)
{
  // _UTFT_Buttons->_UTFT->printNumI(value, text_x, text_y, length);
    text_x += (_UTFT_Buttons->_UTFT->printNumI(value, text_x, text_y, length))*(_UTFT_Buttons->_UTFT->getFontXsize()); 
}
void UTFT_Menu::PathPrint(char *st, int value, byte length)
{	
    _UTFT_Buttons->_UTFT->setColor(COLOR_GREEN);
	text_x = path_x;
    text_y = p_size[1].y1 + 3;
	print(st);
    printNum(value, length); 
    print("     ");
}