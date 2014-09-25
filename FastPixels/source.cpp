#include<cstdio>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include<windows.h>
#include "alex.h"
#include<ctime>
#include<string>
// 1280x800
SDL_Surface *car1[4],*car2[4],*screen,*background;
SDL_Surface *white_line[10],*asphalt[10];
int frame=1,aframe=1,tme,tme1,car1_state,car2_state;
int speed_t=0;
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
SDL_Surface *make_it_transparent( std::string filename )
{
 //The image that's loaded
 SDL_Surface *loadedImage=NULL;
 //The optimized image that will be used
 SDL_Surface *optimizedImage=NULL;
 //Load the image
 loadedImage=IMG_Load(filename.c_str());
 //If the image loaded
 if(loadedImage!=NULL)
    {
	//Create an optimized image
	optimizedImage=SDL_DisplayFormat(loadedImage);
	//Free the old image
	SDL_FreeSurface(loadedImage);
	//If the image was optimized just fine
	if(optimizedImage!=NULL)
        {
	    //Map the color key
	    Uint32 colorkey=SDL_MapRGB(optimizedImage->format,0xFF,0x0,0xE1);
	    //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
	    SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
        }
    }
 //Return the optimized image
 return optimizedImage;
}
void move_line(int frame)
{
 SDL_Surface *image=SDL_LoadBMP("white_line.bmp");
 SDL_Surface *clear=SDL_LoadBMP("black_line.bmp");
 apply_surface(0,380,white_line[frame],screen);
 SDL_Flip(screen);
}
void move_asphalt(int frame)
{
 apply_surface(0,0,asphalt[frame],screen);
 SDL_Flip(screen);
}
void load_all()
{
 white_line[1]=SDL_LoadBMP("images/white_line1.bmp");
 white_line[2]=SDL_LoadBMP("images/white_line2.bmp");
 white_line[3]=SDL_LoadBMP("images/white_line3.bmp");
 white_line[4]=SDL_LoadBMP("images/white_line4.bmp");
 white_line[5]=SDL_LoadBMP("images/white_line5.bmp");
 white_line[6]=SDL_LoadBMP("images/white_line6.bmp");
 white_line[7]=SDL_LoadBMP("images/white_line7.bmp");
 white_line[8]=SDL_LoadBMP("images/white_line8.bmp");
 white_line[9]=SDL_LoadBMP("images/white_line9.bmp");

 asphalt[1]=make_it_transparent("images/asphalt1.bmp");
 asphalt[2]=make_it_transparent("images/asphalt2.bmp");
 asphalt[3]=make_it_transparent("images/asphalt3.bmp");
 asphalt[4]=make_it_transparent("images/asphalt4.bmp");
 asphalt[5]=make_it_transparent("images/asphalt5.bmp");
 asphalt[6]=make_it_transparent("images/asphalt6.bmp");
 asphalt[7]=make_it_transparent("images/asphalt7.bmp");
 asphalt[8]=make_it_transparent("images/asphalt8.bmp");
 asphalt[9]=make_it_transparent("images/asphalt9.bmp");
 car1[1]=make_it_transparent("images/cars/green1.bmp");
 car2[1]=make_it_transparent("images/cars/purple1.bmp");
 car1[2]=make_it_transparent("images/cars/green2.bmp");
 car2[2]=make_it_transparent("images/cars/purple2.bmp");
}
int main(int argc,char *args[])
{
 SDL_Init(SDL_INIT_EVERYTHING);
 Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,1,4096);
 screen=SDL_SetVideoMode(1280,800,32,SDL_FULLSCREEN);
 TTF_Init();
 load_all();
 apply_surface(0,0,asphalt[1],screen);
 apply_surface(400,180,car1[1],screen);
 apply_surface(400,400,car2[1],screen);
 SDL_Flip(screen);
 while(getkey(VK_ESCAPE)==0)
       {
        tme=time(NULL);
        if(tme-tme1>=speed_t)
           {
            move_asphalt(aframe);
            move_line(frame);
            apply_surface(400,180,car1[car1_state%2+1],screen);
            apply_surface(400,400,car2[car2_state%2+1],screen);
            SDL_Flip(screen);
            frame++;
            if(frame>=10)
               {
                frame=1;
                car1_state++;
                car2_state++;
               }
            aframe++;
            if(aframe>=10)
               aframe=1;
            tme1=time(NULL);
           }
       }
}
