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
int modul(int a)
{
 if(a<0)
    return a*(-1);
 else
    return a;
}
Mix_Chunk *sound;
char level[100]={'b'};
Mix_Music *music=NULL;
SDL_Color textColor={0,900,200}, color1={0,900,0},color2={450,0,0},color3{240,240,70};
TTF_Font *font=NULL;
SDL_Surface *message=NULL,*clear=NULL,*burn=NULL;
char pp,mute=1;
int computer=0,difficulty=1;
Uint8 *keystates=SDL_GetKeyState(NULL);
int time_ex,beg1,beg2,end1,end2,t,t1,t2,flag_player;
int power1,power2,power3,power4;
int up,down,right,left,atack_left,atack_right,atack1_left,atack1_right,mana_pot,hp_pot;
int map[LIN_MAX+3][COL_MAX+3],obs[LIN_MAX+3][COL_MAX+3];
SDL_Surface *image=NULL;
SDL_Surface *screen=NULL;
SDL_Surface *background=NULL;
class player
{
 public:
 int hp,xp,mana,money,items[10][10],items_equipped[10];
 int attack,block,fire_res,fire_dmg,permission_basic,permission,skin_state;
 int lin,col;
 char prefix[100];
 SDL_Surface *default_left_skin,*default_right_skin,*default_hit_skin_left,*default_hit_skin_right,*default_dead_skin;
 SDL_Surface *skin;
 public:
 void get_skin(char *prefix)
 {
  char v[1000];
  memset(v,0,1000);
  int x=strlen(v);
  int y=strlen(prefix)-1;
  for(int i=x;i<=x+y;i++)
      v[i]=prefix[i-x];
  x+=y;
  v[x+1]='_';
  v[x+2]='o';
  v[x+3]='n';
  v[x+4]='_';
  x+=4;
  switch(map[lin][col])
	    {
		case 2:
			  {
			   v[x+1]='g';
			   v[x+2]='r';
			   v[x+3]='a';
			   v[x+4]=v[x+5]='s';
			   x+=5;
			   break;
			  }
		case 3:
			  {
			   v[x+1]='b';
			   v[x+2]='r';
			   v[x+3]='i';
			   v[x+4]='c';
			   v[x+5]='k';
			   v[x+6]='s';
			   x+=6;
			   break;
			  }
          case 9:
                 {
			   v[x+1]='o';
			   v[x+2]='p';
			   v[x+3]='e';
			   v[x+4]='n';
			   v[x+5]='e';
			   v[x+6]='d';
			   v[x+7]='_';
			   v[x+8]='c';
			   v[x+9]='i';
			   v[x+10]='t';
			   v[x+11]='y';
			   v[x+12]='_';
			   v[x+13]='d';
			   v[x+14]='o';
			   v[x+15]='o';
			   v[x+16]='r';
			   x+=16;
			   break;
			  }
		case 10:
		        {
		        v[x+1]='b';
			   v[x+2]='l';
			   v[x+3]='u';
			   v[x+4]='e';
			   v[x+5]='_';
			   v[x+6]='d';
			   v[x+7]='u';
			   v[x+8]='n';
			   v[x+9]='g';
			   v[x+10]='e';
			   v[x+11]='o';
			   v[x+12]='n';
			   v[x+13]='_';
			   v[x+14]='f';
			   v[x+15]='l';
			   v[x+16]='o';
			   v[x+17]='o';
			   v[x+18]='r';
			   x+=18;
			    break;
			   }
		case 12:
		        {
		        v[x+1]='g';
			   v[x+2]='r';
			   v[x+3]='e';
			   v[x+4]='e';
			   v[x+5]='n';
			   v[x+6]='_';
			   v[x+7]='d';
			   v[x+8]='u';
			   v[x+9]='n';
			   v[x+10]='g';
			   v[x+11]='e';
			   v[x+12]='o';
			   v[x+13]='n';
			   v[x+14]='_';
			   v[x+15]='f';
			   v[x+16]='l';
			   v[x+17]='o';
			   v[x+18]='o';
			   v[x+19]='r';
			   x+=19;
			    break;
			   }
		case 14:
		        {
		        v[x+1]='r';
			   v[x+2]='e';
			   v[x+3]='d';
			   v[x+4]='_';
			   v[x+5]='d';
			   v[x+6]='u';
			   v[x+7]='n';
			   v[x+8]='g';
			   v[x+9]='e';
			   v[x+10]='o';
			   v[x+11]='n';
			   v[x+12]='_';
			   v[x+13]='f';
			   v[x+14]='l';
			   v[x+15]='o';
			   v[x+16]='o';
			   v[x+17]='r';
			   x+=17;
			    break;
			   }
	    }
  v[x+1]='.';
  v[x+2]='b';
  v[x+3]='m';
  v[x+4]='p';
  x+=4;
  FILE *file=fopen(v,"r");
  default_right_skin=SDL_LoadBMP(v);
  char v1[1000];
  memset(v1,0,1000);
  int x1=strlen(v1);
  int y1=strlen(prefix)-1;
  for(int i=x1;i<=x1+y1;i++)
      v1[i]=prefix[i-x1];
  x1+=y1;
  v1[x1+1]='_';
  v1[x1+2]='o';
  v1[x1+3]='n';
  v1[x1+4]='_';
  x1+=4;
  switch(map[lin][col])
	    {
		case 2:
			  {
			   v1[x1+1]='g';
			   v1[x1+2]='r';
			   v1[x1+3]='a';
			   v1[x1+4]=v1[x1+5]='s';
			   x1+=5;
			   break;
			  }
		case 3:
			  {
			   v1[x1+1]='b';
			   v1[x1+2]='r';
			   v1[x1+3]='i';
			   v1[x1+4]='c';
			   v1[x1+5]='k';
			   v1[x1+6]='s';
			   x1+=6;
			   break;
			  }
		case 9:
                 {
			   v1[x1+1]='o';
			   v1[x1+2]='p';
			   v1[x1+3]='e';
			   v1[x1+4]='n';
			   v1[x1+5]='e';
			   v1[x1+6]='d';
			   v1[x1+7]='_';
			   v1[x1+8]='c';
			   v1[x1+9]='i';
			   v1[x1+10]='t';
			   v1[x1+11]='y';
			   v1[x1+12]='_';
			   v1[x1+13]='d';
			   v1[x1+14]='o';
			   v1[x1+15]='o';
			   v1[x1+16]='r';
			   x1+=16;
			   break;
			  }
		case 10:
		        {
		        v1[x1+1]='b';
			   v1[x1+2]='l';
			   v1[x1+3]='u';
			   v1[x1+4]='e';
			   v1[x1+5]='_';
			   v1[x1+6]='d';
			   v1[x1+7]='u';
			   v1[x1+8]='n';
			   v1[x1+9]='g';
			   v1[x1+10]='e';
			   v1[x1+11]='o';
			   v1[x1+12]='n';
			   v1[x1+13]='_';
			   v1[x1+14]='f';
			   v1[x1+15]='l';
			   v1[x1+16]='o';
			   v1[x1+17]='o';
			   v1[x1+18]='r';
			   x1+=18;
			    break;
			   }
	     case 12:
		        {
		        v1[x1+1]='g';
			   v1[x1+2]='r';
			   v1[x1+3]='e';
			   v1[x1+4]='e';
			   v1[x1+5]='n';
			   v1[x1+6]='_';
			   v1[x1+7]='d';
			   v1[x1+8]='u';
			   v1[x1+9]='n';
			   v1[x1+10]='g';
			   v1[x1+11]='e';
			   v1[x1+12]='o';
			   v1[x1+13]='n';
			   v1[x1+14]='_';
			   v1[x1+15]='f';
			   v1[x1+16]='l';
			   v1[x1+17]='o';
			   v1[x1+18]='o';
			   v1[x1+19]='r';
			   x1+=19;
			    break;
			   }
		case 14:
		        {
		        v1[x1+1]='r';
			   v1[x1+2]='e';
			   v1[x1+3]='d';
			   v1[x1+4]='_';
			   v1[x1+5]='d';
			   v1[x1+6]='u';
			   v1[x1+7]='n';
			   v1[x1+8]='g';
			   v1[x1+9]='e';
			   v1[x1+10]='o';
			   v1[x1+11]='n';
			   v1[x1+12]='_';
			   v1[x1+13]='f';
			   v1[x1+14]='l';
			   v1[x1+15]='o';
			   v1[x1+16]='o';
			   v1[x1+17]='r';
			   x1+=17;
			    break;
			   }
	    }
  v1[x1+1]='_';
  v1[x1+2]='l';
  v1[x1+3]='e';
  v1[x1+4]='f';
  v1[x1+5]='t';
  x1+=5;
  v1[x1+1]='.';
  v1[x1+2]='b';
  v1[x1+3]='m';
  v1[x1+4]='p';
  x1+=4;
  file=fopen(v1,"r");
  default_left_skin=SDL_LoadBMP(v1);
  memset(v1,0,1000);
  v1[0]='h';
  v1[1]='i';
  v1[2]='t';
  v1[3]='_';
  x1=strlen(v1);
  y1=strlen(prefix)-1;
  for(int i=x1;i<=x1+y1;i++)
      v1[i]=prefix[i-x1];
  x1=strlen(v1)-1;
  v1[x1+1]='_';
  v1[x1+2]='l';
  v1[x1+3]='e';
  v1[x1+4]='f';
  v1[x1+5]='t';
  x1+=5;
  v1[x1+1]='.';
  v1[x1+2]='b';
  v1[x1+3]='m';
  v1[x1+4]='p';
  x1+=4;
  default_hit_skin_left=SDL_LoadBMP(v1);
  memset(v1,0,1000);
  v1[0]='h';
  v1[1]='i';
  v1[2]='t';
  v1[3]='_';
  x1=strlen(v1);
  y1=strlen(prefix)-1;
  for(int i=x1;i<=x1+y1;i++)
      v1[i]=prefix[i-x1];
  x1=strlen(v1)-1;
  v1[x1+1]='.';
  v1[x1+2]='b';
  v1[x1+3]='m';
  v1[x1+4]='p';
  x1+=4;
  default_hit_skin_right=SDL_LoadBMP(v1);
  memset(v1,0,1000);
  v1[0]='d';
  v1[1]='e';
  v1[2]='a';
  v1[3]='d';
  v1[4]='_';
  x1=strlen(v1);
  y1=strlen(prefix)-1;
  for(int i=x1;i<=x1+y1;i++)
      v1[i]=prefix[i-x1];
  x1=strlen(v1)-1;
  v1[x1+1]='.';
  v1[x1+2]='b';
  v1[x1+3]='m';
  v1[x1+4]='p';
  x1+=4;
  default_dead_skin=SDL_LoadBMP(v1);
 }
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
        fire_dmg+=fire_dmg*50/100+3;
        attack+=attack*50/100+3;
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
     apply_surface(left_limit+20,120,image,screen);
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
     apply_surface(left_limit+100,120,image,screen);
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
player player[5];
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
 switch(map[l][c])
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
	    case 4:  {image=SDL_LoadBMP("fire.bmp");  break;}
           case 5:  {image=SDL_LoadBMP("bricks.bmp");
                     break;}
           case 6: {
           	     image=SDL_LoadBMP("city_wall.bmp");
           	     break;
                   }
           case 7:  {image=SDL_LoadBMP("water.bmp");break;}
           case 8:  {image=SDL_LoadBMP("closed_city_door.bmp"); break;}
           case 9:  {image=SDL_LoadBMP("opened_city_door.bmp"); break;}
           case 10: {image=SDL_LoadBMP("dungeon_blue_floor.bmp"); break;}
	      case 11: {image=SDL_LoadBMP("dungeon_blue_wall.bmp"); break;}
           case 12: {image=SDL_LoadBMP("dungeon_green_floor.bmp"); break;}
           case 13: {image=SDL_LoadBMP("dungeon_green_wall.bmp"); break;}
           case 14: {image=SDL_LoadBMP("dungeon_red_floor.bmp"); break;}
           case 15: {image=SDL_LoadBMP("dungeon_red_wall.bmp"); break;}
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
         fscanf(fin,"%d ",&map[i][j]);
fclose(fin);
}
void print_level()
{
 int i,j,i1=1,j1=1;
 for(i=0,i1=0;i1<=LIN_MAX;i+=40,i1++)
     for(j=0,j1=0;j1<=COL_MAX;j+=40,j1++)
         {
         	if(obs[i1][j1]<=1){
          switch(map[i1][j1])
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
           case 6: {
           	     image=SDL_LoadBMP("city_wall.bmp");
           	     obs[i1][j1]=1;
           	     break;
                   }
           case 7:  {image=SDL_LoadBMP("water.bmp"); obs[i1][j1]=1; break;}
           case 8:  {image=SDL_LoadBMP("closed_city_door.bmp"); obs[i1][j1]=1; break;}
           case 9:  {image=SDL_LoadBMP("opened_city_door.bmp"); break;}
           case 10: {image=SDL_LoadBMP("dungeon_blue_floor.bmp"); break;}
           case 11: {image=SDL_LoadBMP("dungeon_blue_wall.bmp"); obs[i1][j1]=1; break;}
           case 12: {image=SDL_LoadBMP("dungeon_green_floor.bmp"); break;}
           case 13: {image=SDL_LoadBMP("dungeon_green_wall.bmp"); obs[i1][j1]=1; break;}
           case 14: {image=SDL_LoadBMP("dungeon_red_floor.bmp"); break;}
           case 15: {image=SDL_LoadBMP("dungeon_red_wall.bmp"); obs[i1][j1]=1; break;}
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
 while(keystates[SDLK_RETURN]==0);
}
void put_arena_wall()
{
 for(int i=0;i<=LIN_MAX;i++)
	{
	 map[i][COL_MAX/2]=5;
	}
}
void clear_arena_wall()
{
 for(int i=0;i<=LIN_MAX;i++)
	{
	 map[i][COL_MAX/2]=2;
	 obs[i][COL_MAX/2]=0;
	}
 load_level(level);
}
void player_menu()
{
 SDL_Surface *bck=NULL,*image[5][5];
 image[1][1]=TTF_RenderText_Solid(font,"Player1 vs Computer",color1);
 image[1][2]=TTF_RenderText_Solid(font,"> Player1 vs Computer",color2);
 image[2][1]=TTF_RenderText_Solid(font,"Computer vs Player2 ",color1);
 image[2][2]=TTF_RenderText_Solid(font,"> Computer vs Player2",color2);
 int N=2;
 int poz;
 clear=SDL_LoadBMP("launcher_clear.bmp");
 background=SDL_LoadBMP("wooden_background.bmp");
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
		  apply_surface(450,680-80*(N-poz),clear,screen);
		  apply_surface(450,680-80*(N-poz),image[poz][1],screen);
		  poz--;
		  apply_surface(450,520+80*(poz-1),clear,screen);
		  apply_surface(450,520+80*(poz-1),image[poz][2],screen);
		 }
	   if(down==1 && poz<N)
	      {
		  apply_surface(450,520+80*(poz-1),clear,screen);
		  apply_surface(450,520+80*(poz-1),image[poz][1],screen);
		  poz++;
		  apply_surface(450,680-80*(N-poz),clear,screen);
		  apply_surface(450,680-80*(N-poz),image[poz][2],screen);
		 }
	   SDL_Delay(100);
	   SDL_Flip(screen);
	  }
}
void computer_move_player(int difficulty,int pl)
{
 int other_player=1;
 if(pl==1)
    other_player=2;
 switch(difficulty)
        {
         case 1:
                {
                 if(player[pl].hp>20)
                    {
                     if(player[other_player].lin<player[pl].lin)
                        up=1;
                     if(player[other_player].lin>player[pl].lin)
                        down=1;
                     if(player[other_player].col>player[pl].col)
                        right=1;
                     if(player[other_player].col<player[pl].col)
                         left=1;
                    }
                 else
                    {
                     if(player[pl].lin<player[other_player].lin)
                        down=1;
                     if(player[pl].lin>player[other_player].lin)
                        up=1;
                     if(player[pl].col>player[other_player].col)
                        left=1;
                     if(player[pl].col<player[other_player].col)
                        down=1;
                    }
                 if(obs[player[pl].lin][player[pl].col+1]==2 || obs[player[pl].lin][player[pl].col-1]==2)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=1;
                     else
                        atack_left=atack_right=1;
                    }
                 int x=rand()%3;
                 if(x==0)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=0;
                     else
                        atack_left=atack_right=1;
                    }
                 int y=rand()%2;
                 if(y==0)
                    up=down=left=right=0;
                 power2=0;
                 power1=power3=0;
                 break;
                }
         case 2:
                {
                 if(player[pl].hp>20)
                    {
                     if(player[other_player].lin<player[pl].lin)
                        up=1;
                     if(player[other_player].lin>player[pl].lin)
                        down=1;
                     if(player[other_player].col>player[pl].col)
                        right=1;
                     if(player[other_player].col<player[pl].col)
                         left=1;
                    }
                 else
                    {
                     if(player[pl].lin<player[other_player].lin)
                        down=1;
                     if(player[pl].lin>player[other_player].lin)
                        up=1;
                     if(player[pl].col>player[other_player].col)
                        left=1;
                     if(player[pl].col<player[other_player].col)
                        down=1;
                    }
                 if(obs[player[pl].lin][player[pl].col+1]==2 || obs[player[pl].lin][player[pl].col-1]==2)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=1;
                     else
                        atack_left=atack_right=1;
                    }
                 int x=rand()%3;
                 if(x==0)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=0;
                     else
                        atack_left=atack_right=1;
                    }
                 break;
                }
         case 3:
                {
                 if(player[pl].hp>20)
                    {
                     if(player[other_player].lin<player[pl].lin)
                        up=1;
                     if(player[other_player].lin>player[pl].lin)
                        down=1;
                     if(player[other_player].col>player[pl].col)
                        right=1;
                     if(player[other_player].col<player[pl].col)
                         left=1;
                    }
                 else
                    {
                     if(player[pl].lin<player[other_player].lin)
                        down=1;
                     if(player[pl].lin>player[other_player].lin)
                        up=1;
                     if(player[pl].col>player[other_player].col)
                        left=1;
                     if(player[pl].col<player[other_player].col)
                        down=1;
                    }
                 if(obs[player[pl].lin][player[pl].col+1]==2 || obs[player[pl].lin][player[pl].col-1]==2)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=1;
                     else
                        atack_left=atack_right=1;
                     power2=1;
                    }
                 power1=power3=0;
                 break;
                }
         case 4:
                {
                 if(player[pl].hp>20)
                    {
                     if(player[other_player].lin<player[pl].lin)
                        up=1;
                     if(player[other_player].lin>player[pl].lin)
                        down=1;
                     if(player[other_player].col>player[pl].col)
                        right=1;
                     if(player[other_player].col<player[pl].col)
                         left=1;
                    }
                 else
                    {
                     if(player[pl].lin<player[other_player].lin)
                        down=1;
                     if(player[pl].lin>player[other_player].lin)
                        up=1;
                     if(player[pl].col>player[other_player].col)
                        left=1;
                     if(player[pl].col<player[other_player].col)
                        down=1;
                    }
                 if(obs[player[pl].lin][player[pl].col+1]==2 || obs[player[pl].lin][player[pl].col-1]==2)
                    {
                     if(pl==1)
                        atack1_left=atack1_right=1;
                     else
                        atack_left=atack_right=1;
                    }
                 if(modul(player[other_player].lin-player[pl].lin)<=2 && modul(player[other_player].col-player[pl].col)<=2)
                    {
                     power2=1;
                    }
                 power1=power3=0;
                 break;
                }
        }
}
int main( int argc, char* args[] )
{
 //player_menu();
 player[1].hp=HP1;
 player[2].hp=HP1,player[2].mana=HP1,player[1].mana=HP1;
 player[1].lin=LIN_MAX/2,player[1].col=COL_MAX/2-5,player[2].lin=LIN_MAX/2,player[2].col=COL_MAX/2+5;
 player[1].money,player[2].money,player[2].xp,player[1].xp;
 SDL_Init(SDL_INIT_EVERYTHING);
 Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
 //screen=SDL_SetVideoMode((LIN_MAX+1)*40,(COL_MAX+1)*40,32,SDL_FULLSCREEN/*SDL_SWSURFACE*/);
 screen=SDL_SetVideoMode(0,0,32,SDL_HWSURFACE);
 TTF_Init();
 font=TTF_OpenFont("font2.ttf",40);
 music=Mix_LoadMUS("bck.wav");
 clear=SDL_LoadBMP("wooden_background.bmp");
 apply_surface(0,0,clear,screen);
 if(mute==0)
    Mix_PlayMusic(music, -1 );
 load_level(level);
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
 player[1].default_left_skin=SDL_LoadBMP("warrior1_on_grass_left.bmp");
 player[1].default_right_skin=SDL_LoadBMP("warrior1_on_grass.bmp");
 player[1].skin=SDL_LoadBMP("warrior1_on_grass.bmp");
 player[2].default_left_skin=SDL_LoadBMP("warrior_on_grass_left.bmp");
 player[2].default_right_skin=SDL_LoadBMP("warrior_on_grass.bmp");
 player[2].skin=SDL_LoadBMP("warrior_on_grass.bmp");
 obs[player[2].lin][player[2].col]=2;
 obs[player[1].lin][player[1].col]=3;
 player[2].print_hp(1,COL_MAX+COL_START+2);
 player[1].print_hp(1,0);
 player[2].print_mana(2,COL_MAX+COL_START+2);
 player[1].print_mana(2,0);
 time_ex=0;
 if(mute<=1)
    sound=Mix_LoadWAV("hit.wav");
 print_level();
 int start_t=0;
 put_arena_wall();
 player[1].load_save("player1",0);
 player[2].load_save("player2",27*40);
 player[1].prefix[0]='w';
 player[1].prefix[1]='a';
 player[1].prefix[2]='r';
 player[1].prefix[3]='r';
 player[1].prefix[4]='i';
 player[1].prefix[5]='o';
 player[1].prefix[6]='r';
 player[1].prefix[7]='1';

 player[2].prefix[0]='w';
 player[2].prefix[1]='a';
 player[2].prefix[2]='r';
 player[2].prefix[3]='r';
 player[2].prefix[4]='i';
 player[2].prefix[5]='o';
 player[2].prefix[6]='r';
 player[1].skin_state=1;
 player[2].skin_state=0;
 while(keystates[SDLK_ESCAPE]==NULL && player[1].hp>0 && player[2].hp>0)
       {
        obs[player[1].lin][player[1].col]=3;
        obs[player[2].lin][player[2].col]=2;
	   flag_player=0;
	   t=time(NULL);
        if(t-t1>=2)
           {
            start_t++;
            if(start_t>=3)
               {
			 clear_arena_wall();
               }
            t1=t;
            if(player[2].mana<=99)
			{
			 player[2].mana++;
			 player[2].print_mana(2,COL_MAX+COL_START+2);
			}
		  if(player[1].mana<=99)
			{
			 player[1].mana++;
			 player[1].print_mana(2,0);
			}
            //load_level("a");
            print_level();
            player[2].permission=player[1].permission=0;
           }
	   if(t-t2>=1)
		 {
            player[1].get_skin(player[1].prefix);
            player[2].get_skin(player[2].prefix);
            if(player[1].skin_state==1)
               {
			 player[1].skin=player[1].default_right_skin;
               }
            else
               {
			 player[1].skin=player[1].default_left_skin;
               }
            if(player[2].skin_state==1)
               {
			 player[2].skin=player[2].default_right_skin;
               }
		  else
               {
			 player[2].skin=player[2].default_left_skin;
               }
            t2=t;
		  player[2].permission_basic=player[1].permission_basic=0;
		 }
        if(computer!=1)
	      {
	       atack1_left=keystates[SDLK_z];
            atack1_right=keystates[SDLK_z];
	      }
	   if(computer!=2)
           {
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
            mana_pot=keystates[SDLK_0];
            hp_pot=keystates[SDLK_9];
           }
        else
           computer_move_player(difficulty,2);
	   if(mana_pot==1 && player[2].mana<100)
           {
            if(player[2].items[5][2]>=1)
               {
                player[2].items[5][2]--;
                player[2].mana+=10;
                if(player[2].mana>100)
                   player[2].mana=100;
                player[2].print_mana(2,27);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(80+27*40,120,clear,screen);
                int a=player[2].items[5][2];
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
		      apply_surface(100+27*40,120,image,screen);
               }
           }
        if(hp_pot==1 && player[2].hp<100)
           {
            if(player[2].items[5][1]>=1)
               {
                player[2].items[5][1]--;
                player[2].hp+=10;
                if(player[2].hp>100)
                   player[2].hp=100;
                player[2].print_hp(1,27);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(20+27*40,120,clear,screen);
                int a=player[2].items[5][1];
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
		      apply_surface(27*40,120,image,screen);
               }
           }
        if(power1==1 && player[2].mana>=10 && player[2].hp<=90)
           {
            player[2].mana-=10;
            player[2].hp+=10;
            player[2].print_mana(2,COL_MAX+COL_START+2);
            player[2].print_hp(1,COL_MAX+COL_START+2);
           }
        if(power2==1 && player[2].mana>=30 && player[2].permission==0)
           {
            player[2].mana-=30;
            player[2].permission=1;
            if(max(player[1].lin,player[2].lin)-min(player[1].lin,player[2].lin)<=2 && max(player[1].col,player[2].col)-min(player[1].col,player[2].col)<=2)
               {
                player[1].hp-=40+player[2].fire_dmg*3/10-player[1].fire_res*3/10;
                player[1].print_hp(1,0);
               }
            if(player[2].lin-2<=0)
               beg1=1;
            else
               beg1=player[2].lin-2;
            if(player[2].lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player[2].lin+2;
            if(player[2].col-2<=0)
               beg2=1;
            else
               beg2=player[2].col-2;
            if(player[2].col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player[2].col+2;
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
            player[2].print_mana(2,COL_MAX+COL_START+2);
           }
        if(power3==1 && player[2].hp>10)
           {
            player[2].hp-=10;
            player[2].mana+=10;
            player[2].print_mana(2,COL_MAX+COL_START+2);
            player[2].print_hp(1,COL_MAX+COL_START+2);
           }
        if(atack_left==1 && player[2].permission_basic==0)
           {
            player[2].skin=player[2].default_left_skin;
            player[2].skin_state=0;
            if(obs[player[2].lin][player[2].col-1]==3)
               {
			 player[2].permission_basic=1;
			 player[1].hp-=10+player[2].attack/10-player[1].block/10;
			 player[1].skin=player[1].default_hit_skin_right;
			 player[1].skin_state=1;
			 apply_surface((player[1].col+COL_START)*40,player[1].lin*40,player[1].skin,screen);
                player[1].print_hp(1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack_right==1 && player[2].permission_basic==0)
           {
            player[2].skin=player[2].default_right_skin;
            player[2].skin_state=1;
            if(obs[player[2].lin][player[2].col+1]==3)
               {
			 player[2].permission_basic=1;
			 player[1].hp-=10+player[2].attack/10-player[1].block/10;
			 player[1].skin=player[1].default_hit_skin_left;
			 player[1].skin_state=0;
			 apply_surface((player[1].col+COL_START)*40,player[1].lin*40,player[1].skin,screen);
                player[1].print_hp(1,0);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player[2].lin>=1)
           {
            time_ex++;
            if(obs[player[2].lin-1][player[2].col]==0)
               {
                obs[player[2].lin][player[2].col]=0;
			 put_back(player[2].lin,player[2].col);
                player[2].lin--;
                if(map[player[2].lin][player[2].col]!=map[player[2].lin+1][player[2].col])
                   player[2].get_skin(player[2].prefix);
                obs[player[2].lin][player[2].col]=2;
               }
            if(player[2].skin_state==1)
               {
			 player[2].skin=player[2].default_right_skin;
               }
		  else
               {
			 player[2].skin=player[2].default_left_skin;
               }
           }
        if(down==1 && player[2].lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player[2].lin+1][player[2].col]==0)
               {
                obs[player[2].lin][player[2].col]=0;
			 put_back(player[2].lin,player[2].col);
                player[2].lin++;
                if(map[player[2].lin][player[2].col]!=map[player[2].lin-1][player[2].col])
                   player[2].get_skin(player[2].prefix);
                obs[player[2].lin][player[2].col]=2;
               }
            if(player[2].skin_state==1)
               {
			 player[2].skin=player[2].default_right_skin;
               }
		  else
               {
			 player[2].skin=player[2].default_left_skin;
               }
           }
        if(left==1 && player[2].col>=1)
           {
		  time_ex++;
            if(obs[player[2].lin][player[2].col-1]==0)
               {
                obs[player[2].lin][player[2].col]=0;
			 put_back(player[2].lin,player[2].col);
                player[2].col--;
                if(map[player[2].lin][player[2].col]!=map[player[2].lin][player[2].col+1])
                   player[2].get_skin(player[2].prefix);
                obs[player[2].lin][player[2].col]=2;
                player[2].skin=player[2].default_left_skin;
                player[2].skin_state=0;
               }
           }
        if(right==1 && player[2].col<LIN_MAX)
           {
            time_ex++;
            if(obs[player[2].lin][player[2].col+1]==0)
               {
                obs[player[2].lin][player[2].col]=0;
			 put_back(player[2].lin,player[2].col);
                player[2].col++;
                if(map[player[2].lin][player[2].col]!=map[player[2].lin][player[2].col-1])
                   player[2].get_skin(player[2].prefix);
                obs[player[2].lin][player[2].col]=2;
                player[2].skin=player[2].default_right_skin;
                player[2].skin_state=1;
               }
           }
        apply_surface((player[2].col+COL_START)*40,player[2].lin*40,player[2].skin,screen);
        if(computer!=1)
           {
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
           }
        else
           computer_move_player(difficulty,1);
        if(mana_pot==1 && player[1].mana<100)
           {
            if(player[1].items[5][2]>=1)
               {
                player[1].items[5][2]--;
                player[1].mana+=10;
                if(player[1].mana>100)
                   player[1].mana=100;
                player[1].print_mana(2,0);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(80,120,clear,screen);
                int a=player[1].items[5][2];
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
		      apply_surface(100,120,image,screen);
               }
           }
        if(hp_pot==1 && player[1].hp<100)
           {
            if(player[1].items[5][1]>=1)
               {
                player[1].items[5][1]--;
                player[1].hp+=10;
                if(player[1].hp>100)
                   player[1].hp=100;
                player[1].print_hp(1,0);
                clear=SDL_LoadBMP("inventory_clear.bmp");
                apply_surface(20,120,clear,screen);
                int a=player[1].items[5][1];
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
		      apply_surface(20,120,image,screen);
               }
           }
        if(power1==1 && player[1].mana>=10 && player[1].hp<=90)
           {
            player[1].mana-=10;
            player[1].hp+=10;
            player[1].print_mana(2,0);
            player[1].print_hp(1,0);
           }
        if(power2==1 && player[1].mana>=30 && player[1].permission==0)
           {
            player[1].mana-=30;
            player[1].permission=1;
            if(max(player[2].lin,player[1].lin)-min(player[1].lin,player[2].lin)<=2 && max(player[1].col,player[2].col)-min(player[1].col,player[2].col)<=2)
               {
                player[2].hp-=40+player[1].fire_dmg*3/10-player[2].fire_res*3/10;
                player[2].print_hp(1,COL_MAX+COL_START+2);
               }
            if(player[1].lin-2<=0)
               beg1=1;
            else
               beg1=player[1].lin-2;
            if(player[1].lin+2>=LIN_MAX)
               end1=LIN_MAX;
            else
               end1=player[1].lin+2;
            if(player[1].col-2<=0)
               beg2=1;
            else
               beg2=player[1].col-2;
            if(player[1].col+2>=COL_MAX)
               end2=COL_MAX;
            else
               end2=player[1].col+2;
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
            player[1].print_mana(2,0);
           }
        if(power3==1 && player[1].hp>10)
           {
            player[1].hp-=10;
            player[1].mana+=10;
            player[1].print_mana(2,0);
            player[1].print_hp(1,0);
           }
        if(atack1_left==1 && player[1].permission_basic==0 && flag_player==0)
           {
            if(obs[player[1].lin][player[1].col-1]==2)
               {
			 player[1].permission_basic=1;
                player[1].skin=player[1].default_left_skin;
                player[1].skin_state=0;
			 player[2].hp-=10+player[1].attack/10-player[2].block/10;
                //SDL_FreeSurface(player);
                player[2].print_hp(1,COL_MAX+COL_START+2);
                player[2].skin=player[2].default_hit_skin_right;
                player[2].skin_state=1;
                apply_surface((player[2].col+COL_START)*40,player[2].lin*40,player[2].skin,screen);
                SDL_Flip(screen);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(atack1_right==1 && player[1].permission_basic==0 && flag_player==0)
           {
            if(obs[player[1].lin][player[1].col+1]==2)
               {
			    player[1].permission_basic=1;
                player[1].skin=player[1].default_right_skin;
                player[1].skin_state=1;
			    player[2].hp-=10+player[1].attack/10-player[2].block/10;
                player[2].print_hp(1,COL_MAX+COL_START+2);
                //SDL_FreeSurface(player);
                player[2].skin=player[2].default_hit_skin_left;
                player[2].skin_state=0;
                apply_surface((player[2].col+COL_START)*40,player[2].lin*40,player[2].skin,screen);
                SDL_Flip(screen);
                Mix_PlayChannel(-1, sound, 0);
               }
           }
        if(up==1 && player[1].lin>=1)
           {
            time_ex++;
            if(obs[player[1].lin-1][player[1].col]==0)
               {
                obs[player[1].lin][player[1].col]=0;
			 put_back(player[1].lin,player[1].col);
                player[1].lin--;
                if(map[player[1].lin][player[1].col]!=map[player[1].lin+1][player[1].col])
                   player[1].get_skin(player[1].prefix);
                obs[player[1].lin][player[1].col]=3;
               }
            if(player[1].skin_state==1)
               {
			 player[1].skin=player[1].default_right_skin;
               }
		  else
               {
			 player[1].skin=player[1].default_left_skin;
               }
           }
        if(down==1 && player[1].lin<COL_MAX)
           {
		  time_ex++;
            if(obs[player[1].lin+1][player[1].col]==0)
               {
                obs[player[1].lin][player[1].col]=0;
			 put_back(player[1].lin,player[1].col);
                player[1].lin++;
                if(map[player[1].lin][player[1].col]!=map[player[1].lin-1][player[1].col])
                   player[1].get_skin(player[1].prefix);
			 obs[player[1].lin][player[1].col]=3;
               }
            if(player[1].skin_state==1)
               {
			 player[1].skin=player[1].default_right_skin;
               }
		  else
               {
			 player[1].skin=player[1].default_left_skin;
               }
           }
        if(left==1 && player[1].col>=1)
           {
            time_ex++;
            if(obs[player[1].lin][player[1].col-1]==0)
			{
			 obs[player[1].lin][player[1].col]=0;
			 put_back(player[1].lin,player[1].col);
                player[1].col--;
                if(map[player[1].lin][player[1].col]!=map[player[1].lin][player[1].col+1])
                   player[1].get_skin(player[1].prefix);
                obs[player[1].lin][player[1].col]=3;
                player[1].skin=player[1].default_left_skin;
                player[1].skin_state=0;
               }
           }
        if(right==1 && player[1].col<LIN_MAX)
           {
            time_ex++;
            if(obs[player[1].lin][player[1].col+1]==0)
               {
                obs[player[1].lin][player[1].col]=0;
			 put_back(player[1].lin,player[1].col);
                player[1].col++;
                if(map[player[1].lin][player[1].col]!=map[player[1].lin][player[1].col-1])
                   player[1].get_skin(player[1].prefix);
                obs[player[1].lin][player[1].col]=3;
                player[1].skin=player[1].default_right_skin;
                player[1].skin_state=1;
                }
           }
        SDL_Delay(50);
        apply_surface((player[1].col+COL_START)*40,player[1].lin*40,player[1].skin,screen);
        SDL_Flip(screen);
        SDL_PumpEvents();
       }
 if(player[2].hp>player[1].hp)
    {
     player[1].skin=player[1].default_dead_skin;
     apply_surface((player[1].col+COL_START)*40,player[1].lin*40,player[1].skin,screen);
     message=TTF_RenderText_Solid(font,"Player 2 wins!",textColor);
     player[2].money+=player[2].hp+player[2].mana+player[1].money/50;
     player[1].money+=player[2].money/75+20;
     int x1=player[1].money,x2=player[2].money;
     if(player[1].items_equipped[6]==1)
        player[1].money+=player[2].money/75;
     if(player[2].items_equipped[6]==1)
        player[2].money+=x1/75;
     player[2].xp+=100;
     player[1].xp+=20;
    }
 else
    if(player[2].hp!=player[1].hp)
       {
        player[2].skin=player[2].default_dead_skin;
        apply_surface((player[2].col+COL_START)*40,player[2].lin*40,player[2].skin,screen);
        message=TTF_RenderText_Solid(font,"Player 1 wins!",textColor);
        player[1].money+=player[1].hp+player[1].mana+player[2].money/50;
        player[2].money+=player[1].money/75+20;
        int x1=player[1].money,x2=player[2].money;
        if(player[1].items_equipped[6]==1)
           player[1].money+=player[2].money/75;
	   if(player[2].items_equipped[6]==1)
		 player[2].money+=x1/75;
        player[1].xp+=100;
        player[2].xp+=20;
       }
    else
       {
        player[1].skin=player[1].default_dead_skin;
        apply_surface((player[1].col+COL_START)*40,player[1].lin*40,player[1].skin,screen);
        player[2].skin=player[2].default_dead_skin;
        apply_surface((player[2].col+COL_START)*40,player[2].lin*40,player[2].skin,screen);
	   message=TTF_RenderText_Solid(font,"Round draw!",textColor);
        int cash=(player[2].money+player[1].money)/2/25;
        player[1].money+=cash;
        player[2].money+=cash;
        int x1=player[1].money,x2=player[2].money;
        if(player[1].items_equipped[6]==1)
           player[1].money+=player[2].money/75;
        if(player[2].items_equipped[6]==1)
           player[2].money+=x1/75;
        player[2].xp+=50;
        player[1].xp+=50;
       }
 player[1].save("player1");
 player[2].save("player2");
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
