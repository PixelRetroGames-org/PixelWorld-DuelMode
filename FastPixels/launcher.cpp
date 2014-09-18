#include<cstdio>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<windows.h>
#include<alex.h>
#include<ctime>
// 1280x800
SDL_Surface *screen,*background,*image[5][5];
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
int main(int argc,char *args[])
{
 SDL_Init(SDL_INIT_EVERYTHING);
 Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,1,4096);
 screen=SDL_SetVideoMode(1280,800,32,SDL_FULLSCREEN);
 TTF_Init();
 background=SDL_LoadBMP();
 image[1][1]=SDL_LoadBMP("Player1 vs Computer.bmp");
 image[1][2]=SDL_LoadBMP("Player1 vs Computer_bold.bmp");
 image[1][3]=SDL_LoadBMP("Player1 vs Computer_click.bmp");
 image[2][1]=SDL_LoadBMP("Computer vs Player2.bmp");
 image[2][2]=SDL_LoadBMP("Computer vs Player2_bold.bmp");
 image[2][3]=SDL_LoadBMP("Computer vs Player2_click.bmp");
}
