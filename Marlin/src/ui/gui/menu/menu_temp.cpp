#include "../UTFT_Menu.h"
#include "../../../module/temperature.h"
#include "../../../gcode/queue.h"

extern uint16_t yes[];

// heat bed, nozzle
void heat_nozzle()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("",nozz);
 // thermalManager.setTargetHotend(temp, target_extruder);
 // degHotend(ee), degTargetHotend(ee)
 //  degBed(), degTargetBed()
//degChamber(), degTargetChamber()
  menu.drawSlotVal (0, nozz, COLOR_RED, 1);  
 
}

void heat_bed()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("",nozz);
  menu.drawSlotVal (1, nozz, COLOR_RED, 1);  
 
}

void stop_nozzle()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("",nozz);
  menu.drawSlotVal (0, nozz, COLOR_RED, 1);  
 
}

void stop_bed()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("",nozz);
  menu.drawSlotVal (1, nozz, COLOR_RED, 1);  
 
}
// set bed, nozzle target temp

void set_n1target()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("N1=",nozz);
  menu.drawSlotVal (0, nozz, COLOR_RED, 1);  
 
}

void set_n2target()
{ 
  int nozz= menu.getSliderValue();
  menu.PathPrint("N2=",nozz);
  menu.drawSlotVal (1, nozz, COLOR_RED, 1);  
 
}

void set_bedtarget()
{ 
  int bed= menu.getSliderValue();
  menu.PathPrint("B=",bed);
  menu.drawSlotVal (2, bed, COLOR_RED, 1);  
 
}

// set fan speed

void set_f0()
{ 
  int speed= menu.getSliderValue();
  thermalManager.fan_speed[0] = speed;
  menu.PathPrint("F0=",speed);
  menu.drawSlotVal (3, speed, COLOR_BLUE1, 0); 
//  thermalManager.set_fan_speed(0, speed);
//  queue.inject_P(PSTR("M106 P1 S255"));
 
}

void set_f1()
{ 
  int speed= menu.getSliderValue();
  thermalManager.fan_speed[1] = speed;
  menu.PathPrint("F1=",speed);
  menu.drawSlotVal (3, speed, COLOR_ORANGE, 1); 
//  thermalManager.set_fan_speed(1, speed);
//  queue.inject_P(PSTR("M106 P0 S255"));
 
}

void mute_f0()
{ 
  menu.drawSlotVal (3, 0, COLOR_BLUE1, 0); 
  queue.inject_P(PSTR("M107 P0"));
 // thermalManager.set_fan_speed(1, fan);
 
}

void mute_f1()
{ 
  menu.drawSlotVal (3, 0, COLOR_ORANGE, 1); 
  queue.inject_P(PSTR("M107 P1"));
 // thermalManager.set_fan_speed(1, fan);
 
}

void mute_f2()
{ 
 int fan= menu.getOnOffValue();
 if (fan)
    WRITE(CONTROLLER_FAN_PIN, LOW);
 else  WRITE(CONTROLLER_FAN_PIN, HIGH);
 
}

// ***********************
// ******  NOZZLE1  ******
// ***********************

void goNozzTemp1()
{ 
  
  menu.clrWinItems();
  button.addButton( 70, 90, 340, 40, 0, 300, 0, 1,"NOZZLE 1", BUTTON_ROUND, set_n1target);
  button.addButton( 50, 170, 150, 50, NULL,"HEAT", BUTTON_ROUND | HAS_BORDER, heat_nozzle);
  button.addButton( 280, 170, 150, 50, NULL,"STOP", BUTTON_ROUND | HAS_BORDER, stop_nozzle);
  menu.clrWin();
  menu.drawWin();
  
}

// ***********************
// ******  NOZZLE2  ******
// ***********************

void goNozzTemp2()
{ 
  
  menu.clrWinItems();
  button.addButton( 70, 90, 340, 40, 0, 300, 0, 1,"NOZZLE 2", BUTTON_ROUND, set_n2target);
  button.addButton( 50, 170, 150, 50, NULL,"HEAT", BUTTON_ROUND | HAS_BORDER, heat_nozzle);
  button.addButton( 280, 170, 150, 50, NULL,"STOP", BUTTON_ROUND | HAS_BORDER, stop_nozzle);
  menu.clrWin();
  menu.drawWin();
  
}

// ***********************
// ********  BED  ********
// ***********************

void goBedTemp()
{ 
  
  menu.clrWinItems();
  button.addButton( 70, 90, 340, 40, 0, 150, 0, 1,"BED", BUTTON_ROUND, set_bedtarget);
  button.addButton( 50, 170, 150, 50, NULL,"HEAT", BUTTON_ROUND | HAS_BORDER, heat_bed);
  button.addButton( 280, 170, 150, 50, NULL,"STOP", BUTTON_ROUND | HAS_BORDER, stop_bed);
  menu.clrWin();
  menu.drawWin();
}	

// ***********************
// *******  FANS  ********
// ***********************

void goFanTemp()
{ 
 
  menu.clrWinItems();
  button.addButton( 30, 90, 230, 40, 0, 255, thermalManager.fan_speed[0], 1,"COOL FAN", BUTTON_ROUND, set_f0);
  button.addButton( 30, 170, 230, 40, 0, 100, thermalManager.fan_speed[1], 1,"EXTRUDER FAN", BUTTON_ROUND, set_f1);
  button.addButton( 380, 94, 32, 32, yes, "MUTE", BUTTON_ROUND | HAS_BORDER | BUTTON_ONOFF, mute_f0);
  button.addButton( 380, 174, 32, 32, yes, "MUTE", BUTTON_ROUND | HAS_BORDER | BUTTON_ONOFF, mute_f1);
  menu.clrWin();
  menu.drawWin();
}

// ***********************
// ******  MB FAN  *******
// ***********************

void mb_fan()
{ 
 
  menu.clrWinItems();
  button.addButton( 380, 174, 32, 32, yes, "MUTE", BUTTON_ROUND | HAS_BORDER | BUTTON_ONOFF, mute_f2);
  menu.clrWin();
  menu.drawWin();
}	