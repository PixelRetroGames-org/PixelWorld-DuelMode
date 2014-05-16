#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include "alex.h"
#include<windows.h>
#define N 3
SDL_Surface *screen,*background;
SDL_Surface *image[5][3],*message;
SDL_Color color1={0,900,0},color2={450,0,0},color3{240,240,70};
Mix_Music *music=NULL;
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
{ mmain:
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  font=TTF_OpenFont("font2.ttf",50);
  screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
  image[1][1]=TTF_RenderText_Solid(font,"Single Player Mode ",color1);
  image[1][2]=TTF_RenderText_Solid(font,"Single Player Mode ",color2);
  image[2][1]=TTF_RenderText_Solid(font,"Duel Mode ",color1);
  image[2][2]=TTF_RenderText_Solid(font,"Duel Mode",color2);
  image[3][1]=TTF_RenderText_Solid(font,"Credits",color1);
  image[3][2]=TTF_RenderText_Solid(font,"Credits",color2);
  background=SDL_LoadBMP("launcher_background_image.bmp");
  apply_surface(0,0,background,screen);
  apply_surface(450,600-80,image[1][2],screen);
  apply_surface(450,600,image[2][1],screen);
  apply_surface(450,680,image[3][1],screen);
  SDL_Flip(screen);
  poz=1;
  while(getkey(VK_RETURN)==0 && getkey(VK_ESCAPE)==0)
           {
            up=getkey(VK_UP);
            down=getkey(VK_DOWN);
            if(up==1 && poz>1)
               {
                apply_surface(450,680-80*(N-poz),image[poz][1],screen);
                poz--;
                apply_surface(450,520+80*(poz-1),image[poz][2],screen);
               }
            if(down==1 && poz<N)
               {
                apply_surface(450,520+80*(poz-1),image[poz][1],screen);
                poz++;
                apply_surface(450,680-80*(N-poz),image[poz][2],screen);
               }
            SDL_Delay(100);
            SDL_Flip(screen);
           }
 if(getkey(VK_ESCAPE)==0)
    {
     switch(poz)
	       {
	        case 1:break;
	        case 2:
                    {
				 system("shop.exe");
				 system("shop1.exe");
				 system("a.exe");
				 break;
                    }
             case 3:
                    {
                     Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
                     music=Mix_LoadMUS("credits_bck.wav");
                     Mix_PlayMusic(music,-1);
				 apply_surface(0,0,background,screen);
                     message=TTF_RenderText_Solid(font,"Game Made By ",color1);
                     apply_surface(0,0,message,screen);
                     message=TTF_RenderText_Solid(font,"PIXEL RETRO GAMES COMPANY ",color2);
                     apply_surface(400,0,message,screen);
                     message=TTF_RenderText_Solid(font,"2013-2014",color1);
                     apply_surface(600,50,message,screen);

                     message=TTF_RenderText_Solid(font,"Owners: ",color1);
                     apply_surface(0,150,message,screen);
                     message=TTF_RenderText_Solid(font,"Alex Cioltan      Stef Enescu",color2);
                     apply_surface(250,150,message,screen);
                     message=TTF_RenderText_Solid(font,"and",color1);
                     apply_surface(560,150,message,screen);

                     message=TTF_RenderText_Solid(font,"Team: ",color1);
                     apply_surface(0,250,message,screen);
                     message=TTF_RenderText_Solid(font,"   Alex Cioltan:",color2);
                     apply_surface(100,250,message,screen);
                     message=TTF_RenderText_Solid(font,"Code, Graphics",color1);
                     apply_surface(500,250,message,screen);
                     message=TTF_RenderText_Solid(font,"   Stef Enescu:",color2);
                     apply_surface(80,300,message,screen);
                     message=TTF_RenderText_Solid(font,"Code, Graphics",color1);
                     apply_surface(500,300,message,screen);
                     message=TTF_RenderText_Solid(font," Razvan Ionescu:",color2);
                     apply_surface(100,350,message,screen);
                     message=TTF_RenderText_Solid(font," Graphics",color1);
                     apply_surface(550,350,message,screen);
                     message=TTF_RenderText_Solid(font," Alex Duta: ",color2);
                     apply_surface(200,400,message,screen);
                     message=TTF_RenderText_Solid(font,"Graphics",color1);
                     apply_surface(500,400,message,screen);
                     while(getkey(VK_RETURN)==0 && getkey(VK_ESCAPE)==0);
                     goto mmain;
                     break;
                    }
	       }
    }
}
