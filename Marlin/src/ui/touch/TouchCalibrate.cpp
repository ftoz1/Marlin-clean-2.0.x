
// These calibration test return CAL-X,CAL-Y,CAL-S values for your touchscreen

#include "../UTFT.h"
#include "URTouch.h"

#define TOUCH_ORIENTATION LCD_ORIENTATION
extern uint8_t Retro8x16[];

 
 int rx[8], ry[8];
// int text_y_center;


void waitForTouch()
{
  while (touch.dataAvailable() == true) {}
  while (touch.dataAvailable() == false) {}
//  while (touch.dataAvailable() == true) {}
}


void drawCrossHair(int x, int y)
{
  tft.drawRect(x-10, y-10, x+10, y+10);
  tft.drawLine(x-5, y, x+5, y);
  tft.drawLine(x, y-5, x, y+5);
}


void TsCalibrate(int x, int y, int i)
{
  tft.setColor(COLOR_WHITE);
  drawCrossHair(x,y);
  tft.setBackColor(COLOR_RED);
   
  // read coordinates
  int iter = 5000;
  int failcount = 0;
  int cnt = 0;
  uint32_t tx=0;
  uint32_t ty=0;
  boolean OK = false;
  
  while (OK == false)
  {
  //  tft.setColor(255, 255, 255);
    tft.print("*  PRESS  *", CENTER, tft.getDisplayYSize()/2 -6);
    while (touch.dataAvailable() == false) {}
    tft.print("*  HOLD!  *", CENTER, tft.getDisplayYSize()/2 -6);
    while ((touch.dataAvailable() == true) && (cnt<iter) && (failcount<10000))
    {
      touch.calibrateRead();
      if (!((touch.TP_X==65535) || (touch.TP_Y==65535)))
      {
        tx += touch.TP_X;
        ty += touch.TP_Y;
        cnt++;
      }
      else
        failcount++;
    }
    if (cnt>=iter)
    {
      OK = true;
    }
    else
    {
      tx = 0;
      ty = 0;
      cnt = 0;
    }
    if (failcount>=10000)
    { 
		 // ts calibration fail
         tft.clrScr();
         tft.setColor(COLOR_RED);
         tft.fillRect(0, 0, tft.getDisplayXSize() -1, 16);
         tft.setColor(COLOR_WHITE);
     //    tft.setBackColor(COLOR_RED);
         tft.drawLine(0, 17, tft.getDisplayXSize() -1, 17);
         tft.print("URTouch Calibration FAILED", CENTER, 1);
         tft.setBackColor(COLOR_BLACK);
         tft.print("Unable to read the position", CENTER, 30);
         tft.print("of the press. This is", CENTER, 46);
         tft.print("a hardware issue.", CENTER, 62);
	 
         waitForTouch();
         tft.clrScr();
	}
  }

  rx[i] = tx / iter;
  ry[i] = ty / iter;
  // end of reading

//  tft.setColor(COLOR_WHITE);
  tft.print("* RELEASE *", CENTER, tft.getDisplayYSize()/2 -6);
  tft.setColor(80, 80, 80);
  drawCrossHair(x,y);

  while (touch.dataAvailable() == true) {}
}


void HexPrint(uint32_t num, int pos)
{
  char buf[13];
  buf[0] = '0';
  buf[1] = 'x';
  buf[10] = 'U';
  buf[11] = 'L';
  buf[12] = 0;
  for (int zz=9; zz>1; zz--)
  {
    if ((num & 0xF) > 9)
      buf[zz] = (num & 0xF) + 55;
    else
      buf[zz] = (num & 0xF) + 48;
    num=num>>4;
  }
  tft.print(buf, CENTER, pos);
}

