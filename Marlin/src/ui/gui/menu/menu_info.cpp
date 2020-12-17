

#include "../../../inc/MarlinConfigPre.h"
#include "../../../module/printcounter.h"
#include "../UTFT_Menu.h"

void marlin_info()
{ 
  menu.clrWin();
  menu.drawWinFrame();
  menu.setText(CENTER, COLOR_WHITE);
  menu.printLn(STR_MARLIN);                                 // Marlin
  menu.printLn(SHORT_BUILD_VERSION);                        // x.x.x-Branch
  menu.printLn(STRING_DISTRIBUTION_DATE);                    // YYYY-MM-DD HH:MM
  menu.setText(LEFT);
  menu.setTextXY(5);   
  menu.printPairLn(STR_FREE_MEMORY,freeMemory(),":");           //free memory
  menu.setTextXY(4); 
  menu.printPairLn("Planner Buffer", 84 * BLOCK_BUFFER_SIZE, ":");
  menu.setText(CENTER);
  menu.printLn(STRING_CONFIG_H_AUTHOR);                      // Changes by
  menu.printLn(WEBSITE_URL);                                // www.my3dprinter.com
 

//  menu.printLn(SOURCE_CODE_URL);                                
  
 }

void board_info()
{
  menu.clrWin();
  menu.drawWinFrame();
  menu.setText(CENTER, COLOR_WHITE);
  menu.printLn(BOARD_INFO_NAME);               // MyPrinterController
  menu.printLn("CXY-V5-180409 chitu F mini");
  menu.printLn("Steppers: A4982");                         // Steppers
  menu.printLn("MCU: STM32F103ZET6  72MHz");                              // MCU
  menu.printLn("Mem: 64kB RAM 512kB Flash");                              // MCU
  menu.printLn("SPI Flash: Winbond W25Q16");                         // SPI Flash
  menu.printLn("EEprom: 24C16  16KB");                         // EEprom
                
}
 
void printer_info()
{
  menu.clrWin();
  menu.drawWinFrame();
  menu.setText(CENTER, COLOR_WHITE);
  menu.printLn(MACHINE_NAME);                                  // My3DPrinter 
  menu.printLn("CoreXY 24V");
  menu.setText(LEFT);
  menu.setTextXY(5);                                           // if y not specify stay same
  menu.printPair("X",X_BED_SIZE,":");                         // Dimension 
  menu.printPair(" Y",Y_BED_SIZE,":"); 
  menu.printPairLn(" Z",Z_MAX_POS,":"); 
//  menu.setText(CENTER);
  uint16_t lcdid= 0; // LCD_IO_ReadData(0x04,3);   fsmc.GetID()
  menu.setTextXY(7);
  menu.print("LCD ID: 0x");
  menu.printNum((lcdid & 0xF000)>>12);
  menu.printNum((lcdid & 0x0F00)>>8);
  menu.printNum((lcdid & 0x00F0)>>4);
  menu.printNum(lcdid & 0x000F);
  menu.ln();
  menu.setText(CENTER);
  if ((lcdid & 0xFFFF) == 0x8066)  
		menu.printLn("Raydium RM68140 320x480");                                      // x5sa lcd-- Raydium RM68140 LCD controller
  menu.printLn("Heaters: ");   
  menu.printLn("Power supply: S-360-24"); 
}

void printer_stat_info()
{
  menu.clrWin();
  menu.drawWinFrame();
  menu.setText(CENTER, COLOR_WHITE); 
//  tft.print(MSG_INFO_PRINT_COUNT, CENTER, 45);            // Print Count: 999
//  tft.printNumI(stats.totalPrints ,300, 45, 7);
//  tft.print(MSG_INFO_COMPLETED_PRINTS,CENTER, 70);               // Completed  : 666
//  tft.printNumI(stats.finishedPrints ,300, 70, 7);
 // tft.print(MSG_INFO_PRINT_TIME, CENTER, 95);          // YYYY-MM-DD HH:MM
//    duration_t(stats.printTime).toString(buffer)
//  tft.print(MSG_INFO_PRINT_LONGEST, CENTER, 120);                // Longest job time:
// duration_t(stats.longestPrint).toString(buffer)
//  tft.print(MSG_INFO_PRINT_FILAMENT, CENTER, 145);                      
// sprintf_P(buffer, PSTR("%ld.%im"), long(stats.filamentUsed / 1000), int16_t(stats.filamentUsed / 100) % 10);
//  tft.print(MSG_INFO_EXTRUDERS,CENTER, 145);                // Service X in:
 // tft.printNumI(EXTRUDERS,300, 145, 1);   duration_t(stats.nextService1).toString(buffer)
}
