#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
//#include "PixelWorld.h"
#include<string>
#define COL_START 6
#define LIN_MAX 19
#define COL_MAX 19
#include<cstdio>
#define HP1 100
#include<ctime>
#include "alex.h"
/***
 NOTE: Player1 is really Player1
       Player is actually Player2
 TO DO LATER: A good way to make the code more simple is to make players objects...
 DONE!
***/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
Mix_Chunk *sound;
Mix_Music *music=NULL;
SDL_Color textColor={0,900,200}, color1={0,900,0},color2={450,0,0},color3{240,240,70};
TTF_Font *font=NULL;
SDL_Surface *message=NULL,*clear=NULL,*burn=NULL;
char pp,mute=0;
Uint8 *keystates=SDL_GetKeyState(NULL);
int time_ex,beg1,beg2,end1,end2,t,t1,t2,flag_player;
int power1,power2,power3,power4;
int up,down,right,left,atack_left,atack_right,atack1_left,atack1_right,mana_pot,hp_pot;
int v[LIN_MAX+3][COL_MAX+3],obs[LIN_MAX+3][COL_MAX+3];
SDL_Surface *image=NULL;
SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;
class player
{
 public:
 int hp,xp,mana,money,items[10][10],items_equipped[10];
 int attack,block,fire_res,fire_dmg,permission_basic,permission,skin_state;
 int lin,col;
 SDL_Surface *skin;
 public:
 void load_save(char *nume_salvare,int left_limit)
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
      fprintf(salvare,"0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
      fclose(salvare);
      salvare=fopen(nume_salvare1,"r");
     }
  fscanf(salvare,"%d %d",&money,&xp);
  for(int j=1;j<=5;j++)
     for(int i=1;i<=4;i++)
         {
		 fscanf(salvare,"%d",&items[i][j]);
         }
 for(int i=5;i<=5;i++)
     for(int j=1;j<=5;j++)
         fscanf(salvare,"%d ",&items[i][j]);
  if(items[1][4]==1)
     items_equipped[1]=4;
  else
     if(items[1][3]==1)
         items_equipped[1]=3;
     else
         if(items[1][2]==1)
             items_equipped[1]=2;
         else
             if(items[1][1]==1)
                 items_equipped[1]=1;
  if(items[2][4]==1)
     items_equipped[2]=4;
  else
     if(items[2][3]==1)
        items_equipped[2]=3;
     else
        if(items[2][2]==1)
            items_equipped[2]=2;
        else
           if(items[2][1]==1)
              items_equipped[2]=1;
  if(items[3][4]==1)
     items_equipped[3]=4;
  else
     if(items[3][3]==1)
         items_equipped[3]=3;
     else
         if(items[3][2]==1)
             items_equipped[3]=2;
         else
             if(items[3][1]==1)
                 items_equipped[3]=1;
  if(items[4][4]==1)
     items_equipped[4]=4;
  else
     if(items[4][3]==1)
         items_equipped[4]=3;
     else
         if(items[4][2]==1)
             items_equipped[4]=2;
         else
             if(items[4][1]==1)
                 items_equipped[4]=1;
  if(items[4][5]==1)
     items_equipped[5]=4;
  else
     if(items[3][5]==1)
         items_equipped[5]=3;
     else
         if(items[2][5]==1)
             items_equipped[5]=2;
         else
             if(items[1][5]==1)
                 items_equipped[5]=1;
  SDL_Surface *amulet=NULL,*hp_pot=NULL,*mana_pot=NULL,*helmet=NULL,*chestplate=NULL,*boots=NULL,*trousers=NULL,*sword=NULL;
  TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
  SDL_Color color2={255,294,10};
  if(items_equipped[1]==1)
     {
     block+=10;
     helmet=SDL_LoadBMP("lvl1_helmet.bmp");
    }
 if(items_equipped[2]==1)
    {
     block+=10;
     chestplate=SDL_LoadBMP("lvl1_chestplate.bmp");
    }
 if(items_equipped[3]==1)
    {
     block+=10;
     trousers=SDL_LoadBMP("lvl1_trousers.bmp");
    }
 if(items_equipped[4]==1)
    {
     block+=10;
     boots=SDL_LoadBMP("lvl1_boots.bmp");
    }
 if(items_equipped[5]==1)
    {
     attack+=10;
     sword=SDL_LoadBMP("lvl1_sword.bmp");
    }
 if(items_equipped[1]==2)
    {
     block+=14;
     fire_res+=3;
     helmet=SDL_LoadBMP("lvl2_helmet.bmp");
    }
 if(items_equipped[2]==2)
    {block+=14;
    fire_res+=3;
    chestplate=SDL_LoadBMP("lvl2_chestplate.bmp");
    }
 if(items_equipped[3]==2)
    {block+=14;
    fire_res+=3;
    trousers=SDL_LoadBMP("lvl2_trousers.bmp");
    }
 if(items_equipped[4]==2)
    {block+=14;
    fire_res+=3;
    boots=SDL_LoadBMP("lvl2_boots.bmp");
    }
 if(items_equipped[5]==2)
    {attack+=15;
    fire_dmg+=3;
    sword=SDL_LoadBMP("lvl2_sword.bmp");
    }
 if(items_equipped[1]==3)
    {block+=17;
    fire_res+=8;
    helmet=SDL_LoadBMP("lvl3_helmet.bmp");
    }
 if(items_equipped[2]==3)
    {block+=17;
    fire_res+=8;
    chestplate=SDL_LoadBMP("lvl3_chestplate.bmp");
    }
 if(items_equipped[3]==3)
    {block+=17;
    fire_res+=8;
    trousers=SDL_LoadBMP("lvl3_trousers.bmp");
    }
 if(items_equipped[4]==3)
    {block+=17;
    fire_res+=8;
    boots=SDL_LoadBMP("lvl3_boots.bmp");
    }
 if(items_equipped[5]==3)
    {attack+=17;
    fire_dmg+=7;
    sword=SDL_LoadBMP("lvl3_sword.bmp");
    }
 if(items_equipped[1]==4)
    {
     block+=20;
     fire_res+=14;
     helmet=SDL_LoadBMP("lvl4_helmet.bmp");
    }
 if(items_equipped[2]==4)
    {block+=20;
    fire_res+=14;
    chestplate=SDL_LoadBMP("lvl4_chestplate.bmp");
    }
 if(items_equipped[3]==4)
    {block+=20;
    fire_res+=14;
    trousers=SDL_LoadBMP("lvl4_trousers.bmp");
    }
 if(items_equipped[4]==4)
    {block+=20;
    fire_res+=14;
    boots=SDL_LoadBMP("lvl4_boots.bmp");
    }
 if(items_equipped[5]==4)
    {attack+=25;
    fire_dmg+=10;
    sword=SDL_LoadBMP("lvl4_sword.bmp");
    }
 if(items[5][1]>0)
    {
     hp_pot=SDL_LoadBMP("life_potion.bmp");
    }
 if(items[5][2]>0)
    {
     mana_pot=SDL_LoadBMP("mana_potion.bmp");
    }
 if(items[5][3]>0)
    {
	amulet=SDL_LoadBMP("amulet_of_greed.bmp");
     items_equipped[6]=1;
    }
 if(items[5][4]>0)
    {
    	amulet=SDL_LoadBMP("amulet_of_fire_res.bmp");
    	items_equipped[6]=2;
    }
 if(items[5][5]>0)
    {
    	amulet=SDL_LoadBMP("Devil's_Amulet.bmp");
     items_equipped[6]=3;
    }
 if(items_equipped[6]==2)
    {
    	fire_res+=fire_res*10/100+3;
    }
 else
    if(items_equipped[6]==3)
       {
        fire_dmg+=fire_dmg*30/100+3;
        attack+=attack*40/100+3;
       }
 if(amulet!=NULL)
    {
    	apply_surface(left_limit,200,amulet,screen);
    }
 if(hp_pot!=NULL)
    {
    	apply_surface(left_limit,120,hp_pot,screen);
     int a=items[5][1];
     int i=0,i1,j;
     if(a<0)
        a=0;
     char v[10]={0,0,0,0,0,0,0,0,0,0};
     char v1[10]={0,0,0,0,0,0,0,0,0,0};
     while(a!=0)
           {
            i++;
            v[i]=a%10+'0';
            a/=10;
           }
     for(i1=1,j=i;j>=1;i1++,j--)
         v1[i1]=v[j];
     if(i==0)
        {
         i++;
         v1[i]='0';
        }
     v1[0]='x';
     image=TTF_RenderText_Solid(font2,v1,color2);
     apply_surface(left_limit+50,120,image,screen);
    }
 if(mana_pot!=NULL)
    {
    	apply_surface(left_limit+80,120,mana_pot,screen);
     int a=items[5][2];
     int i=0,i1,j;
     if(a<0)
        a=0;
     char v[10]={0,0,0,0,0,0,0,0,0,0};
     char v1[10]={0,0,0,0,0,0,0,0,0,0};
     while(a!=0)
           {
            i++;
            v[i]=a%10+'0';
            a/=10;
           }
     for(i1=1,j=i;j>=1;i1++,j--)
         v1[i1]=v[j];
     if(i==0)
        {
         i++;
         v1[i]='0';
        }
     v1[0]='x';
     image=TTF_RenderText_Solid(font2,v1,color2);
     apply_surface(left_limit+130,120,image,screen);
    }
 if(helmet!=NULL)
    apply_surface(left_limit+20,280,helmet,screen);
 if(chestplate!=NULL)
    apply_surface(left_limit+20,360,chestplate,screen);
 if(trousers!=NULL)
    apply_surface(left_limit+20,440,trousers,screen);
 if(boots!=NULL)
    apply_surface(left_limit+20,520,boots,screen);
 if(sword!=NULL)
    apply_surface(left_limit+100,360,sword,screen);
 }
 void save(char *nume_salvare)
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
  fprintf(salvare,"%d\n%d\n",money,xp);
  for(int j=1;j<=5;j++)
      {
	   for(int i=1;i<=4;i++)
	       {
		    fprintf(salvare,"%d\n",items[i][j]);
	       }
       fprintf(salvare,"\n");
      }
  for(int j=1;j<=5;j++)
      for(int i=5;i<=5;i++)
          fprintf(salvare,"%d\n",items[i][j]);
 }
 void print_hp(int lin,int col)
 {
  int a=hp;
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
 void print_mana(int lin,int col)
 {
  int i=0,i1,j;
  int a=mana;
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
};
player player1,player2;
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
void get_burn(int i,int j)
{
 burn=SDL_LoadBMP("burn.bmp");
}
void welcome_message()
{
 SDL_Surface *message1=TTF_RenderText_Solid(font,"Welcome to Pixel World:Duel Mode! ",color2);
 apply_surface(280,160,message1,screen);
 SDL_FreeSurface(message1);
 SDL_Surface *message2=TTF_RenderText_Solid(font,"Code:Alex Cioltan and Stefan Enescu ",color2);
 apply_surface(280,200,message2,screen);
 SDL_Surface *message3=TTF_RenderText_Solid(font,"Graphics: Stefan Enescu,",color2);
 apply_surface(280,240,message3,screen);
 SDL_Surface *message4=TTF_RenderText_Solid(font,"Alex Cioltan, Victor Ionescu and",color2);
 apply_surface(280,280,message4,screen);
 message4=TTF_RenderText_Solid(font,"Duta Alexandru",color2);
 apply_surface(280,320,message4,screen);
 SDL_Flip(screen);
 while(getkey(VK_RETURN)==0);
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
 player1.hp=HP1;
 player2.hp=HP1,player2.mana=HP1,player1.mana=HP1;
 player1.lin=LIN_MAX/2,player1.col=COL_MAX/2-5,player2.lin=LIN_MAX/2,player2.col=COL_MAX/2+5;
 player1.money,player2.money,player2.xp,player1.xp;
 SDL_Init(SDL_INIT_EVERYTHING);
 //Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
 //screen=SDL_SetVideoMode((LIN_MAX+1)*40,(COL_MAX+1)*40,32,SDL_FULLSCREEN/*SDL_SWSURFACE*/);
 screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
 TTF_Init();
 font=TTF_OpenFont("font2.ttf",40);
 music=Mix_LoadMUS("bck.wav");
 clear=SDL_LoadBMP("wooden_background.bmp");
 apply_surface(0,0,clear,screen);
 if(mute==0)
    Mix_PlayMusic(music, -1 );
 load_level("a");
 print_level();
 //welcome_message();
 clear=SDL_LoadBMP("clear.bmp");
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
 player1.skin=SDL_LoadBMP("warrior1_on_grass.bmp");
 player2.skin=SDL_LoadBMP("warrior_on_grass.bmp");
 obs[player2.lin][player2.col]=2;
 obs[player1.lin][player1.col]=3;
 player2.print_hp(1,COL_MAX+COL_START+2);
 player1.print_hp(1,0);
 player2.print_mana(2,COL_MAX+COL_START+2);
 player1.print_mana(2,0);
 time_ex=0;
 if(mute<=1)
    sound=Mix_LoadWAV("hit.wav");
 print_level();
 int start_t=0;
 put_arena_wall();
 player1.load_save("player1",0);
 player2.load_save("player2",27*40);
 player1.skin_state=1;
 player2.skin_state=0;
 while(keystates[SDLK_ESCAPE]==NULL && player1.hp>0 && player2.hp>0)
       {
	   flag_player=0;
	   t=time(NULL);
        if(t-t1>=2)
           {
            start_t++;
            if(start_t>=4)
               {
			 clear_arena_wall();
               }
            t1=t;
            if(player2.mana<=99)
			{
			 player2.mana++;
			 player2.print_mana(2,COL_MAX+COL_START+2);
			}
		  if(player1.mana<=99)
			{
			 player1.mana++;
			 player1.print_mana(2,0);
			}
            //load_level("a");
            print_level();
            player2.permission=player1.permission=0;
           }
	   if(t-t2>=1)
		 {
          if(player1.skin_state==1)
              player1.skin=SDL_LoadBMP("warrior1_on_grass.bmp");
          else
              player1.skin=SDL_LoadBMP("warrior1_on_grass_left.bmp");
          if(player2.skin_state==1)
              player2.skin=SDL_LoadBMP("warrior_on_grass.bmp");
		  else
              player2.skin=SDL_LoadBMP("warrior_on_grass_left.bmp");
          t2=t;
		  player2.permission_basic=player1.permission_basic=0;
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
        mana_pot=keystates[SDLK_0];
        hp_pot=keystates[SDLK_9];
	   if(mana_pot==1 && player2.mana<100)
           {
            if(player2.items[5][2]>=1)
               {
                player2.items[5][2]--;
                player2.mana+=10;
                if(player2.mana>100)
                   player2.mana=100;
                player2.print_mana(2,27);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(130+27*40,120,clear,screen);
                int a=player2.items[5][2];
			 int i=0,i1,j;
			 if(a<0)
			    a=0;
			 char v[10]={0,0,0,0,0,0,0,0,0,0};
			 char v1[10]={0,0,0,0,0,0,0,0,0,0};
			 while(a!=0)
				  {
				   i++;
				   v[i]=a%10+'0';
				   a/=10;
				  }
			 for(i1=1,j=i;j>=1;i1++,j--)
				v1[i1]=v[j];
			 if(i==0)
			    {
				i++;
				v1[i]='0';
			    }
			 v1[0]='x';
			 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
			 SDL_Color color2={255,294,10};
			 image=TTF_RenderText_Solid(font2,v1,color2);
		      apply_surface(130+27*40,120,image,screen);
               }
           }
        if(hp_pot==1 && player2.hp<100)
           {
            if(player2.items[5][1]>=1)
               {
                player2.items[5][1]--;
                player2.hp+=10;
                if(player2.hp>100)
                   player2.hp=100;
                player2.print_hp(1,27);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(40+27*40,120,clear,screen);
                int a=player2.items[5][1];
			 int i=0,i1,j;
			 if(a<0)
			    a=0;
			 char v[10]={0,0,0,0,0,0,0,0,0,0};
			 char v1[10]={0,0,0,0,0,0,0,0,0,0};
			 while(a!=0)
				  {
				   i++;
				   v[i]=a%10+'0';
				   a/=10;
				  }
			 for(i1=1,j=i;j>=1;i1++,j--)
				v1[i1]=v[j];
			 if(i==0)
			    {
				i++;
				v1[i]='0';
			    }
			 v1[0]='x';
			 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
			 SDL_Color color2={255,294,10};
			 image=TTF_RenderText_Solid(font2,v1,color2);
		      apply_surface(50+27*40,120,image,screen);
               }
           }
        if(power1==1 && player2.mana>=10 && player2.hp<=90)
           {
            player2.mana-=10;
            player2.hp+=10;
            player2.print_mana(2,COL_MAX+COL_START+2);
            player2.print_hp(1,COL_MAX+COL_START+2);
           }
        if(power2==1 && player2.mana>=30 && player2.permission==0)
           {
            player2.mana-=30;
            player2.permission=1;
            if(max(player1.lin,player2.lin)-min(player1.lin,player2.lin)<=2 && max(player1.col,player2.col)-min(player1.col,player2.col)<=2)
               {
                player1.hp-=40+player2.fire_dmg*3/10-player1.fire_res*3/10;
                player1.print_hp(1,0);
               }
            if(player2.lin-2<=0)
               beg1=1;
            else
               beg1=player2.lin-2;
            if(player2.lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player2.lin+2;
            if(player2.col-2<=0)
               beg2=1;
            else
               beg2=player2.col-2;
            if(player2.col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player2.col+2;
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
            player2.print_mana(2,COL_MAX+COL_START+2);
           }
        if(power3==1 && player2.hp>10)
           {
            player2.hp-=10;
            player2.mana+=10;
            player2.print_mana(2,COL_MAX+COL_START+2);
            player2.print_hp(1,COL_MAX+COL_START+2);
           }
        if(atack_left==1 && player2.permission_basic==0)
           {
            player2.skin=SDL_LoadBMP("warrior_on_grass_left.bmp");
            player2.skin_state=0;
            if(obs[player2.lin][player2.col-1]==3)
               {
			 player2.permission_basic=1;
			 player1.hp-=10+player2.attack/10-player1.block/10;
			 player1.skin=SDL_LoadBMP("hit_warrior1_on_grass.bmp");
			 player1.skin_state=1;
			 apply_surface((player1.col+COL_START)*40,player1.lin*40,player1.skin,screen);
                player1.print_hp(1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack_right==1 && player2.permission_basic==0)
           {
            player2.skin=SDL_LoadBMP("warrior_on_grass.bmp");
            player2.skin_state=1;
            if(obs[player2.lin][player2.col+1]==3)
               {
			 player2.permission_basic=1;
			 player1.hp-=10+player2.attack/10-player1.block/10;
			 player1.skin=SDL_LoadBMP("hit_warrior1_on_grass_left.bmp");
			 player1.skin_state=0;
			 apply_surface((player1.col+COL_START)*40,player1.lin*40,player1.skin,screen);
                player1.print_hp(1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player2.lin>1)
           {
            time_ex++;
            if(obs[player2.lin-1][player2.col]==0)
               {
                obs[player2.lin][player2.col]=0;
			 put_back(player2.lin,player2.col);
                player2.lin--;
                obs[player2.lin][player2.col]=2;
               }
           }
        if(down==1 && player2.lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player2.lin+1][player2.col]==0)
               {
                obs[player2.lin][player2.col]=0;
			 put_back(player2.lin,player2.col);
                player2.lin++;
                obs[player2.lin][player2.col]=2;
               }
           }
        if(left==1 && player2.col>1)
           {
		  time_ex++;
            if(obs[player2.lin][player2.col-1]==0)
               {
                obs[player2.lin][player2.col]=0;
			 put_back(player2.lin,player2.col);
                player2.col--;
                obs[player2.lin][player2.col]=2;
                player2.skin=SDL_LoadBMP("warrior_on_grass_left.bmp");
                player2.skin_state=0;
               }
           }
        if(right==1 && player2.col<LIN_MAX)
           {
            time_ex++;
            if(obs[player2.lin][player2.col+1]==0)
               {
                obs[player2.lin][player2.col]=0;
			 put_back(player2.lin,player2.col);
                player2.col++;
                obs[player2.lin][player2.col]=2;
                player2.skin=SDL_LoadBMP("warrior_on_grass.bmp");
                player2.skin_state=1;
               }
           }
        apply_surface((player2.col+COL_START)*40,player2.lin*40,player2.skin,screen);
        up=keystates[SDLK_w];
        down=keystates[SDLK_s];
        right=keystates[SDLK_d];
        left=keystates[SDLK_a];
        power1=keystates[SDLK_1];
        power2=keystates[SDLK_2];
        power3=keystates[SDLK_3];
        power4=keystates[SDLK_4];
        mana_pot=keystates[SDLK_F2];
        hp_pot=keystates[SDLK_F1];
        if(mana_pot==1 && player1.mana<100)
           {
            if(player1.items[5][2]>=1)
               {
                player1.items[5][2]--;
                player1.mana+=10;
                if(player1.mana>100)
                   player1.mana=100;
                player1.print_mana(2,0);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(130,120,clear,screen);
                int a=player1.items[5][2];
			 int i=0,i1,j;
			 if(a<0)
			    a=0;
			 char v[10]={0,0,0,0,0,0,0,0,0,0};
			 char v1[10]={0,0,0,0,0,0,0,0,0,0};
			 while(a!=0)
				  {
				   i++;
				   v[i]=a%10+'0';
				   a/=10;
				  }
			 for(i1=1,j=i;j>=1;i1++,j--)
				v1[i1]=v[j];
			 if(i==0)
			    {
				i++;
				v1[i]='0';
			    }
			 v1[0]='x';
			 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
			 SDL_Color color2={255,294,10};
			 image=TTF_RenderText_Solid(font2,v1,color2);
		      apply_surface(130,120,image,screen);
               }
           }
        if(hp_pot==1 && player1.hp<100)
           {
            if(player1.items[5][1]>=1)
               {
                player1.items[5][1]--;
                player1.hp+=10;
                if(player1.hp>100)
                   player1.hp=100;
                player1.print_hp(1,0);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(40,120,clear,screen);
                int a=player1.items[5][1];
			 int i=0,i1,j;
			 if(a<0)
			    a=0;
			 char v[10]={0,0,0,0,0,0,0,0,0,0};
			 char v1[10]={0,0,0,0,0,0,0,0,0,0};
			 while(a!=0)
				  {
				   i++;
				   v[i]=a%10+'0';
				   a/=10;
				  }
			 for(i1=1,j=i;j>=1;i1++,j--)
				v1[i1]=v[j];
			 if(i==0)
			    {
				i++;
				v1[i]='0';
			    }
			 v1[0]='x';
			 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
			 SDL_Color color2={255,294,10};
			 image=TTF_RenderText_Solid(font2,v1,color2);
		      apply_surface(50,120,image,screen);
               }
           }
        if(power1==1 && player1.mana>=10 && player1.hp<=90)
           {
            player1.mana-=10;
            player1.hp+=10;
            player1.print_mana(2,0);
            player1.print_hp(1,0);
           }
        if(power2==1 && player1.mana>=30 && player1.permission==0)
           {
            player1.mana-=30;
            player1.permission=1;
            if(max(player2.lin,player1.lin)-min(player1.lin,player2.lin)<=2 && max(player1.col,player2.col)-min(player1.col,player2.col)<=2)
               {
                player2.hp-=40+player1.fire_dmg*3/10-player2.fire_res*3/10;
                player2.print_hp(1,COL_MAX+COL_START+2);
               }
            if(player1.lin-2<=0)
               beg1=1;
            else
               beg1=player1.lin-2;
            if(player1.lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player1.lin+2;
            if(player1.col-2<=0)
               beg2=1;
            else
               beg2=player1.col-2;
            if(player1.col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player1.col+2;
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
            player1.print_mana(2,0);
           }
        if(power3==1 && player1.hp>10)
           {
            player1.hp-=10;
            player1.mana+=10;
            player1.print_mana(2,0);
            player1.print_hp(1,0);
           }
        if(atack1_left==1 && player1.permission_basic==0 && flag_player==0)
           {
            if(obs[player1.lin][player1.col-1]==2)
               {
			 player1.permission_basic=1;
                player1.skin=SDL_LoadBMP("warrior1_on_grass_left.bmp");
                player1.skin_state=0;
			 player2.hp-=10+player1.attack/10-player2.block/10;
                //SDL_FreeSurface(player);
                player2.print_hp(1,COL_MAX+COL_START+2);
                player2.skin=SDL_LoadBMP("hit_warrior_on_grass.bmp");
                player2.skin_state=1;
                apply_surface((player2.col+COL_START)*40,player2.lin*40,player2.skin,screen);
                SDL_Flip(screen);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack1_right==1 && player1.permission_basic==0 && flag_player==0)
           {
            if(obs[player1.lin][player1.col+1]==2)
               {
			    player1.permission_basic=1;
                player1.skin=SDL_LoadBMP("warrior1_on_grass.bmp");
                player1.skin_state=1;
			    player2.hp-=10+player1.attack/10-player2.block/10;
                player2.print_hp(1,COL_MAX+COL_START+2);
                //SDL_FreeSurface(player);
                player2.skin=SDL_LoadBMP("hit_warrior_on_grass_left.bmp");
                player2.skin_state=0;
                apply_surface((player2.col+COL_START)*40,player2.lin*40,player2.skin,screen);
                SDL_Flip(screen);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player1.lin>1)
           {
            time_ex++;
            if(obs[player1.lin-1][player1.col]==0)
               {
                obs[player1.lin][player1.col]=0;
			    put_back(player1.lin,player1.col);
                player1.lin--;
                obs[player1.lin][player1.col]=3;
               }
           }
        if(down==1 && player1.lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player1.lin+1][player1.col]==0)
               {
                obs[player1.lin][player1.col]=0;
			    put_back(player1.lin,player1.col);
                player1.lin++;
                obs[player1.lin][player1.col]=3;
               }
           }
        if(left==1 && player1.col>1)
           {
            time_ex++;
            if(obs[player1.lin][player1.col-1]==0)
			{
			 obs[player1.lin][player1.col]=0;
			 put_back(player1.lin,player1.col);
                player1.col--;
                obs[player1.lin][player1.col]=3;
                player1.skin=SDL_LoadBMP("warrior1_on_grass_left.bmp");
                player1.skin_state=0;
               }
           }
        if(right==1 && player1.col<LIN_MAX)
           {
            time_ex++;
            if(obs[player1.lin][player1.col+1]==0)
               {
                obs[player1.lin][player1.col]=0;
			 put_back(player1.lin,player1.col);
                player1.col++;
                obs[player1.lin][player1.col]=3;
                player1.skin=SDL_LoadBMP("warrior1_on_grass.bmp");
                player1.skin_state=1;
                }
           }
        SDL_Delay(50);
        apply_surface((player1.col+COL_START)*40,player1.lin*40,player1.skin,screen);
        SDL_Flip(screen);
        SDL_PumpEvents();
       }
 if(player2.hp>player1.hp)
    {
     player1.skin=SDL_LoadBMP("dead_warrior1_on_grass.bmp");
     apply_surface((player1.col+COL_START)*40,player1.lin*40,player1.skin,screen);
     message=TTF_RenderText_Solid(font,"Player 2 wins!",textColor);
     player2.money+=player2.hp+player2.mana+player1.money/50;
     player1.money+=player2.money/75+20;
     int x1=player1.money,x2=player2.money;
     if(player1.items_equipped[6]==1)
        player1.money+=player2.money/75;
     if(player2.items_equipped[6]==1)
        player2.money+=x1/75;
     player2.xp+=100;
     player1.xp+=20;
    }
 else
    if(player2.hp!=player1.hp)
       {
        player2.skin=SDL_LoadBMP("dead_warrior_on_grass.bmp");
        apply_surface((player2.col+COL_START)*40,player2.lin*40,player2.skin,screen);
        message=TTF_RenderText_Solid(font,"Player 1 wins!",textColor);
        player1.money+=player1.hp+player1.mana+player2.money/50;
        player2.money+=player1.money/75+20;
        int x1=player1.money,x2=player2.money;
        if(player1.items_equipped[6]==1)
           player1.money+=player2.money/75;
	   if(player2.items_equipped[6]==1)
		 player2.money+=x1/75;
        player1.xp+=100;
        player2.xp+=20;
       }
    else
       {
        player1.skin=SDL_LoadBMP("dead_warrior1_on_grass.bmp");
        apply_surface((player1.col+COL_START)*40,player1.lin*40,player1.skin,screen);
        player2.skin=SDL_LoadBMP("dead_warrior_on_grass.bmp");
        apply_surface((player2.col+COL_START)*40,player2.lin*40,player2.skin,screen);
	   message=TTF_RenderText_Solid(font,"Round draw!",textColor);
        int cash=(player2.money+player1.money)/2/25;
        player1.money+=cash;
        player2.money+=cash;
        int x1=player1.money,x2=player2.money;
        if(player1.items_equipped[6]==1)
           player1.money+=player2.money/75;
        if(player2.items_equipped[6]==1)
           player2.money+=x1/75;
        player2.xp+=50;
        player1.xp+=50;
       }
 player1.save("player1");
 player2.save("player2");
 Mix_CloseAudio();
 //Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
 sound=Mix_LoadWAV("win.wav");
 Mix_PlayChannel(-1,sound,0);
 apply_surface(((COL_MAX+COL_START)/2-1)*40,(LIN_MAX/2-1)*40,message,screen);
 SDL_Flip(screen);
 SDL_Delay(2000);
 TTF_CloseFont(font);
 SDL_Quit();
return 0;
}
