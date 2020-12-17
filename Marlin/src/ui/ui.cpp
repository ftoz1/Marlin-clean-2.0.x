// this file is equival with ultralcd.cpp
// It init all UTFT classes


#include "../inc/MarlinConfig.h"
#include "gui/menuItems.h"
#include "../sd/cardreader.h"
#include "../module/temperature.h"
#include "../HAL/STM32F1/tft/tft_fsmc.h"
//#include "../module/thermistor/thermistors.h"

 
#if HAS_BUZZER
  #include "../libs/buzzer.h"
#endif

#ifdef HAS_FSMC_TFT
 TFT_FSMC fsmc;
#endif
UTFT tft(&fsmc, MODEL, FSMC_RS_PIN, FSMC_WR_PIN, FSMC_CS_PIN, TFT_RESET_PIN);  //bus type,lcd type, RS, WR, CS, RST  
URTouch  touch(TOUCH_SCK_PIN, TOUCH_CS_PIN, TOUCH_MOSI_PIN, TOUCH_MISO_PIN, TOUCH_INT_PIN); // touchscreen driver
UTFT_Buttons  button(&tft, &touch);  //touch button lib
UTFT_Menu     menu(&button, size_menu, drive_menu, slot_menu, marlin_menu,2,3,TILT % 2); //main menu tree, all marlin menu, menu size x, menu size y(can be changed to 3x2 or 1x6),screen orientation

void ui_init() {

  OUT_WRITE(TFT_BACKLIGHT_PIN, LOW);
  
  tft.InitLCD(TILT); 
  tft.clrScr();
     
  WRITE(TFT_BACKLIGHT_PIN, HIGH);
  
#ifdef SHOW_BOOTSCREEN
  tft.drawBitmap(XRES/2 -50*(BOOTSCREEN_SCALE),YRES/2 -50*(BOOTSCREEN_SCALE),100,100,marlin_logo100,BOOTSCREEN_SCALE);
  delay(BOOTSCREEN_DELAY);
#endif

  touch.InitTouch(LCD_ORIENTATION);
  touch.setPrecision(PREC_EXTREME);
  button.setTextFont(Arial_round_16x24);
  menu.setFont(Arial_round_16x24,Retro8x16); 

#ifdef BOOTSCREEN_DISAPPER
  tft.drawBitmapToDark(XRES/2 -50*(BOOTSCREEN_SCALE),YRES/2 -50*(BOOTSCREEN_SCALE),100,100,marlin_logo100,32/BOOTSCREEN_SCALE, BOOTSCREEN_SCALE);
#endif

#ifdef TOUCH_CALIBRATION
  TsCalibration();
#endif

  menu.drawPage();
}

void sd_update1() {
 #if ENABLED(SDSUPPORT) && PIN_EXISTS(SD_DETECT)

    const uint8_t sd_status = (uint8_t)IS_SD_INSERTED();     //test sd_insert_pin
  //  if (sd_status != lcd_sd_status && detected()) {

    //  uint8_t old_sd_status = lcd_sd_status; // prevent re-entry to this block!
    //  lcd_sd_status = sd_status;
     menu.PathPrint("SD-",sd_status);
      if (sd_status) 
	  {
    //    safe_delay(500); // Some boards need a delay to get settled
        card.mount();
   //     if (old_sd_status == 2)
          card.beginautostart();  // Initial boot
   //     else
   //       menu.PathPrint("SD-",1);
      }
      else 
	  {
        card.release();
   //     if (old_sd_status != 2) set_status_P(PSTR(MSG_SD_REMOVED));
    //      menu.PathPrint("SD-",0);
      }

    //  refresh();
    //  init_lcd(); // May revive the LCD if static electricity killed it
//    }

  #endif // SDSUPPORT && SD_DETECT_PIN
}

void temp_update()
{
  menu.drawSlotVal (0, thermalManager.degHotend(0), COLOR_GREEN, 0); 
//  menu.drawSlotVal (1, temp_hotend[HOTEND_INDEX].celsius, COLOR_GREEN, 0); 
  menu.drawSlotVal (2, thermalManager.degBed() , COLOR_GREEN, 0); 
}
void ui_update() 
{
     p_func pf = menu.checkPage();
    if (pf != NULL)
		{ 
		   
		  if (menu.press_slider == false)
		  {
		 //    buzzer.tone(1, 200);
            // buzzer.tick(); 
		  }		  
		 pf();
        }
   //  sd_update1();
     temp_update();
}  