void TsCalibration()
{ 

  //calibration start

  
  int dispx=tft.getDisplayXSize();  // display native is portrait
  int dispy=tft.getDisplayYSize();
  int calx, caly, cals;
  int clx, crx, cty, cby;
  float px, py;
//  text_y_center=(dispy/2)-6;

  tft.setFont(Retro8x16);
  tft.clrScr();
  tft.setColor(COLOR_RED);
  tft.fillRect(0, 0, dispx-1, 16);
  tft.setColor(COLOR_WHITE);
  tft.setBackColor(COLOR_RED);
  tft.drawLine(0, 17, dispx-1, 17);
  tft.print("URTouch Calibration", CENTER, 1);
  tft.setBackColor(COLOR_BLACK);

 
    tft.print("INSTRUCTIONS", CENTER, 30);
    tft.print("Use a stylus to touch to the center", CENTER, 50);
    tft.print("of the highlighted crosshair. Keep", CENTER, 66);
    tft.print("holding until the highlight is removed.", CENTER, 82);
    tft.print("Repeat for all crosshairs in sequence.", CENTER, 98);
    tft.print("Touch screen to continue", CENTER, 226);
  

  waitForTouch();
  tft.clrScr();

 //main calibration
  
  tft.setColor(80, 80, 80);
  drawCrossHair(dispx-11, 10);
  drawCrossHair(dispx/2, 10);
  drawCrossHair(10, 10);
  drawCrossHair(dispx-11, dispy/2);
  drawCrossHair(10, dispy/2);
  drawCrossHair(dispx-11, dispy-11);
  drawCrossHair(dispx/2, dispy-11);
  drawCrossHair(10, dispy-11);
  tft.setColor(COLOR_WHITE);
  tft.setBackColor(COLOR_RED);
  tft.print("***********", CENTER, (dispy/2)-18);
  tft.print("***********", CENTER, (dispy/2)+6);

  TsCalibrate(10, 10, 0);
  TsCalibrate(10, dispy/2, 1);
  TsCalibrate(10, dispy-11, 2);
  TsCalibrate(dispx/2, 10, 3);
  TsCalibrate(dispx/2, dispy-11, 4);
  TsCalibrate(dispx-11, 10, 5);
  TsCalibrate(dispx-11, dispy/2, 6);
  TsCalibrate(dispx-11, dispy-11, 7);
  
  if (TOUCH_ORIENTATION == LANDSCAPE)
    cals=(long(dispx-1)<<12)+(dispy-1);
  else
    cals=(long(dispy-1)<<12)+(dispx-1);

  if (TOUCH_ORIENTATION == PORTRAIT)
    px = abs(((float(rx[2]+rx[4]+rx[7])/3)-(float(rx[0]+rx[3]+rx[5])/3))/(dispy-20));  // PORTRAIT
  else
    px = abs(((float(rx[5]+rx[6]+rx[7])/3)-(float(rx[0]+rx[1]+rx[2])/3))/(dispy-20));  // LANDSCAPE

  if (TOUCH_ORIENTATION == PORTRAIT)
  {
    clx = (((rx[0]+rx[3]+rx[5])/3));  // PORTRAIT
    crx = (((rx[2]+rx[4]+rx[7])/3));  // PORTRAIT
  }
  else
  {
    clx = (((rx[0]+rx[1]+rx[2])/3));  // LANDSCAPE
    crx = (((rx[5]+rx[6]+rx[7])/3));  // LANDSCAPE
  }
  if (clx<crx)
  {
    clx = clx - (px*10);
    crx = crx + (px*10);
  }
  else
  {
    clx = clx + (px*10);
    crx = crx - (px*10);
  }
  
  if (TOUCH_ORIENTATION == PORTRAIT)
    py = abs(((float(ry[5]+ry[6]+ry[7])/3)-(float(ry[0]+ry[1]+ry[2])/3))/(dispx-20));  // PORTRAIT
  else
    py = abs(((float(ry[0]+ry[3]+ry[5])/3)-(float(ry[2]+ry[4]+ry[7])/3))/(dispx-20));  // LANDSCAPE

  if (TOUCH_ORIENTATION == PORTRAIT)
  {
    cty = (((ry[5]+ry[6]+ry[7])/3));  // PORTRAIT
    cby = (((ry[0]+ry[1]+ry[2])/3));  // PORTRAIT
  }
  else
  {
    cty = (((ry[0]+ry[3]+ry[5])/3));  // LANDSCAPE
    cby = (((ry[2]+ry[4]+ry[7])/3));  // LANDSCAPE
  }
  if (cty<cby)
  {
    cty = cty - (py*10);
    cby = cby + (py*10);
  }
  else
  {
    cty = cty + (py*10);
    cby = cby - (py*10);
  }
  
  calx = (long(clx)<<14) + long(crx);
  caly = (long(cty)<<14) + long(cby);
  if (TOUCH_ORIENTATION == LANDSCAPE)
    cals = cals + (1L<<31);

// calibration done

  tft.clrScr();
  tft.setColor(COLOR_RED);
  tft.fillRect(0, 0, dispx-1, 16);
  tft.setColor(COLOR_WHITE);
  tft.setBackColor(COLOR_RED);
  tft.drawLine(0, 17, dispx-1, 17);
  tft.print("URTouch Calibration", CENTER, 1);
  tft.setBackColor(COLOR_BLACK);
  
    tft.print("CALIBRATION COMPLETE", CENTER, 30);
    tft.print("CAL_X:", 80, 150);
    tft.print("CAL_Y:", 80, 166);
    tft.print("CAL_S:", 80, 182);

    HexPrint(calx, 150);
    HexPrint(caly, 166);
    HexPrint(cals, 182);

    touch.setCAL(calx,caly,cals,TOUCH_ORIENTATION);
  
  waitForTouch();
  tft.clrScr();
}
