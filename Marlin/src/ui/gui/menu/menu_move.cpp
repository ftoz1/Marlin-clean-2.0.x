

#include "../../../inc/MarlinConfigPre.h"
//#include "../../../module/configuration_store.h"
#include "../../../module/planner.h"
#include "../../../gcode/queue.h"
#include "../UTFT_Menu.h"

extern uint16_t move1[];
extern uint16_t move2[];
extern uint16_t move_center[];
extern uint16_t move_corner[];
extern uint16_t yes[];

// move functions

void move_diagonal1()
{
  menu.PathPrint("X-Y+",10);
  queue.inject_P(PSTR("G1 X-10 Y10"));
}

void move_diagonal2()
{
  menu.PathPrint("X+Y+",10);
  queue.inject_P(PSTR("G1 X10 Y10"));
}

void move_diagonal3()
{
  menu.PathPrint("X-Y-",10);
  queue.inject_P(PSTR("G1 X-10 Y-10"));
}

void move_diagonal4()
{
  menu.PathPrint("X+Y-",10);
  queue.inject_P(PSTR("G1 X10 Y-10"));
}

void move_Xplus()
{
  menu.PathPrint("X+",20);
  queue.inject_P(PSTR("G0 X20"));
}

void move_Xminus()
{
  menu.PathPrint("X-",20);
  queue.inject_P(PSTR("G0 X-20"));
}
void move_Yplus()
{
  menu.PathPrint("Y+",20);
  queue.inject_P(PSTR("G0 Y20"));
}
void move_Yminus()
{
  menu.PathPrint("Y-",20);
  queue.inject_P(PSTR("G0 Y-20"));
}
void move_Zplus()
{
  menu.PathPrint("Z+",10);
  queue.inject_P(PSTR("G0 Z10"));
}
void move_Zminus()
{
  menu.PathPrint("Z-",10); 
  queue.inject_P(PSTR("G0 Z-10"));
}

void move_center1()
{
  menu.PathPrint("HomeXY",0);
  queue.inject_P(PSTR("G28 X Y"));
}

void move_center2()
{
  menu.PathPrint("HomeZ",0);
//  queue.inject_P(PSTR("G28 Z"));

}

//
// move/velocity/xyze
//

void velocityX()
{ 
  int vel= menu.getSliderValue();
  menu.PathPrint("VX=",vel);
  planner.settings.max_acceleration_mm_per_s2[X_AXIS] = vel;

}
void velocityY()
{ 
  int vel= menu.getSliderValue();
  menu.PathPrint("VY=",vel);
  planner.settings.max_acceleration_mm_per_s2[Y_AXIS] = vel;
}

void velocityZ()
{ 
  int vel= menu.getSliderValue();
  menu.PathPrint("VZ=",vel);
  planner.settings.max_acceleration_mm_per_s2[Z_AXIS] = vel;
}

void velocityE()
{ 
  int vel= menu.getSliderValue();
  menu.PathPrint("VE=",vel);
  planner.settings.max_acceleration_mm_per_s2[E_AXIS] = vel;
}

//
// move/accelerate/xyze
//

void accelP()
{ 
  int acc= menu.getSliderValue();
  menu.PathPrint("A=",acc);
  planner.settings.acceleration = acc;
}
void accelR()
{ 
  int acc= menu.getSliderValue();
  menu.PathPrint("AR=",acc);
  planner.settings.retract_acceleration = acc;
}

void accelT()
{ 
  int acc= menu.getSliderValue();
  menu.PathPrint("AT=",acc);
  planner.settings.travel_acceleration = acc;
}

//
// move/jerk/xyze
//

void jerkXY()
{ 
  int je= menu.getSliderValue();
  menu.PathPrint("JXY=",je);
//  planner.max_jerk.x = planner.max_jerk.y = je;
}
void jerkZ()
{ 
  int je= menu.getSliderValue();
  menu.PathPrint("JZ=",je);
//  planner.max_jerk.z = je;
}

void jerkE()
{ 
  int je= menu.getSliderValue();
  menu.PathPrint("JE=",je);
 // planner.max_jerk.e = je;
}
//
// move/step/xyze
//

void stepXY()
{ 
  int st= menu.getSliderValue();
  menu.PathPrint("SXY=",st);
  planner.settings.max_feedrate_mm_s[X_AXIS] = planner.settings.max_feedrate_mm_s[Y_AXIS] = st;
}

