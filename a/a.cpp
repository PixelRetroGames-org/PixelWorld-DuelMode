#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#define COL_START 6
#define LIN_MAX 19
#define COL_MAX 19
#include<cstdio>
#define HP1 100
#include<ctime>
/***
 NOTE: Player1 is really Player1
       Player is actually Player2
 TO DO LATER: A good way to make the code more simple is to make players objects...
***/
Mix_Chunk *sound;
Mix_Music *music=NULL;
SDL_Color textColor={0,900,200}, color1={0,900,0},color2={450,0,0},color3{240,240,70};
TTF_Font *font=NULL;
SDL_Surface *message=NULL,*clear=NULL,*burn=NULL,*player2=NULL;
char pp,mute=1;
int player1_items[10][10];
int player_items[10][10];
int player1_items_equipped[7],player_items_equipped[7];
int player1_attack,player1_block,player1_fire_res,player1_fire_dmg;
int player_attack,player_block,player_fire_res,player_fire_dmg;
Uint8 *keystates=SDL_GetKeyState(NULL);
int time_ex,beg1,beg2,end1,end2,t,t1,permission_player,permission_player1,t2,permission_basic_player,permission_basic_player1,flag_player;
int power1,power2,power3,power4;
int player1_hp=HP1,player_hp=HP1,player_mana=HP1,player1_mana=HP1;
int up,down,right,left,atack_left,atack_right,atack1_left,atack1_right;
int player1_lin=LIN_MAX/2,player1_col=COL_MAX/2-5,player_lin=LIN_MAX/2,player_col=COL_MAX/2+5;
int player1_money,player_money,player_xp,player1_xp;
int v[LIN_MAX+3][COL_MAX+3],obs[LIN_MAX+3][COL_MAX+3];
SDL_Surface *image=NULL;
SDL_Surface *screen=NULL;
SDL_Surface *player=NULL;
SDL_Surface *player1=NULL;
SDL_Surface *background=NULL;
char file[100];
int max(int a,int b)
{
 if(a>b)
    return a;
 else
    return b;
}
int min(int a,int b)
{
 if(a<b)
    return a;
 else
    return b;
}
void load_save_player1(char *nume_salvare)
{
 char nume_salvare1[100];
 memset(nume_salvare1,0,100);
 strcpy(nume_salvare1,nume_salvare);
 int nr=strlen(nume_salvare1);
 nume_salvare1[nr]='.';
 nume_salvare1[nr+1]='p';
 nume_salvare1[nr+2]='w';
 nume_salvare1[nr+3]='s';
 nume_salvare1[nr+4]=NULL;
 nr+=4;
 FILE *salvare=fopen(nume_salvare1,"r");
 if(salvare==NULL)
    {
     salvare=fopen(nume_salvare1,"w");
     fprintf(salvare,"0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");
     fclose(salvare);
     salvare=fopen(nume_salvare1,"r");
    }
 fscanf(salvare,"%d %d",&player1_money,&player1_xp);
 for(int j=1;j<=5;j++)
     for(int i=1;i<=4;i++)
	    fscanf(salvare,"%d",&player1_items[i][j]);
 if(player1_items[1][4]==1)
    player1_items_equipped[1]=4;
 else
    if(player1_items[1][3]==1)
        player1_items_equipped[1]=3;
    else
        if(player1_items[1][2]==1)
            player1_items_equipped[1]=2;
        else
            if(player1_items[1][1]==1)
                player1_items_equipped[1]=1;
 if(player1_items[2][4]==1)
    player1_items_equipped[2]=4;
 else
    if(player1_items[2][3]==1)
        player1_items_equipped[2]=3;
    else
        if(player1_items[2][2]==1)
            player1_items_equipped[2]=2;
        else
            if(player1_items[2][1]==1)
                player1_items_equipped[2]=1;
 if(player1_items[3][4]==1)
    player1_items_equipped[3]=4;
 else
    if(player1_items[3][3]==1)
        player1_items_equipped[3]=3;
    else
        if(player1_items[3][2]==1)
            player1_items_equipped[3]=2;
        else
            if(player1_items[3][1]==1)
                player1_items_equipped[3]=1;
 if(player1_items[4][4]==1)
    player1_items_equipped[4]=4;
 else
    if(player1_items[4][3]==1)
        player1_items_equipped[4]=3;
    else
        if(player1_items[4][2]==1)
            player1_items_equipped[4]=2;
        else
            if(player1_items[4][1]==1)
                player1_items_equipped[4]=1;
 if(player1_items[1][5]==1)
    player1_items_equipped[5]=1;
 else
    if(player1_items[2][5]==1)
        player1_items_equipped[5]=2;
    else
        if(player1_items[3][5]==1)
            player1_items_equipped[5]=3;
        else
            if(player1_items[4][5]==1)
                player1_items_equipped[5]=4;
 if(player1_items_equipped[1]==1)
    player1_block+=10;
 if(player1_items_equipped[2]==1)
    player1_block+=10;
 if(player1_items_equipped[3]==1)
    player1_block+=10;
 if(player1_items_equipped[4]==1)
    player1_block+=10;
 if(player1_items_equipped[5]==1)
    player1_attack+=10;
 if(player1_items_equipped[1]==2)
    {player1_block+=14;
    player1_fire_res+=3;
    }
 if(player1_items_equipped[2]==2)
    {player1_block+=14;
    player1_fire_res+=3;
    }
 if(player1_items_equipped[3]==2)
    {player1_block+=14;
    player1_fire_res+=3;
    }
 if(player1_items_equipped[4]==2)
    {player1_block+=14;
    player1_fire_res+=3;
    }
 if(player1_items_equipped[5]==2)
    {player1_attack+=15;
    player1_fire_dmg+=3;
    }
 if(player1_items_equipped[1]==3)
    {player1_block+=17;
    player1_fire_res+=8;
    }
 if(player1_items_equipped[2]==3)
    {player1_block+=17;
    player1_fire_res+=8;
    }
 if(player1_items_equipped[3]==3)
    {player1_block+=17;
    player1_fire_res+=8;
    }
 if(player1_items_equipped[4]==3)
    {player1_block+=17;
    player1_fire_res+=8;
    }
 if(player1_items_equipped[5]==3)
    {player1_attack+=17;
    player1_fire_dmg+=7;
    }
 if(player1_items_equipped[1]==4)
    {player1_block+=20;
    player1_fire_res+=14;
    }
 if(player1_items_equipped[2]==4)
    {player1_block+=20;
    player1_fire_res+=14;
    }
 if(player1_items_equipped[3]==4)
    {player1_block+=20;
    player1_fire_res+=14;
    }
 if(player1_items_equipped[4]==4)
    {player1_block+=20;
    player1_fire_res+=14;
    }
 if(player1_items_equipped[5]==4)
    {player1_attack+=25;
    player1_fire_dmg+=10;
    }
}
void load_save_player(char *nume_salvare)
{
 char nume_salvare1[100];
 memset(nume_salvare1,0,100);
 strcpy(nume_salvare1,nume_salvare);
 int nr=strlen(nume_salvare1);
 nume_salvare1[nr]='.';
 nume_salvare1[nr+1]='p';
 nume_salvare1[nr+2]='w';
 nume_salvare1[nr+3]='s';
 nume_salvare1[nr+4]=NULL;
 nr+=4;
 FILE *salvare=fopen(nume_salvare1,"r");
 if(salvare==NULL)
    {
     salvare=fopen(nume_salvare1,"w");
     fprintf(salvare,"0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");
     fclose(salvare);
     salvare=fopen(nume_salvare1,"r");
    }
 fscanf(salvare,"%d %d",&player_money,&player_xp);
 for(int j=1;j<=5;j++)
     for(int i=1;i<=4;i++)
	    fscanf(salvare,"%d",&player_items[i][j]);
 if(player_items[1][4]==1)
    player_items_equipped[1]=4;
 else
    if(player_items[1][3]==1)
        player_items_equipped[1]=3;
    else
        if(player_items[1][2]==1)
            player_items_equipped[1]=2;
        else
            if(player_items[1][4]==1)
                player_items_equipped[1]=1;
 if(player_items[2][4]==1)
    player_items_equipped[2]=4;
 else
    if(player_items[2][3]==1)
        player_items_equipped[2]=3;
    else
        if(player_items[2][2]==1)
            player_items_equipped[2]=2;
        else
            if(player_items[2][4]==1)
                player_items_equipped[2]=1;
 if(player_items[3][4]==1)
    player_items_equipped[3]=4;
 else
    if(player_items[3][3]==1)
        player_items_equipped[3]=3;
    else
        if(player_items[3][2]==1)
            player_items_equipped[3]=2;
        else
            if(player_items[3][4]==1)
                player_items_equipped[3]=1;
 if(player_items[4][4]==1)
    player_items_equipped[4]=4;
 else
    if(player_items[4][3]==1)
        player_items_equipped[4]=3;
    else
        if(player_items[4][2]==1)
            player_items_equipped[4]=2;
        else
            if(player_items[4][4]==1)
                player_items_equipped[4]=1;
 if(player_items[1][5]==1)
    player_items_equipped[5]=4;
 else
    if(player_items[2][5]==1)
        player_items_equipped[5]=3;
    else
        if(player_items[3][5]==1)
            player_items_equipped[5]=2;
        else
            if(player_items[4][5]==1)
                player_items_equipped[5]=1;
 if(player_items_equipped[1]==1)
    player_block+=10;
 if(player_items_equipped[2]==1)
    player_block+=10;
 if(player_items_equipped[3]==1)
    player_block+=10;
 if(player_items_equipped[4]==1)
    player_block+=10;
 if(player_items_equipped[5]==1)
    player_attack+=10;
 if(player_items_equipped[1]==2)
    {player_block+=14;
    player_fire_res+=3;
    }
 if(player_items_equipped[2]==2)
    {player_block+=14;
    player_fire_res+=3;
    }
 if(player_items_equipped[3]==2)
    {player_block+=14;
    player_fire_res+=3;
    }
 if(player_items_equipped[4]==2)
    {player_block+=14;
    player_fire_res+=3;
    }
 if(player_items_equipped[5]==2)
    {player_attack+=15;
    player_fire_dmg+=3;
    }
 if(player_items_equipped[1]==3)
    {player_block+=17;
    player_fire_res+=8;
    }
 if(player_items_equipped[2]==3)
    {player_block+=17;
    player_fire_res+=8;
    }
 if(player_items_equipped[3]==3)
    {player_block+=17;
    player_fire_res+=8;
    }
 if(player_items_equipped[4]==3)
    {player_block+=17;
    player_fire_res+=8;
    }
 if(player_items_equipped[5]==3)
    {player_attack+=17;
    player_fire_dmg+=7;
    }
 if(player_items_equipped[1]==4)
    {player_block+=20;
    player_fire_res+=14;
    }
 if(player_items_equipped[2]==4)
    {player_block+=20;
    player_fire_res+=14;
    }
 if(player_items_equipped[3]==4)
    {player_block+=20;
    player_fire_res+=14;
    }
 if(player_items_equipped[4]==4)
    {player_block+=20;
    player_fire_res+=14;
    }
 if(player_items_equipped[5]==4)
    {player_attack+=25;
    player_fire_dmg+=10;
    }
}
void save_player(char *nume_salvare)
{
 char nume_salvare1[100];
 memset(nume_salvare1,0,100);
 strcpy(nume_salvare1,nume_salvare);
 int nr=strlen(nume_salvare1);
 nume_salvare1[nr]='.';
 nume_salvare1[nr+1]='p';
 nume_salvare1[nr+2]='w';
 nume_salvare1[nr+3]='s';
 nume_salvare1[nr+4]=NULL;
 nr+=4;
 FILE *salvare=fopen(nume_salvare1,"w");
 fprintf(salvare,"%d\n%d\n",player_money,player_xp);
 for(int j=1;j<=5;j++)
     {
	 for(int i=1;i<=4;i++)
	     {
		 fprintf(salvare,"%d\n",player_items[i][j]);
	     }
      fprintf(salvare,"\n");
     }
}
void save_player1(char *nume_salvare)
{
 char nume_salvare1[100];
 memset(nume_salvare1,0,100);
 strcpy(nume_salvare1,nume_salvare);
 int nr=strlen(nume_salvare1);
 nume_salvare1[nr]='.';
 nume_salvare1[nr+1]='p';
 nume_salvare1[nr+2]='w';
 nume_salvare1[nr+3]='s';
 nume_salvare1[nr+4]=NULL;
 nr+=4;
 FILE *salvare=fopen(nume_salvare1,"w");
 fprintf(salvare,"%d\n%d\n",player1_money,player1_xp);
 for(int j=1;j<=5;j++)
     {
	 for(int i=1;i<=4;i++)
          {
	 	 fprintf(salvare,"%d\n",player1_items[i][j]);
          }
      fprintf(salvare,"\n");
     }
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
void put_back(int l,int c)
{
 switch(v[l][c])
	   {
	    case 1: {
			   image=SDL_LoadBMP("tree.bmp");
			   break;
			  }
	    case 2: {
	    	        image=SDL_LoadBMP("grass.bmp");
			   break;
			  }
	    case 3: {
	    	        image=SDL_LoadBMP("bricks.bmp");
	    	        break;
			  }
	   }
 apply_surface((c+COL_START)*40,l*40,image,screen);
}
void load_level(char *name)
{
 int n=strlen(name),i,j;
 strcpy(file,name);
 file[n]='.';
 file[n+1]='l';
 file[n+2]='v';
 file[n+3]='l';
 file[n+4]=NULL;
 FILE *fin=fopen(file,"r");
 for(i=0;i<=LIN_MAX;i++)
     for(j=0;j<=COL_MAX;j++)
         fscanf(fin,"%d",&v[i][j]);
fclose(fin);
}
void print_level()
{
 int i,j,i1=1,j1=1;
 for(i=0,i1=0;i1<=LIN_MAX;i+=40,i1++)
     for(j=0,j1=0;j1<=COL_MAX;j+=40,j1++)
         {
         	if(obs[i1][j1]<=1){
          switch(v[i1][j1])
          {
           case 1:  {image=SDL_LoadBMP("tree.bmp");
                     obs[i1][j1]=1;
                     break;}
           case 2:  {image=SDL_LoadBMP("grass.bmp");  break;}
           case 3:  {image=SDL_LoadBMP("bricks.bmp");  break;}
           case 4:  {image=SDL_LoadBMP("fire.bmp");  break;}
           case 5:  {image=SDL_LoadBMP("bricks.bmp");
                     obs[i1][j1]=1;
                     break;}
          }
          //SDL_BlitSurface(image,NULL,screen,NULL);
          apply_surface(j+COL_START*40,i,image,screen);}
         }
}
void print_background()
{
 background=SDL_LoadBMP("background1.bmp");
 int i,j;
 for(i=0;i<=LIN_MAX;i++)
     {
	 apply_surface((COL_MAX+COL_START+1)*40,i*40,background,screen);
	 apply_surface((COL_START-1)*40,i*40,background,screen);
	}
}
void print_hp(int a,int lin,int col)
{
 int i=0,i1,j;
 if(a<0)
    a=0;
 char v[5]={0,0,0,0,0},v1[5]={0,0,0,0,0};
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=1,j=i;i1<=i;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 v1[i+1]='%';
 clear=SDL_LoadBMP("clear.bmp");
 apply_surface(col*40,lin*40,clear,screen);
 message=TTF_RenderText_Solid(font,v1+1,color2);
 apply_surface(col*40,lin*40,message,screen);
}
void get_burn(int i,int j)
{
 burn=SDL_LoadBMP("burn.bmp");
}
void print_mana(int a,int lin,int col)
{
 int i=0,i1,j;
 char v[5]={0,0,0,0,0},v1[5]={0,0,0,0,0};
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=1,j=i;i1<=i;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 v1[i+1]='%';
 clear=SDL_LoadBMP("clear1.bmp");
 apply_surface(col*40,lin*40,clear,screen);
 message=TTF_RenderText_Solid(font,v1+1,color3);
 apply_surface(col*40,lin*40,message,screen);
}
void welcome_message()
{
 SDL_Surface *message1=TTF_RenderText_Solid(font,"Welcome to Pixel World : Duel Mode! ",color2);
 apply_surface(320,160,message1,screen);
 SDL_FreeSurface(message1);
 SDL_Surface *message2=TTF_RenderText_Solid(font,"Code: Alex Cioltan ",color2);
 apply_surface(320,200,message2,screen);
 SDL_Surface *message3=TTF_RenderText_Solid(font,"Graphics: Stefan Enescu and Alex Cioltan",color2);
 apply_surface(320,240,message3,screen);
 SDL_Flip(screen);
 SDL_Delay(2000);
}
void put_arena_wall()
{
 for(int i=1;i<=LIN_MAX-1;i++)
	{
	 v[i][COL_MAX/2]=5;
	}
}
void clear_arena_wall()
{
 for(int i=1;i<=LIN_MAX-1;i++)
	{
	 v[i][COL_MAX/2]=2;
	 obs[i][COL_MAX/2]=0;
	}
}
int main( int argc, char* args[] )
{
 SDL_Init(SDL_INIT_EVERYTHING);
 Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
 //screen=SDL_SetVideoMode((LIN_MAX+1)*40,(COL_MAX+1)*40,32,SDL_FULLSCREEN/*SDL_SWSURFACE*/);
 screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
 TTF_Init();
 font=TTF_OpenFont("font.ttf",40);
 music=Mix_LoadMUS("bck.wav");
 clear=SDL_LoadBMP("wooden_background.bmp");
 apply_surface(0,0,clear,screen);
 if(mute==0)
    Mix_PlayMusic(music, -1 );
 clear=SDL_LoadBMP("clear.bmp");
 load_level("a");
 print_level();
 welcome_message();
 print_background();
 burn=SDL_LoadBMP("fire.bmp");
 background=SDL_LoadBMP("name_background.bmp");
 message=TTF_RenderText_Solid(font,"Player 2",color1);
 apply_surface((COL_MAX+COL_START+2)*40,0,background,screen);
 apply_surface((COL_MAX+COL_START+2)*40+5,0,message,screen);
 SDL_Flip(screen);
 message=TTF_RenderText_Solid(font,"Player 1",color1);
 apply_surface((0)*40,0,background,screen);
 apply_surface((0)*40+5,0,message,screen);
 SDL_Flip(screen);
 player=SDL_LoadBMP("warrior_on_grass.bmp");
 player1=SDL_LoadBMP("warrior1_on_grass.bmp");
 obs[player_lin][player_col]=2;
 obs[player1_lin][player1_col]=3;
 print_hp(player_hp,1,COL_MAX+COL_START+2);
 print_hp(player1_hp,1,0);
 print_mana(player_mana,2,COL_MAX+COL_START+2);
 print_mana(player_mana,2,0);
 time_ex=0;
 if(mute<=1)
    sound=Mix_LoadWAV("hit.wav");
 print_level();
 int start_t=0;
 put_arena_wall();
 load_save_player1("player1");
 load_save_player("player2");
 while(keystates[SDLK_ESCAPE]==NULL && player1_hp>0 && player_hp>0)
       {flag_player=0;
	   t=time(NULL);
        if(t-t1>=2)
           {
            start_t++;
            if(start_t>=4)
               {
			 clear_arena_wall();
               }
            t1=t;
            if(player_mana<=99)
			{
			 player_mana++;
			 print_mana(player_mana,2,COL_MAX+COL_START+2);
			}
		  if(player1_mana<=99)
			{
			 player1_mana++;
			 print_mana(player1_mana,2,0);
			}
            //load_level("a");
            print_level();
            permission_player=permission_player1=0;
           }
	   if(t-t2>=1)
		 {
		  t2=t;
		  permission_basic_player=permission_basic_player1=0;
		 }
        up=keystates[SDLK_UP];
        down=keystates[SDLK_DOWN];
        right=keystates[SDLK_RIGHT];
        left=keystates[SDLK_LEFT];
        atack_left=keystates[SDLK_RCTRL];
        atack_right=keystates[SDLK_RCTRL];
        power1=keystates[SDLK_u];
        power2=keystates[SDLK_i];
        power3=keystates[SDLK_o];
        power4=keystates[SDLK_p];
        atack1_left=keystates[SDLK_z];
        atack1_right=keystates[SDLK_z];
        if(power1==1 && player_mana>=10 && player_hp<=90)
           {
            player_mana-=10;
            player_hp+=10;
            print_mana(player_mana,2,COL_MAX+COL_START+2);
            print_hp(player_hp,1,COL_MAX+COL_START+2);
           }
        if(power2==1 && player_mana>=30 && permission_player==0)
           {
            player_mana-=30;
            permission_player=1;
            if(max(player1_lin,player_lin)-min(player1_lin,player_lin)<=2 && max(player1_col,player_col)-min(player1_col,player_col)<=2)
               {
                player1_hp-=40+player_fire_dmg*3/10-player1_fire_res*3/10;
                print_hp(player1_hp,1,0);
               }
            if(player_lin-2<=0)
               beg1=1;
            else
               beg1=player_lin-2;
            if(player_lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player_lin+2;
            if(player_col-2<=0)
               beg2=1;
            else
               beg2=player_col-2;
            if(player_col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player_col+2;
            for(int i=beg1;i<=end1;i++)
                for(int j=beg2;j<=end2;j++)
                    {
                     if(obs[i][j]==0)
                        {
                         //get_burn(i,j);
                         //burn=SDL_LoadBMP("fire.bmp");
                         apply_surface((j+COL_START)*40,i*40,burn,screen);
                        }
                    }
            print_mana(player_mana,2,COL_MAX+COL_START+2);
           }
        if(power3==1 && player_hp>10)
           {
            player_hp-=10;
            player_mana+=10;
            print_mana(player_mana,2,COL_MAX+COL_START+2);
            print_hp(player_hp,1,COL_MAX+COL_START+2);
           }
        if(atack_left==1 && permission_basic_player==0)
           {
            player=SDL_LoadBMP("warrior_on_grass_left.bmp");
            if(obs[player_lin][player_col-1]==3)
               {
			    permission_basic_player=1;
			    player1_hp-=10+player_attack/10-player1_block/10;
                print_hp(player1_hp,1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack_right==1 && permission_basic_player==0)
           {
            player=SDL_LoadBMP("warrior_on_grass.bmp");
            if(obs[player_lin][player_col+1]==3)
               {
			    permission_basic_player=1;
			    player1_hp-=10+player_attack/10-player1_block/10;
                print_hp(player1_hp,1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player_lin>1)
           {
            time_ex++;
            if(obs[player_lin-1][player_col]==0)
               {
                obs[player_lin][player_col]=0;
			 put_back(player_lin,player_col);
                player_lin--;
                obs[player_lin][player_col]=2;
               }
           }
        if(down==1 && player_lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player_lin+1][player_col]==0)
               {
                obs[player_lin][player_col]=0;
			 put_back(player_lin,player_col);
                player_lin++;
                obs[player_lin][player_col]=2;
               }
           }
        if(left==1 && player_col>1)
           {
		  time_ex++;
            if(obs[player_lin][player_col-1]==0)
               {
                obs[player_lin][player_col]=0;
			 put_back(player_lin,player_col);
                player_col--;
                obs[player_lin][player_col]=2;
                player=SDL_LoadBMP("warrior_on_grass_left.bmp");
               }
           }
        if(right==1 && player_col<LIN_MAX)
           {
            time_ex++;
            if(obs[player_lin][player_col+1]==0)
               {
                obs[player_lin][player_col]=0;
			 put_back(player_lin,player_col);
                player_col++;
                obs[player_lin][player_col]=2;
                player=SDL_LoadBMP("warrior_on_grass.bmp");
               }
           }
        apply_surface((player_col+COL_START)*40,player_lin*40,player,screen);
        up=keystates[SDLK_w];
        down=keystates[SDLK_s];
        right=keystates[SDLK_d];
        left=keystates[SDLK_a];
        power1=keystates[SDLK_1];
        power2=keystates[SDLK_2];
        power3=keystates[SDLK_3];
        power4=keystates[SDLK_4];
        if(power1==1 && player1_mana>=10 && player1_hp<=90)
           {
            player1_mana-=10;
            player1_hp+=10;
            print_mana(player1_mana,2,0);
            print_hp(player1_hp,1,0);
           }
        if(power2==1 && player1_mana>=30 && permission_player1==0)
           {
            player1_mana-=30;
            permission_player1=1;
            if(max(player_lin,player1_lin)-min(player1_lin,player_lin)<=2 && max(player1_col,player_col)-min(player1_col,player_col)<=2)
               {
                player_hp-=40+player1_fire_dmg*3/10-player_fire_res*3/10;
                print_hp(player_hp,1,COL_MAX+COL_START+2);
               }
            if(player1_lin-2<=0)
               beg1=1;
            else
               beg1=player1_lin-2;
            if(player1_lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player1_lin+2;
            if(player1_col-2<=0)
               beg2=1;
            else
               beg2=player1_col-2;
            if(player1_col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player1_col+2;
            for(int i=beg1;i<=end1;i++)
                for(int j=beg2;j<=end2;j++)
                    {
                     if(obs[i][j]==0)
                        {
                         //get_burn(i,j);
                         //burn=SDL_LoadBMP("fire.bmp");
                         apply_surface((j+COL_START)*40,i*40,burn,screen);
                        }
                    }
            print_mana(player1_mana,2,0);
           }
        if(power3==1 && player1_hp>10)
           {
            player1_hp-=10;
            player1_mana+=10;
            print_mana(player1_mana,2,0);
            print_hp(player1_hp,1,0);
           }
        if(atack1_left==1 && permission_basic_player1==0 && flag_player==0)
           {
            if(obs[player1_lin][player1_col-1]==2)
               {
			 permission_basic_player1=1;
                player1=SDL_LoadBMP("warrior1_on_grass_left.bmp");
			 player_hp-=10+player1_attack/10-player_block/10;
                //SDL_FreeSurface(player);
                print_hp(player_hp,1,COL_MAX+COL_START+2);
                /*player2=SDL_LoadBMP("hit_warrior_on_grass.bmp");
                apply_surface(player_col*40,player_lin*40,player,screen);*/
                SDL_Flip(screen);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack1_right==1 && permission_basic_player1==0 && flag_player==0)
           {
            if(obs[player1_lin][player1_col+1]==2)
               {
			    permission_basic_player1=1;
                player1=SDL_LoadBMP("warrior1_on_grass.bmp");
			    player_hp-=10+player1_attack/10-player_block/10;
                print_hp(player_hp,1,COL_MAX+COL_START+2);
                //SDL_FreeSurface(player);
                player2=SDL_LoadBMP("hit_warrior_on_grass.bmp");
                /*apply_surface(player_col*40,player_lin*40,player,screen);
                SDL_Flip(screen);*/
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player1_lin>1)
           {
            time_ex++;
            if(obs[player1_lin-1][player1_col]==0)
               {
                obs[player1_lin][player1_col]=0;
			    put_back(player1_lin,player1_col);
                player1_lin--;
                obs[player1_lin][player1_col]=3;
               }
           }
        if(down==1 && player1_lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player1_lin+1][player1_col]==0)
               {
                obs[player1_lin][player1_col]=0;
			    put_back(player1_lin,player1_col);
                player1_lin++;
                obs[player1_lin][player1_col]=3;
               }
           }
        if(left==1 && player1_col>1)
           {
            time_ex++;
            if(obs[player1_lin][player1_col-1]==0)
			{
			 obs[player1_lin][player1_col]=0;
			 put_back(player1_lin,player1_col);
                player1_col--;
                obs[player1_lin][player1_col]=3;
                player1=SDL_LoadBMP("warrior1_on_grass_left.bmp");
               }
           }
        if(right==1 && player1_col<LIN_MAX)
           {
            time_ex++;
            if(obs[player1_lin][player1_col+1]==0)
               {
                obs[player1_lin][player1_col]=0;
			 put_back(player1_lin,player1_col);
                player1_col++;
                obs[player1_lin][player1_col]=3;
                player1=SDL_LoadBMP("warrior1_on_grass.bmp");
               }
           }
        SDL_Delay(30);
        apply_surface((player1_col+COL_START)*40,player1_lin*40,player1,screen);
        SDL_Flip(screen);
        SDL_PumpEvents();
       }
 if(player_hp>player1_hp)
    {
     player1=SDL_LoadBMP("dead_warrior1_on_grass.bmp");
     apply_surface((player1_col+COL_START)*40,player1_lin*40,player1,screen);
     message=TTF_RenderText_Solid(font,"Player 2 wins!",textColor);
     player_money+=player_hp+player_mana+player1_money/50;
     player1_money+=player_money/75+20;
     player_xp+=100;
     player1_xp+=20;
    }
 else
    if(player_hp!=player1_hp)
       {
        player=SDL_LoadBMP("dead_warrior_on_grass.bmp");
        apply_surface((player_col+COL_START)*40,player_lin*40,player,screen);
        message=TTF_RenderText_Solid(font,"Player 1 wins!",textColor);
        player1_money+=player1_hp+player1_mana+player_money/50;
        player_money+=player1_money/75+20;
        player1_xp+=100;
        player_xp+=20;
       }
    else
       {
        player1=SDL_LoadBMP("dead_warrior1_on_grass.bmp");
        apply_surface((player1_col+COL_START)*40,player1_lin*40,player1,screen);
        player=SDL_LoadBMP("dead_warrior_on_grass.bmp");
        apply_surface((player_col+COL_START)*40,player_lin*40,player,screen);
	    message=TTF_RenderText_Solid(font,"Round draw!",textColor);
        int cash=(player_money+player1_money)/2/25;
        player1_money+=cash;
        player_money+=cash;
        player_xp+=50;
        player1_xp+=50;
       }
 save_player1("player1");
 save_player("player2");
 Mix_CloseAudio();
 Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
 sound=Mix_LoadWAV("win.wav");
 Mix_PlayChannel(-1,sound,0);
 apply_surface(((COL_MAX+COL_START)/2-1)*40,(LIN_MAX/2-1)*40,message,screen);
 SDL_Flip(screen);
 SDL_Delay(2000);
 TTF_CloseFont(font);
 SDL_Quit();
return 0;
}
