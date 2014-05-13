#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include "alex.h"
#define N 2
SDL_Surface *screen,*image1,*image1_bold,*image2,*image2_bold,*background;
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
 SDL_Flip(screen);
}
int up,down,poz=1;
int main( int argc, char* args[] )
{
  SDL_Init(SDL_INIT_EVERYTHING);
  screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
  image1=SDL_LoadBMP("image1.bmp");
  image1_bold=SDL_LoadBMP("image1_bold.bmp");
  image2=SDL_LoadBMP("image2.bmp");
  image2_bold=SDL_LoadBMP("image2_bold.bmp");
  background=SDL_LoadBMP("launcher_background_image.bmp");
  apply_surface(0,0,background,screen);
  apply_surface(450,500-80,image1_bold,screen);
  apply_surface(450,500,image2,screen);
  SDL_Flip(screen);
  while(getkey(VK_RETURN)==0 && getkey(VK_ESCAPE)==0)
           {
            up=getkey(VK_UP);
            down=getkey(VK_DOWN);
            if(up==1 && poz>1)
               {
                apply_surface(450,500-80,image1_bold,screen);
                poz--;
                apply_surface(450,500,image2,screen);
               }
            if(down==1 && poz<N)
               {
                apply_surface(450,500,image2_bold,screen);
                poz++;
                apply_surface(450,500-80,image1,screen);
               }
            SDL_Delay(100);
            SDL_Flip(screen);
           }
 if(getkey(VK_ESCAPE)==0)
    if(poz==2)
        {
         system("shop.exe");
         system("shop1.exe");
         system("a.exe");
        }
}
