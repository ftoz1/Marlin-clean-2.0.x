
	LCD_Write_COM(0xC1); 
	LCD_Write_DATA(0xFF);
	LCD_Write_DATA(0x83);
	LCD_Write_DATA(0x40); 
	LCD_Write_COM(0x11); 
	delay(100);
	LCD_Write_COM(0xCA); 
	LCD_Write_DATA(0x70);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0xD9); 
	LCD_Write_DATA(0x01);
	LCD_Write_DATA(0x11); 

	LCD_Write_COM(0xC9); 
	LCD_Write_DATA(0x90);
	LCD_Write_DATA(0x49);
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x28);
	LCD_Write_DATA(0x28); 
	LCD_Write_DATA(0x10); 
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x06);
	delay(20);
	LCD_Write_COM(0xC2); 
	LCD_Write_DATA(0x60);
	LCD_Write_DATA(0x71);
	LCD_Write_DATA(0x01); 
	LCD_Write_DATA(0x0E);
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x02); 
	LCD_Write_DATA(0x09); 
	LCD_Write_DATA(0x31);
	LCD_Write_DATA(0x0A);
  
	LCD_Write_COM(0xc3); 
	LCD_Write_DATA(0x67);
	LCD_Write_DATA(0x30);
	LCD_Write_DATA(0x61); 
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x48); 
	LCD_Write_DATA(0x07); 
	LCD_Write_DATA(0x05); 
	LCD_Write_DATA(0x33); 
	delay(10);
	LCD_Write_COM(0xB5); 
	LCD_Write_DATA(0x35);
	LCD_Write_DATA(0x20);
	LCD_Write_DATA(0x45); 

	LCD_Write_COM(0xB4); 
	LCD_Write_DATA(0x33);
	LCD_Write_DATA(0x25);
	LCD_Write_DATA(0x4c); 
	delay(10);
	LCD_Write_COM(0x3a); 
	LCD_Write_DATA(0x05);
	LCD_Write_COM(0x29); 
	delay(10);
	LCD_Write_COM(0x2a); 
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0xaf); 
	LCD_Write_COM(0x2b); 
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0xdb); 
	LCD_Write_COM(0x2c); 
	
