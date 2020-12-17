// This is  structucture with main marlin menu tree. Menu has 2 window, one is defined as fullscreen and second for menu buttons and text messages. 
//Drive buttons are used to list menu and call home. Short buttons use as short icon to one of menu items. Short buttons ara place in one of 8 slot.
//Each slot has icon and 2 text info. Main menu structure is set default for 6 items per window . Each item has flag, first 4 bits are deep in tree.So max deep is 16.
//Second 4 bits are item flag. First item in each page has flag ITEM_FIRST. Item as submenu with no function has flag ITEM_SUBMENU. Last issue is name of function to call, when button is pressed.

 
#include "UTFT_Menu.h"

extern uint8_t Arial_round_16x24[];
extern uint8_t Retro8x16[];
extern uint16_t marlin_logo100[];
extern uint16_t butt1[];
extern uint16_t butt2[];
extern uint16_t butt3[];
extern uint16_t nozzle_30x40[];
extern uint16_t bed[];
extern uint16_t fan[];
extern uint16_t chip[];
extern uint16_t yes[];

extern void benchmark();
extern void marlin_info();
extern void board_info();
extern void printer_info();
extern void printer_stat_info();
extern void move_test();
extern void goNozzTemp1();
extern void goNozzTemp2();
extern void goBedTemp();
extern void goFanTemp();
extern void mb_fan();
extern void sd_func();
extern void move_velocity();
extern void move_accel();
extern void move_jerk();
extern void move_step();
extern void touch_set();
extern void TsCalibration();
extern void lcd_bright();
extern void lcd_tilt();
extern void set_color_txt();
extern void set_color_bgr();
extern void set_color_bline();
extern void set_menu_xy();
extern void save_settings();
extern void load_settings();
extern void point_level();
extern void linear_level();
extern void manual_level();
extern void bilinear_level();
extern void unified_level();
extern void mb_fan();

/*void customgraphic()
{ 
  tft.setColor(COLOR_VIOLET);
  tft.drawRoundRect(10,222,470,242);
}*/

void drawOff()
{ 
  tft.setColor(COLOR_RED);
  tft.print("OFF",400,33,0);
}

/*void goInfo()
{ 
	 char str[] ="This a sample string";
			char *pch;
            pch = strtok(str," ");
            int numspc = 0;
            while (pch != NULL)
              {
               tft.print(pch, 10, 20 * numspc + 30);
               numspc++;
               pch = strtok(NULL," ");
              }	
}*/


//
//  Drive button functions
//
void goback()
{ 
  menu.goBack();
}

void gohome()
{ 
  menu.goHome();
}

void gonext()
{ 
  menu.goNext();
}

//
// Main menu tree structure
//
static size_type  size_menu[] ={
	// outer and inner window size- upper cord, bottom cord
    { 0, 0, XRES, YRES},
    { 10, 60, XRES-20, 233}
};

static drive_type  drive_menu[] ={
	// drive buttons - posx, posy, sizex, sizey, bitmapdata, function
	{50, 265, 60,  50, butt1, goback},
    {(XRES)/3 + 50, 265, 60,  50, butt2, gohome},
    {2*(XRES)/3 + 50, 265, 60,  50, butt3, goback},
   // {7*XRES/8-40, 250, 80,  60, button4,NULL,0, goback},
    {0,0,0,0,NULL,NULL}  // end sigh 
};

static slot_type  slot_menu[] ={  // slot buttons up to 8 slot here, each slot has button and 2x numeral value, its 4 slots per row.
//  {num1_value, num2_value, num1_color, num2_color, bitmap_xsize, bitmap_ysize, bitmap, bitmap inner label, bitmap flags, jump function}
    {0,275,COLOR_GREEN,COLOR_RED,30,40,nozzle_30x40,"1",LABEL_INUP | LABEL_DARK ,goNozzTemp1},
	{0,275,COLOR_GREEN,COLOR_RED,30,40,chip,"M",LABEL_DARK ,goNozzTemp2},
	{0,275,COLOR_GREEN,COLOR_RED,30,40,bed,NULL,0,goBedTemp},
	{80,90,COLOR_BLUE1,COLOR_ORANGE,40,40,fan,NULL,0,goFanTemp},
	{0,0,0,0,0,0,0,NULL,0,NULL}  // end sigh
};

