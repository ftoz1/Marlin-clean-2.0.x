

#include "../../../inc/MarlinConfigPre.h"
//#include "../../language/language_en.h"
//#include "../../menu/menu.h"
#include "../../../module/printcounter.h"
#include "../UTFT_Menu.h"
#include "../../sd/cardreader.h"

void sd_func()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  menu.setText(LEFT, COLOR_WHITE);
  menu.setTextXY(5);   
//  menu.printPairLn("Inserted",sd_status,":",1);           //free memory
  menu.setText(CENTER);
                             
  
 }
