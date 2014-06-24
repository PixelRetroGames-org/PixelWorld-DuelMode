#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include "alex.h"
#include<windows.h>
SDL_Surface *screen,*background;
SDL_Surface *image[5][3],*message,*clear;
SDL_Color color1={0,900,0},color2={450,0,0},color3{240,240,70};
Mix_Music *music=NULL;
int difficulty,computer;
TTF_Font *font=NULL;
Uint8 *keystates=SDL_GetKeyState(NULL);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
 SDL_Flip(screen);
}
void DuelMode_player_menu()
{
 SDL_Surface *bck=NULL,*image[5][5];
 SDL_Delay(200);
 image[1][1]=SDL_LoadBMP("Player1 vs Computer.bmp");
 image[1][2]=SDL_LoadBMP("Player1 vs Computer_bold.bmp");
 image[1][3]=SDL_LoadBMP("Player1 vs Computer_click.bmp");
 image[2][1]=SDL_LoadBMP("Computer vs Player2.bmp");
 image[2][2]=SDL_LoadBMP("Computer vs Player2_bold.bmp");
 image[2][3]=SDL_LoadBMP("Computer vs Player2_click.bmp");
 int N=2;
 int poz;
 int up,down,left,right;
 SDL_PumpEvents();
 apply_surface(0,0,background,screen);
 apply_surface(450,600-80,image[1][2],screen);
 apply_surface(450,600,image[2][1],screen);
 SDL_Flip(screen);
 poz=1;
 while(keystates[SDLK_RETURN]==0)
	  {
	   up=keystates[SDLK_UP];
	   down=keystates[SDLK_DOWN];
	   if(up==1 && poz>1)
		 {
		  apply_surface(450,600-80*(N-poz),image[poz][1],screen);
		  poz--;
		  apply_surface(450,520+80*(poz-1),image[poz][2],screen);
		 }
	   if(down==1 && poz<N)
	      {
		  apply_surface(450,520+80*(poz-1),image[poz][1],screen);
		  poz++;
		  apply_surface(450,600-80*(N-poz),image[poz][2],screen);
		 }
	   SDL_Delay(100);
	   SDL_Flip(screen);
	   SDL_PumpEvents();
	  }
 apply_surface(450,520+80*(poz-1),image[poz][3],screen);
 computer=N-poz+1;
 SDL_Delay(200);
 image[1][1]=SDL_LoadBMP("Easy.bmp");
 image[1][2]=SDL_LoadBMP("Easy_bold.bmp");
 image[1][3]=SDL_LoadBMP("Easy_click.bmp");
 image[2][1]=SDL_LoadBMP("Normal.bmp");
 image[2][2]=SDL_LoadBMP("Normal_bold.bmp");
 image[2][3]=SDL_LoadBMP("Normal_click.bmp");
 image[3][1]=SDL_LoadBMP("Hard.bmp");
 image[3][2]=SDL_LoadBMP("Hard_bold.bmp");
 image[3][3]=SDL_LoadBMP("Hard_click.bmp");
 image[4][1]=SDL_LoadBMP("Insane.bmp");
 image[4][2]=SDL_LoadBMP("Insane_bold.bmp");
 image[4][3]=SDL_LoadBMP("Insane_click.bmp");
 N=4;
 apply_surface(0,0,background,screen);
 apply_surface(450,600-80,image[1][2],screen);
 apply_surface(450,600,image[2][1],screen);
 apply_surface(450,680,image[3][1],screen);
 apply_surface(450,760,image[4][1],screen);
 SDL_Flip(screen);
 poz=1;
 SDL_PumpEvents();
 while(keystates[SDLK_RETURN]==0)
	  {
	   up=keystates[SDLK_UP];
	   down=keystates[SDLK_DOWN];
	   if(up==1 && poz>1)
		 {
		  apply_surface(450,760-80*(N-poz),image[poz][1],screen);
		  poz--;
		  apply_surface(450,520+80*(poz-1),image[poz][2],screen);
		 }
	   if(down==1 && poz<N)
	      {
		  apply_surface(450,520+80*(poz-1),image[poz][1],screen);
		  poz++;
		  apply_surface(450,760-80*(N-poz),image[poz][2],screen);
		 }
	   SDL_Delay(100);
	   SDL_Flip(screen);
	   SDL_PumpEvents();
	  }
 apply_surface(450,520+80*(poz-1),image[poz][3],screen);
 difficulty=poz;
}
int up,down,poz=1;
int main( int argc, char* args[] )
{
 first:
 int N=3;
 SDL_Init(SDL_INIT_EVERYTHING);
 TTF_Init();
 font=TTF_OpenFont("font2.ttf",50);
 screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
 image[1][1]=SDL_LoadBMP("single_player_mode.bmp");
 image[1][2]=SDL_LoadBMP("single_player_mode_bold.bmp");
 image[1][3]=SDL_LoadBMP("single_player_mode_click.bmp");
 image[2][1]=SDL_LoadBMP("duel_mode.bmp");
 image[2][2]=SDL_LoadBMP("duel_mode_bold.bmp");
 image[2][3]=SDL_LoadBMP("duel_mode_click.bmp");
 image[3][1]=SDL_LoadBMP("credits.bmp");
 image[3][2]=SDL_LoadBMP("credits_bold.bmp");
 image[3][3]=SDL_LoadBMP("credits_click.bmp");
 clear=SDL_LoadBMP("launcher_clear.bmp");
 background=SDL_LoadBMP("launcher_background_image.bmp");
 apply_surface(0,0,background,screen);
 apply_surface(450,600-80,image[1][2],screen);
 apply_surface(450,600,image[2][1],screen);
 apply_surface(450,680,image[3][1],screen);
 SDL_Flip(screen);
 poz=1;
 SDL_PumpEvents();
 while(keystates[SDLK_RETURN]==0 && keystates[SDLK_ESCAPE]==0)
	  {
	   up=keystates[SDLK_UP];
	   down=keystates[SDLK_DOWN];
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
	   SDL_PumpEvents();
	  }
 SDL_PumpEvents();
 if(keystates[SDLK_ESCAPE]==0)
    {
	apply_surface(450,520+80*(poz-1),image[poz][3],screen);
	SDL_PumpEvents();
     switch(poz)
	       {
	        case 1:
	               {
	                clear=SDL_LoadBMP("launcher_clear.bmp");
                     background=SDL_LoadBMP("launcher_background_image.bmp");
                     DuelMode_player_menu();
				 FILE *file=fopen("DuelMode_status.sts","w");
                     fprintf(file,"%d %d",difficulty,computer);
                     fclose(file);
                     if(computer!=1)
				    system("shop.exe");
				 else
				    system("shop1.exe");
				 system("a.exe");
				 break;
	               }
	        case 2:
                    {
                     clear=SDL_LoadBMP("launcher_clear.bmp");
                     background=SDL_LoadBMP("launcher_background_image.bmp");
				 FILE *file=fopen("DuelMode_status.sts","w");
                     fprintf(file,"0 0");
                     fclose(file);
				 system("shop.exe");
				 system("shop1.exe");
				 system("a.exe");
				 break;
                    }
             case 3:
                    {
                     SDL_PumpEvents();
                     Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
                     music=Mix_LoadMUS("credits_bck.wav");
                     Mix_PlayMusic(music,-1);
				 background=SDL_LoadBMP("wooden_background.bmp");
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
                     message=TTF_RenderText_Solid(font," Teo Oprescu: ",color2);
                     apply_surface(200,450,message,screen);
                     message=TTF_RenderText_Solid(font,"Graphics",color1);
                     apply_surface(560,450,message,screen);
                     SDL_PumpEvents();
                     while(keystates[SDLK_RETURN]==0 && keystates[SDLK_ESCAPE]==0)
                           {
                            SDL_PumpEvents();
					  }
                     Mix_CloseAudio();
                     goto first;
                     break;
                    }
	       }
    }
}