void stepZ()
{ 
  int st= menu.getSliderValue();
  menu.PathPrint("SZ=",st);
  planner.settings.max_feedrate_mm_s[Z_AXIS] = st;
}

void stepE()
{ 
  int st= menu.getSliderValue();
  menu.PathPrint("SE=",st);
  planner.settings.max_feedrate_mm_s[E_AXIS] = st;
}

//
// Test move menu 
//

void move_test()
{ 
  menu.clrWin();
  menu.clrWinItems();
  queue.inject_P(PSTR("G91")); // set all moves to relative position
  button.addButton( 40, 62, 50, 50, move_corner, NULL, BITMAP_ROT90, move_diagonal1);
  button.addButton( 98, 62, 50, 34, move1, NULL, BITMAP_ROT90, move_Yplus);
  button.addButton( 156, 62, 50, 50, move_corner, NULL, BITMAP_ROT180, move_diagonal2);
  button.addButton( 40, 120, 34, 50, move1, NULL ,0, move_Xminus);
  button.addButton( 98, 120, 50, 50, move_center,NULL,0, move_center1);
  button.addButton( 172, 120, 34, 50, move1, NULL, BITMAP_ROT180, move_Xplus);
  button.addButton( 40, 178, 50, 50, move_corner,NULL,0, move_diagonal3);
  button.addButton( 98, 194, 50, 34, move1, NULL, (BITMAP_ROT90 | BITMAP_ROT180), move_Yminus);
  button.addButton( 156, 178, 50, 50, move_corner, NULL,(BITMAP_ROT90 | BITMAP_ROT180), move_diagonal4);
  button.addButton( 380, 62, 50, 44, move2, NULL ,0 , move_Zminus);
  button.addButton( 380, 120, 50, 50, move_center, NULL,0, move_center2);
  button.addButton( 380, 184, 50, 44, move2,NULL, BITMAP_ROT180, move_Zplus);
  
  menu.drawWin();

 }

//
// Menu move/velocity
//
void  move_velocity() {
  
  menu.clrWinItems();
// settings.max_acceleration_mm_per_s2[axis] = targetValue;
  button.addButton( 20, 90, 200, 40, 50, 2000, 50, 10,"VELOCIY-X", BUTTON_ROUND, velocityX);
  button.addButton( 20, 170, 200, 40, 50, 2000, 50, 10,"VELOCIY-Y", BUTTON_ROUND, velocityY);
  button.addButton( 260, 90, 200, 40, 50, 500, 50, 5,"VELOCIY-Z", BUTTON_ROUND, velocityZ);
  button.addButton( 260, 170, 200, 40, 1000, 10000, 1000, 200,"VELOCIY-E", BUTTON_ROUND, velocityE);
  menu.clrWin();
  menu.drawWin();

}

void  move_accel() {
  menu.clrWinItems();
  button.addButton( 20, 90, 200, 40, 50, 2000, 50, 10,"A-PRINT", BUTTON_ROUND, accelP);
  button.addButton( 20, 170, 200, 40, 50, 2000, 50, 10,"A-RETRACT", BUTTON_ROUND, accelR);
  button.addButton( 260, 90, 200, 40, 50, 500, 50, 5,"A-TRAVEL", BUTTON_ROUND, accelT);
//  button.addButton( 260, 170, 200, 40, 1000, 10000, 0, 200,"ACCELERATE-E", BUTTON_ROUND, accelE);
  menu.clrWin();
  menu.drawWin();

}

void  move_jerk() {
  menu.clrWinItems();
  button.addButton( 20, 90, 200, 40, 50, 2000, 50, 10,"JERK-XY", BUTTON_ROUND, jerkXY);
  button.addButton( 20, 170, 200, 40, 50, 2000, 50, 10,"JERK-Z", BUTTON_ROUND, jerkZ);
  button.addButton( 260, 90, 200, 40, 50, 500, 50, 5,"JERK-E", BUTTON_ROUND, jerkE);
  menu.clrWin();
  menu.drawWin();

}

void  move_step() {
  menu.clrWinItems();
  button.addButton( 20, 90, 200, 40, 50, 2000, 50, 10,"S-XY/mm", BUTTON_ROUND, stepXY);
  button.addButton( 20, 170, 200, 40, 50, 2000, 50, 10,"S-Z/mm", BUTTON_ROUND, stepZ);
  button.addButton( 260, 90, 200, 40, 50, 500, 50, 5,"S-E/mm", BUTTON_ROUND, stepE);
  menu.clrWin();
  menu.drawWin();

}

