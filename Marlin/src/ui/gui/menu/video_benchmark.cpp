
#include "../../UTFT.h"

extern uint16_t marlin_logo100[];
extern uint16_t UTFT_logo[];
extern uint8_t Retro8x16[];

void clrBenchWin()
{ 
  tft.setColor(0);
  tft.fillRect(1,19,478,301);
}

void benchmark()   // benchark for lcd-mcu speed
{
  int buf[478];
  int x, x2;
  int y, y2;
  int r;

// Clear the screen and draw the frame
  tft.setFont(Retro8x16);
  tft.clrScr();
  tft.setColor(255, 0, 0);
  tft.fillRect(0, 0, 479, 18);
  tft.setColor(64, 64, 64);
  tft.fillRect(0, 301, 479, 319);
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("UTFT Benchmark", CENTER, 1);
  tft.setBackColor(64, 64, 64);
  tft.setColor(255,255,0);
  tft.print("<http://www.RinkyDinkElectronics.com/>", CENTER, 302);

  tft.setColor(0, 0, 255);
  tft.drawRect(0, 19, 479, 300);
//  millisStart();

// Draw crosshairs
  tft.setColor(0, 0, 255);
  tft.setBackColor(0, 0, 0);
  tft.drawLine(239, 19, 239, 301);
  tft.drawLine(1, 159, 478, 159);
  for (int i=9; i<470; i+=10)
    tft.drawLine(i, 157, i, 161);
  for (int i=19; i<220; i+=10)
    tft.drawLine(237, i, 241, i);

// Draw sin-, cos- and tan-lines  
  tft.setColor(0,255,255);
  tft.print("Sin", 5, 20);
  for (int i=1; i<478; i++)
  {
    tft.drawPixel(i,159+(sin(((i*1.13)*3.14)/180)*95));
  }
  
  tft.setColor(255,0,0);
  tft.print("Cos", 5, 32);
  for (int i=1; i<478; i++)
  {
    tft.drawPixel(i,159+(cos(((i*1.13)*3.14)/180)*95));
  }

  tft.setColor(255,255,0);
  tft.print("Tan", 5, 44);
  for (int i=1; i<478; i++)
  {
    tft.drawPixel(i,159+(tan(((i*1.13)*3.14)/180)));
  }

// Draw a moving sinewave

  clrBenchWin();

  tft.setColor(0, 0, 255);
  tft.setBackColor(0, 0, 0);
  tft.drawLine(239, 19, 239, 301);
  tft.drawLine(1, 159, 478, 159);


  x=1;
  for (int i=1; i<(478*15); i++) 
  {
    x++;
    if (x==479)
      x=1;
    if (i>479)
    {
      if ((x==239)||(buf[x-1]==159))
        tft.setColor(0,0,255);
      else
        tft.setColor(0,0,0);
      tft.drawPixel(x,buf[x-1]);
    }
    tft.setColor(0,255,255);
    y=159+(sin(((i*0.7)*3.14)/180)*(90-(i / 100)));
    tft.drawPixel(x,y);
    buf[x-1]=y;
  }

// Draw some filled rectangles

  clrBenchWin();

  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
    tft.fillRect(150+(i*20), 70+(i*20), 210+(i*20), 130+(i*20));
  }

// Draw some filled, rounded rectangles
  
  clrBenchWin();

  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
    tft.fillRoundRect(270-(i*20), 70+(i*20), 330-(i*20), 130+(i*20));
  }
  
// Draw some filled circles
  
  clrBenchWin();

  for (int i=1; i<6; i++)
  {
    switch (i)
    {
      case 1:
        tft.setColor(255,0,255);
        break;
      case 2:
        tft.setColor(255,0,0);
        break;
      case 3:
        tft.setColor(0,255,0);
        break;
      case 4:
        tft.setColor(0,0,255);
        break;
      case 5:
        tft.setColor(255,255,0);
        break;
    }
    tft.fillCircle(180+(i*20),100+(i*20), 30);
  }
  
// Draw some lines in a pattern
  
  clrBenchWin();

  tft.setColor (255,0,0);
  for (int i=19; i<301; i+=5)
  {
    tft.drawLine(1, i, (i*1.6)-10, 301);
  }
  tft.setColor (255,0,0);
  for (int i=301; i>19; i-=5)
  {
    tft.drawLine(478, i, (i*1.6)-11, 19);
  }
  tft.setColor (0,255,255);
  for (int i=301; i>19; i-=5)
  {
    tft.drawLine(1, i, 491-(i*1.6), 19);
  }
  tft.setColor (0,255,255);
  for (int i=19; i<301; i+=5)
  {
    tft.drawLine(478, i, 490-(i*1.6), 301);
  }
  
// Draw some random circles
  
  clrBenchWin();

  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=32+random(416);
    y=45+random(226);
    r=random(30);
    tft.drawCircle(x, y, r);
  }

// Draw some random rectangles
  
  clrBenchWin();

  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=19+random(282);
    x2=2+random(476);
    y2=19+random(282);
    tft.drawRect(x, y, x2, y2);
  }

 // Draw some random rounded rectangles
  
  clrBenchWin();

  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=19+random(282);
    x2=2+random(476);
    y2=19+random(282);
    tft.drawRoundRect(x, y, x2, y2);
  }

 // Draw random lines
  
  clrBenchWin();

  for (int i=0; i<100; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    x=2+random(476);
    y=19+random(282);
    x2=2+random(476);
    y2=19+random(282);
    tft.drawLine(x, y, x2, y2);
  }

 // Draw random pixels
  
  clrBenchWin();

  for (int i=0; i<10000; i++)
  {
    tft.setColor(random(255), random(255), random(255));
    tft.drawPixel(2+random(476), 20+random(280));
  }

 // Marlin logo move 

  clrBenchWin();

  for (int i=0; i<200; i++)
  {
  tft.drawBitmap(10+i,110,100,100,marlin_logo100);
  }
  tft.drawBitmapToDark(209,110,100,100,marlin_logo100,32);

 // Marlin logo scale 2 move and disappear

  clrBenchWin();

  for (int i=0; i<100; i++)
  {
  tft.drawBitmap(10 + i,160 -100,100,100,marlin_logo100,2);
  
  }
  tft.drawBitmapToDark(109,160 -100,100,100,marlin_logo100,32,2);


// Bitmap rotation

  clrBenchWin();

  for (int i=0; i<360; i++)
  {
  tft.drawBitmap(240,150,40,50,UTFT_logo,i,20,25);
  
  }

//  Runtime

  tft.fillScr(0, 0, 255);
  tft.setColor(255, 0, 0);
  tft.fillRoundRect(160, 120, 319, 190);
  tft.setColor(255, 255, 255);
  tft.setBackColor(255, 0, 0);
  tft.print("Runtime: (ms)", CENTER, 140);
  tft.printNumI(millis(), CENTER, 160);  
}