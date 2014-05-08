#include<conio.h>
#include <stdlib.h>
#include<windows.h>
//Goes to x,y coord. on screen.

void gotoxy(int x,int y)
{
 COORD coord;
 coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



//Puts a char at x,y coord. on screen.


void putchar(int x,int y,char ch)
{
 gotoxy(x, y);
 _putch(ch);
}

enum MISC_KEYS
{
 VK_OEM_PLUS   =  0xBB,
 VK_OEM_COMMA  =  0xBC,
 VK_OEM_MINUS  =  0xBD,
 VK_OEM_PERIOD =  0xBE
};

//Enumerate all colors.
enum COLOR
{
 BLACK      = 0,
 GREY       = FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED,
 WHITE      = FOREGROUND_INTENSITY+GREY,
 INTENS_BLUE       = FOREGROUND_INTENSITY+FOREGROUND_BLUE,
 INTENS_GREEN      = FOREGROUND_INTENSITY+FOREGROUND_GREEN,
 INTENS_RED        = FOREGROUND_INTENSITY+FOREGROUND_RED,
	   CYAN       = FOREGROUND_BLUE+FOREGROUND_GREEN,
 INTENS_CYAN       = FOREGROUND_INTENSITY+CYAN,
	   MAGENTA    = FOREGROUND_RED+FOREGROUND_BLUE,
 INTENS_MAGENTA    = FOREGROUND_INTENSITY+MAGENTA,
	   YELLOW     = FOREGROUND_RED+FOREGROUND_GREEN,
 INTENS_YELLOW     = FOREGROUND_INTENSITY+YELLOW,
	   BG_BLACK   = 0,
	   BG_GREY    = BACKGROUND_BLUE+BACKGROUND_GREEN+BACKGROUND_RED,
	   BG_WHITE   = BACKGROUND_INTENSITY+BG_GREY,
 BG_INTENS_BLUE    = BACKGROUND_INTENSITY+BACKGROUND_BLUE,
 BG_INTENS_GREEN   = BACKGROUND_INTENSITY+BACKGROUND_GREEN,
 BG_INTENS_RED     = BACKGROUND_INTENSITY+BACKGROUND_RED,
	   BG_CYAN    = BACKGROUND_BLUE+BACKGROUND_GREEN,
 BG_INTENS_CYAN    = BACKGROUND_INTENSITY+BG_CYAN,
	   BG_MAGENTA = BACKGROUND_RED+BACKGROUND_BLUE,
 BG_INTENS_MAGENTA = BACKGROUND_INTENSITY+BG_MAGENTA,
	   BG_YELLOW  = BACKGROUND_RED+BACKGROUND_GREEN,
 BG_INTENS_YELLOW  = BACKGROUND_INTENSITY+BG_YELLOW
};


//Hides cursor


void hidecursor()
{
 HANDLE hOut;
 CONSOLE_CURSOR_INFO ConCurInf;
 hOut=GetStdHandle(STD_OUTPUT_HANDLE);
 ConCurInf.dwSize=10;
 ConCurInf.bVisible=FALSE;
 SetConsoleCursorInfo(hOut,&ConCurInf);
}

//Puts a string on screen starting at x,y coord on screen

void putstr(int x,int y,char *s)
{
 gotoxy(x,y);
 _cprintf(s);
}


//Adaptation of GetAssyncKeyState

int getkey(int key)
{
 return (GetAsyncKeyState(key)&0x8000)>0;
}


//Set the text color
void settextcolor(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


//Makes console full screen
void AltEnter()
{
 keybd_event(VK_MENU,0x38,0,0);
 keybd_event(VK_RETURN,0x1c,0,0);
 keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
 keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
 return;
}


//Hides window
void HideWindow()
{
 HWND window;
 AllocConsole();
 window=FindWindowA("ConsoleWindowClass", NULL);
 ShowWindow(window,0);
}