// Main menu tree with 6 items per menu.
static item_type  marlin_menu[] ={
  
  //main page  functoin draw addon graphics :{ name, deep | item_flag, jump function}
    {"MAIN",0, drawOff},
  // page 1
	{"TEMP",1 | ITEM_FIRST | ITEM_SUBMENU, gonext},
    {"LEVEL",1 | ITEM_SUBMENU, gonext},
	{"MOVE",1 | ITEM_SUBMENU, gonext},
	{"FILAMENT",1 | ITEM_SUBMENU, gonext},
	{"SD",1, sd_func},
    {"OTHERS",1 | ITEM_SUBMENU, gonext},

 //  page 1.1
	{"NOZZLE",2 | ITEM_FIRST | ITEM_SUBMENU, gonext},
	{"BED",2 , goBedTemp},
	{"CHAMBER",2 , goBedTemp},
    {"FAN",2  | ITEM_SUBMENU, gonext},
	
//  page 1.2
	{"3 POINT",2 | ITEM_FIRST, point_level},
	{"LINEAR",2, linear_level},
	{"MANUAL",2 , manual_level},
    {"BILINEAR",2 , bilinear_level},
	{"UNIFIED",2 , unified_level},

//  page 1.3
	{"TEST",2 | ITEM_FIRST , move_test},
	{"VELOCITY",2 , move_velocity},
    {"ACCEL",2 , move_accel},
	{"JERK",2 , move_jerk},
	{"STEPS",2 , move_step},

//  page 1.4
	{"EXTRUDE",2 | ITEM_FIRST , drawOff},
	{"CHECK",2 , drawOff},

//  page 1.6
	
	{"LCD",2 | ITEM_FIRST | ITEM_SUBMENU, gonext},
	{"TOUCH",2 | ITEM_SUBMENU , gonext},
	{"MOTORS",2  , drawOff},
    {"MENU",2 | ITEM_SUBMENU, gonext},
    {"CONSOLE",2 , drawOff},
	{"INFO",2 | ITEM_SUBMENU, gonext},

//  page 1.1.1
	{"NOZZLE1",3 | ITEM_FIRST, goNozzTemp1},
	{"NOZZLE2",3 , goNozzTemp2},
  
//  page 1.1.4
	{"FANS",3 | ITEM_FIRST, goFanTemp},
	{"MB FAN",3 , mb_fan},

//  page 1.6.1
	{"BRIGHT",3 | ITEM_FIRST, lcd_bright},
    {"TILT",3, lcd_tilt},
	{"BENCH",3 , benchmark},    
   

//  page 1.6.2
	{"PRECIS",3 | ITEM_FIRST, touch_set},
    {"CALIB",3, TsCalibration},

//  page 1.6.4
	{"M-XY",3 | ITEM_FIRST, set_menu_xy},
    {"M-FLAG",3 , benchmark},
    {"B-TEXT",3 , set_color_txt},
	{"B-BACKG",3 , set_color_bgr},
    {"B-LINE",3 , set_color_bline},
    {"SETTING",3 | ITEM_SUBMENU, gonext},

//  page 1.6.6
	{"MARLIN",3 | ITEM_FIRST, marlin_info},
	{"BOARD",3 , board_info},
	{"PRINTER",3 , printer_info},
	{"STATS",3 , printer_stat_info}, 
		
//  page 1.6.4.6		 
    {"SAVE",4 | ITEM_FIRST, save_settings},
    {"LOAD",4 , load_settings},


    {"",0,NULL}                    // end sigh
};




