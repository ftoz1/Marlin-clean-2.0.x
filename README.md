# Marlin 3D Printer Firmware
 This is fork of marlin 2.0.7.2.
 It has no UI and work only with pronterface. 
 Idea is get back clean Marlin FW core as layerable software without any useless files to get more comfortable for develop.
 Marlin only as core with base lib drivers + serial + gcodes. UI as separate layer for custom builds. 
 
 Focus on: clean any UI isseus,
           clean any u8glib issues,
		   clean monochrome LCD isseus,
		   clean unnecesary Gcodes,
           clean crazy macros,
		   hold structures of base files
		   
		                                         Welcome to clean !!!   
												   
Done: cleaned all /lcd	directory and its issues
      cleaned LCD languages.
      cleaned configuration.h (some issues was moved to configuration_adv.h)	  