

#include "UTFT_Buttons.h"

#define UTFT_MENU_VERSION	100


#define MAX_DEEP	8
#define BUT_SPACE	5
#define FONT1	    0
#define FONT2	    1


// Define Item flag status     //low 4 bits deep, hi 4 bits flag 
#define ITEM_FIRST			    0x10
#define ITEM_SUBMENU		    0x20
#define ITEM_DISABLE	        0x40
#define ITEM_UNUSED	            0x80
#define ITEM_DEEP	            0x0F

//drive function back, up, down, home, forw,( cancel, stop, start, accept)


typedef struct
{                
	             uint16_t          x,y,x1,y1;         
                				 
} size_type; 

typedef struct
{                
	             uint16_t          x,y, width,height;
                 bitmapdatatype    data;
                 p_func            function;
				 
} drive_type;

typedef struct
{                
	             uint16_t          val1,val2;
				 word              col1,col2;
	             uint16_t          width,height;
                 bitmapdatatype    data;
                 char				*label;
                 uint16_t          flag;
                 p_func            function;
				 
} slot_type;

typedef struct
{                
	             char				*label;
                 byte               flag;
                 p_func             function;
				 
} item_type;

class UTFT_Menu
{
	public:
		UTFT_Menu(UTFT_Buttons *ptrUTFT_Buttons, size_type *ptrsize, drive_type *ptrdrive, slot_type *ptrslot, item_type *ptrmenu, byte nbx, byte nby, boolean scr_orient);
	    void    addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, bitmapdatatype data, char *label, uint16_t flags, p_func func);
        void    addButton(uint16_t x, uint16_t y, uint16_t width, uint16_t height, float min, float max, float current, float step, char *label, uint16_t flags, p_func func);
	    void	drawPage();
        void	drawWin();
        void    drawWinFrame();
        void	drawPath();
        void    drawPathFrame();
        void	clrWin();
        p_func	checkPage();
        void	goBack();
        void	goNext();
        void	goHome();
		void    clrWinItems();
        void    addWinItems();
        boolean backWinItems();
        boolean nextWinItems();
		void	setPageType(uint8_t* font, word atxt, word iatxt, word brd, word brdhi, word back);
   		void	setFont(uint8_t* font1, uint8_t* font2);
        float   getSliderValue();
        boolean getOnOffValue();
        void    drawSlotVal(int slt, int val, word textcol, boolean type);
        void    setEnv(byte nbx , byte nby, byte spc , uint16_t flag);
        void    setText(word t_order, word color=COLOR_WHITE, boolean font=0);
        void    setTextXY(byte tx, byte ty=255);
		void    ln();
        void    print(char *st);
        void    printLn(char *st);
        void    printPair(char *st, int value, char *ch=NULL, byte length=0);
        void    printPairLn(char *st, int value, char *ch=NULL, byte length=0);
        void    printNum(int value, byte length=0);
        void    PathPrint(char *st, int value, byte length=0);
	//	void	setMenuColors(word atxt, word iatxt, word brd, word brdhi, word back); 
        boolean     in_menu, press_slider, scr_orient;
        byte        nb_x, nb_y, pos_space;
        word        buttons_flag, color_txt, color_bgr;
	protected:
		
		UTFT_Buttons *_UTFT_Buttons;
        size_type    *p_size;
        drive_type   *p_drive;
        slot_type    *p_slot;
        item_type    *p_item;
        long    	path[MAX_DEEP];		
		byte        deep, bdrive_cnt, bshort_cnt;
		int         press_idx;
        word        deep1_idx, curr1_idx, text_x, text_y, path_x, textorder;
		uint8_t		*_font1,*_font2;
};
extern  UTFT_Menu     menu;

