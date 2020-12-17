

#include "../../../inc/MarlinConfigPre.h"
//#include "../../module/temperature.h"
//#include "../../../module/configuration_store.h"
#include "../../../module/planner.h"
#include "../../../gcode/queue.h"
#include "../UTFT_Menu.h"


void point_level()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  queue.inject_P(PSTR("G28 X Y"));
  queue.inject_P(PSTR("G29"));
 
 }

void linear_level()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  queue.inject_P(PSTR("G28"));
  queue.inject_P(PSTR("G29 S0"));
 
 }
void manual_level()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  queue.inject_P(PSTR("G28"));
  queue.inject_P(PSTR("G29 P2 B T "));
 
 }
void bilinear_level()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  queue.inject_P(PSTR("G28"));
  queue.inject_P(PSTR("G29 J"));
 
 }
void unified_level()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  queue.inject_P(PSTR("G28"));
  queue.inject_P(PSTR("G29 P1"));
 
 }
