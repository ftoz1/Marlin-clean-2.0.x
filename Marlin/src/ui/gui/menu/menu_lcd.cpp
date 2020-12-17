
#include "../../../inc/MarlinConfig.h"
#include "../UTFT_Menu.h"
#include "../../../libs/BL24CXX.h"
// menu brightness

void set_bright()
{
  byte br = menu.getSliderValue();
  tft.setBrightness(br);
  menu.PathPrint("BR=",br);
}

void lcd_bright()
{
  menu.clrWinItems();
  button.addButton( 50, 120, 380, 40, 0, 255, 100, 1,"BRIGHTNESS", BUTTON_ROUND, set_bright);
  menu.clrWin();
  menu.drawWin();
}

// menu tilt
void set_tilt0()
{
  tft.screenOrient(0);
  tft.clrScr();
  menu.drawPage();
}
void set_tilt90()
{
  tft.screenOrient(1);
  tft.clrScr();
  menu.drawPage();
}
void set_tilt180()
{
  tft.screenOrient(2);
  tft.clrScr();
  menu.drawPage();
}
void set_tilt270()
{
  tft.screenOrient(3);
  tft.clrScr();
  menu.drawPage();
}

void lcd_tilt()
{
  menu.clrWinItems();
  button.addButton( 50, 90, 150, 50, NULL,"0 DEG", BUTTON_ROUND | HAS_BORDER, set_tilt0);
  button.addButton( 50, 170, 150, 50, NULL,"90 DEG", BUTTON_ROUND | HAS_BORDER, set_tilt90);
  button.addButton( 280, 90, 150, 50, NULL,"180 DEG", BUTTON_ROUND | HAS_BORDER, set_tilt180);
  button.addButton( 280, 170, 150, 50, NULL,"270 DEG", BUTTON_ROUND | HAS_BORDER, set_tilt270);
  menu.clrWin();
  menu.drawWin();
}

// menu touch
void touch_prec()
{ 
  byte pr = menu.getSliderValue();
  touch.setPrecision(pr);
  menu.PathPrint("TP=",pr);
}
void touch_set()
{ 
  menu.clrWinItems();
  button.addButton( 50, 120, 380, 40, 1, 5, 5, 1,"TOUCH PRECISION", BUTTON_ROUND, touch_prec);
  menu.clrWin();
  menu.drawWin();
}

// menu set menu text color
void txt_red()
{
  byte col = menu.getSliderValue();
  button.color_txt = (button.color_txt & 0x07FF) | (col<<11);
  tft.setColor(button.color_txt);
  tft.fillRoundRect(330,170, 390, 210);
}

void txt_green()
{
  byte col = menu.getSliderValue();
  button.color_txt = (button.color_txt & 0xF81F) | (col<<5);
  tft.setColor(button.color_txt);
  tft.fillRoundRect(330,170, 390, 210);
}

void txt_blue()
{
  byte col = menu.getSliderValue();
  button.color_txt = (button.color_txt & 0xFFE0) | col;
  tft.setColor(button.color_txt);
  tft.fillRoundRect(330,170, 390, 210);
}

void set_color_txt()
{ 
  menu.clrWinItems();
  byte red= button.color_txt >> 11;
  byte green= button.color_txt & 0x7FF >> 5;
  byte blue= button.color_txt & 0x1F;
  button.addButton( 30, 90, 180, 40, 0, 31, red, 1,"RED", BUTTON_ROUND, txt_red);
  button.addButton( 270, 90, 180, 40, 0, 63, green, 1,"GREEN", BUTTON_ROUND, txt_green);
  button.addButton( 30, 170, 180, 40, 0, 31, blue, 1,"BLUE", BUTTON_ROUND, txt_blue);
  menu.clrWin();
  menu.drawWin();
  tft.setColor(button.color_txt);
  tft.fillRoundRect(330,170, 390, 210);
}

// set menu background color
void bgr_red()
{
  byte col = menu.getSliderValue();
  button.color_bgr = (button.color_bgr & 0x07FF) | (col<<11);
  tft.setColor(button.color_bgr);
  tft.fillRoundRect(330,170, 390, 210);
}

void bgr_green()
{
  byte col = menu.getSliderValue();
  button.color_bgr = (button.color_bgr & 0xF81F) | (col<<5);
  tft.setColor(button.color_bgr);
  tft.fillRoundRect(330,170, 390, 210);
}

void bgr_blue()
{
  byte col = menu.getSliderValue();
  button.color_bgr = (button.color_bgr & 0xFFE0) | col;
  tft.setColor(button.color_bgr);
  tft.fillRoundRect(330,170, 390, 210);
}

void set_color_bgr()
{ 
  menu.clrWinItems();
  byte red= button.color_bgr >> 11;
  byte green= button.color_bgr & 0x7FF >> 5;
  byte blue= button.color_bgr & 0x1F;
  button.addButton( 30, 90, 180, 40, 0, 31, red, 1,"RED", BUTTON_ROUND, bgr_red);
  button.addButton( 270, 90, 180, 40, 0, 63, green, 1,"GREEN", BUTTON_ROUND, bgr_green);
  button.addButton( 30, 170, 180, 40, 0, 31, blue, 1,"BLUE", BUTTON_ROUND, bgr_blue);
  menu.clrWin();
  menu.drawWin();
  tft.setColor(button.color_bgr);
  tft.fillRoundRect(330,170, 390, 210);
}

