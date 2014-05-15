#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include "alex.h"
#define N 2
SDL_Surface *screen,*image1,*image1_bold,*image2,*image2_bold,*background;
SDL_Color color1={0,900,0},color2={450,0,0},color3{240,240,70};
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
 SDL_Flip(screen);
}
int up,down,poz=1;
TTF_Font *font=NULL;
int main( int argc, char* args[] )
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  font=TTF_OpenFont("font2.ttf",50);
  screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
  image1=TTF_RenderText_Solid(font,"Single Player Mode ",color1);
  image1_bold=TTF_RenderText_Solid(font,"Single Player Mode ",color2);
  image2=TTF_RenderText_Solid(font,"Duel Mode ",color1);
  image2_bold=TTF_RenderText_Solid(font,"Duel Mode",color2);
  background=SDL_LoadBMP("launcher_background_image.bmp");
  apply_surface(0,0,background,screen);
  apply_surface(450,600-80,image1_bold,screen);
  apply_surface(450,600,image2,screen);
  SDL_Flip(screen);
  while(getkey(VK_RETURN)==0 && getkey(VK_ESCAPE)==0)
           {
            up=getkey(VK_UP);
            down=getkey(VK_DOWN);
            if(up==1 && poz>1)
               {
                apply_surface(450,600-80,image1_bold,screen);
                poz--;
                apply_surface(450,600,image2,screen);
               }
            if(down==1 && poz<N)
               {
                apply_surface(450,600,image2_bold,screen);
                poz++;
                apply_surface(450,600-80,image1,screen);
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
