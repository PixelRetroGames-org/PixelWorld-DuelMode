#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include<ctime>
#include "alex.h"
SDL_Surface *screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
SDL_Surface *clear,*message;
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
class player
{
 public:
 int hp,xp,mana,money,items[10][10],items_equipped[7];
 int attack,block,fire_res,fire_dmg,permission_basic,permission;
 int lin,col;
 void load_save(char *nume_salvare)
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
  fscanf(salvare,"%d %d",&money,&xp);
  for(int j=1;j<=5;j++)
      for(int i=1;i<=4;i++)
	      fscanf(salvare,"%d",&items[i][j]);
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
  SDL_Surface *helmet,*chestplate,*boots,*trousers,*sword;
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
 apply_surface(27*40+20,280,helmet,screen);
 apply_surface(27*40+20,360,chestplate,screen);
 apply_surface(27*40+20,440,trousers,screen);
 apply_surface(27*40+20,520,boots,screen);
 apply_surface(27*40+100,360,sword,screen);
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