// set menu border line
void line_red()
{
  byte col = menu.getSliderValue();
  button.color_bline = (button.color_bline & 0x07FF) | (col<<11);
  tft.setColor(button.color_bline);
  tft.fillRoundRect(330,170, 390, 210);
  menu.drawPathFrame();
}

void line_green()
{
  byte col = menu.getSliderValue();
  button.color_bline = (button.color_bline & 0xF81F) | (col<<5);
  tft.setColor(button.color_bline);
  tft.fillRoundRect(330,170, 390, 210);
  menu.drawPathFrame();
}

void line_blue()
{
  byte col = menu.getSliderValue();
  button.color_bline = (button.color_bline & 0xFFE0) | col;
  tft.setColor(button.color_bline);
  tft.fillRoundRect(330,170, 390, 210);
  menu.drawPathFrame();
}

void set_color_bline()
{ 
  menu.clrWinItems();
  byte red= button.color_bline >> 11;
  byte green= button.color_bline & 0x7FF >> 5;
  byte blue= button.color_bline & 0x1F;
  button.addButton( 30, 90, 180, 40, 0, 31, red, 1,"RED", BUTTON_ROUND, line_red);
  button.addButton( 270, 90, 180, 40, 0, 63, green, 1,"GREEN", BUTTON_ROUND, line_green);
  button.addButton( 30, 170, 180, 40, 0, 31, blue, 1,"BLUE", BUTTON_ROUND, line_blue);
  menu.clrWin();
  menu.drawWin();
  tft.setColor(button.color_bline);
  tft.fillRoundRect(330,170, 390, 210);
}

// set menu xy
void xy_16()
{
  menu.nb_x = 1;
  menu.nb_y = 6;
  menu.PathPrint("1x",menu.nb_y);
}

void xy_23()
{
  menu.nb_x = 2;
  menu.nb_y = 3;
  menu.PathPrint("2x",menu.nb_y);
}

void xy_32()
{
  menu.nb_x = 3;
  menu.nb_y = 2;
  menu.PathPrint("3x",menu.nb_y);
}

void set_space()
{
   menu.pos_space = menu.getSliderValue();
   menu.PathPrint("PS=",menu.pos_space);
}

void set_menu_xy()
{ 
 menu.clrWinItems();
  button.addButton( 50, 90, 80, 40, NULL,"1x6", BUTTON_ROUND | HAS_BORDER , xy_16);
  button.addButton( 200, 90, 80, 40, NULL,"2x3", BUTTON_ROUND | HAS_BORDER , xy_23);
  button.addButton( 350, 90, 80, 40, NULL,"3x2", BUTTON_ROUND | HAS_BORDER , xy_32);
  button.addButton( 120, 170, 230, 40, 0, 10, menu.pos_space, 1,"BUTTON SPACE", BUTTON_ROUND, set_space);
  menu.clrWin();
  menu.drawWin();
}


// save settings
void set_print1()
{
 // WRITE(I2C_GPIO, LOW);
 uint16_t br=menu.getSliderValue();
 uint8_t yes0[5]= {0,1,2,3,4};
// uint8_t yes1 = 128;
 
//  WRITE(I2C_GPIO, HIGH);
//          eeprom.write(br, (uint8_t*)&yes0, sizeof(yes0));
//eeprom.writeOneByte(br,128);
  menu.setTextXY(1,1);
//  menu.printPair("",yes1,">");
  menu.printPair("",yes0[0],":");
  menu.printPair("",yes0[1],":");
  menu.printPair("",yes0[2],":");
  menu.printPair("",yes0[3],":");
  menu.printPair("",yes0[4],":");  
  
}
void save_settings()
{
 
 menu.clrWinItems();
 menu.clrWin();
// uint8_t yes1[5]= {0,0,0,0,0};

// eeprom.read(10, (uint8_t*)&yes1, sizeof(yes1));
 menu.setText(LEFT, COLOR_WHITE); 
 button.addButton( 30, 170, 230, 40, 0, 10, 10, 1,"ADDR SPACE", BUTTON_ROUND, set_print1);
 menu.drawWin(); 
}

// load settings
void set_print()
{
 uint16_t br=menu.getSliderValue();
 uint8_t yes0[5]= {0,1,2,3,4};
 uint8_t yes1 = 1;
//              eeprom.read(br, (uint8_t*)&yes0, sizeof(yes0));
//yes1 = eeprom.readOneByte(br);
  menu.setTextXY(1,1);
//  menu.printPair("",yes1,">");
  menu.printPair("",yes0[0],":");
  menu.printPair("",yes0[1],":");
  menu.printPair("",yes0[2],":");
  menu.printPair("",yes0[3],":");
  menu.printPair("",yes0[4],":");  
  
}

// load settings
void load_settings()
{
 menu.clrWinItems();
 menu.clrWin();
// uint8_t yes1[5]= {0,0,0,0,0};

// eeprom.read(10, (uint8_t*)&yes1, sizeof(yes1));
 menu.setText(LEFT, COLOR_WHITE); 
 button.addButton( 30, 170, 230, 40, 0, 10, 10, 1,"ADDR SPACE", BUTTON_ROUND, set_print);
 menu.drawWin(); 
  
}