#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include "alex.h"
int player1_money,player_money,player_xp,player1_xp;
int player1_items[10][10],prices[10][10];
int player1_items_equipped[7],player_items_equipped[7];
SDL_Surface *background,*screen,*image;
TTF_Font *font=NULL;
int player1_attack,player1_block,player1_fire_res,player1_fire_dmg;
void load_prices()
{
 int i,j;
 FILE *prc=fopen("player1_prices.prc","r");
 for(j=1;j<=5;j++)
	{
	 for(i=1;i<=4;i++)
		fscanf(prc,"%d",&prices[i][j]);
	}
 for(i=5;i<=5;i++)
     for(j=1;j<=5;j++)
         fscanf(prc,"%d",&prices[i][j]);
 fclose(prc);
}
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
void print_money(int a,int lin,int col)
{
 SDL_Surface *clear,*message;
 SDL_Color color2={255,194,10};
 int i=0,i1,j;
 if(a<0)
    a=0;
 char v[10]={0,0,0,0,0,0,0,0,0,0},v1[10]={0,0,0,0,0,0,0,0,0,0};
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
 v1[i+1]=' ';
 v1[i+2]='G';
 v1[i+3]='o';
 v1[i+4]='l';
 v1[i+5]='d';
 v1[i+6]=NULL;
 message=TTF_RenderText_Solid(font,v1+1,color2);
 apply_surface(col*40,lin*40,message,screen);
}
void print_xp(int a,int lin,int col)
{
 SDL_Surface *clear,*message;
 SDL_Color color2={174,0,0};
 int i=0,i1,j;
 if(a<0)
    a=0;
 char v[10]={0,0,0,0,0,0,0,0,0,0},v1[10]={0,0,0,0,0,0,0,0,0,0};
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
 v1[i+1]=' ';
 v1[i+2]='X';
 v1[i+3]='P';
 v1[i+4]=NULL;
 message=TTF_RenderText_Solid(font,v1+1,color2);
 apply_surface(col*40,lin*40,message,screen);
}
char* int_to_char(int a)
{
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
 for(i1=1,j=i;i1<=i;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 return v1;
}
void print_main_layer()
{
 image=SDL_LoadBMP("inventory_potion.bmp");
 apply_surface(0,80,image,screen);
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
     fprintf(salvare,"0 0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
     fclose(salvare);
     salvare=fopen(nume_salvare1,"r");
    }
 fscanf(salvare,"%d %d ",&player1_money,&player1_xp);
 for(int j=1;j<=5;j++)
     for(int i=1;i<=4;i++)
         {
		fscanf(salvare,"%d",&player1_items[i][j]);
         }
 for(int i=5;i<=5;i++)
     for(int j=1;j<=5;j++)
         fscanf(salvare,"%d ",&player1_items[i][j]);
}
void print_player_info(bool pp)
{
 TTF_Init();
 SDL_Surface *message;
 message=SDL_LoadBMP("clear_player_info.bmp");
 apply_surface(0,0,message,screen);
 SDL_Color color1={0,900,0};
 font=TTF_OpenFont("font2.ttf",50);
 message=TTF_RenderText_Solid(font,"Player 1",color1);
 apply_surface(0,0,message,screen);
 if(pp==true)
    load_save_player1("player1");
 color1={174,0,0};
 message=TTF_RenderText_Solid(font,"Experience: ",color1);
 apply_surface(230,0,message,screen);
 print_xp(player1_xp,0,13);
 color1={255,194,0};
 message=TTF_RenderText_Solid(font,"Money: ",color1);
 apply_surface(750,0,message,screen);
 print_money(player1_money,0,24);
 SDL_Flip(screen);
}
void print_shop(int m,int n)
{
 TTF_Font *font1=TTF_OpenFont("font2.ttf",40);
 SDL_Color color1={255,190,0};
 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
 SDL_Color color2={255,294,10};
 image=SDL_LoadBMP("inventory_lvl1_helmet.bmp");
 apply_surface(0,80,image,screen);
 int a=prices[1][1];
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
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(0,160,image,screen);

 image=SDL_LoadBMP("inventory_lvl1_chestplate.bmp");
 apply_surface(0,200,image,screen);
 a=prices[2][1];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(0,280,image,screen);
 image=SDL_LoadBMP("inventory_lvl1_trousers.bmp");
 apply_surface(0,320,image,screen);
 a=prices[3][1];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(0,400,image,screen);
 image=SDL_LoadBMP("inventory_lvl1_boots.bmp");
 apply_surface(0,440,image,screen);
 a=prices[4][1];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(0,520,image,screen);

 image=SDL_LoadBMP("inventory_lvl2_helmet.bmp");
 apply_surface(160,80,image,screen);
 a=prices[2][1];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(160,160,image,screen);
 image=SDL_LoadBMP("inventory_lvl2_chestplate.bmp");
 apply_surface(160,200,image,screen);
 a=prices[2][2];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(160,280,image,screen);
 image=SDL_LoadBMP("inventory_lvl2_trousers.bmp");
 apply_surface(160,320,image,screen);
 a=prices[3][2];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(160,400,image,screen);
 image=SDL_LoadBMP("inventory_lvl2_boots.bmp");
 apply_surface(160,440,image,screen);
 a=prices[4][2];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(160,520,image,screen);

 image=SDL_LoadBMP("inventory_lvl3_helmet.bmp");
 apply_surface(320,80,image,screen);
 a=prices[1][3];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(320,160,image,screen);
 image=SDL_LoadBMP("inventory_lvl3_chestplate.bmp");
 apply_surface(320,200,image,screen);
 a=prices[2][3];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(320,280,image,screen);
 image=SDL_LoadBMP("inventory_lvl3_trousers.bmp");
 apply_surface(320,320,image,screen);
 a=prices[3][3];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(320,400,image,screen);
 image=SDL_LoadBMP("inventory_lvl3_boots.bmp");
 apply_surface(320,440,image,screen);
 a=prices[4][3];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(320,520,image,screen);

 image=SDL_LoadBMP("inventory_lvl4_helmet.bmp");
 apply_surface(480,80,image,screen);
 a=prices[1][4];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(480,160,image,screen);
 image=SDL_LoadBMP("inventory_lvl4_chestplate.bmp");
 apply_surface(480,200,image,screen);
 a=prices[2][4];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(480,280,image,screen);
 image=SDL_LoadBMP("inventory_lvl4_trousers.bmp");
 apply_surface(480,320,image,screen);
 a=prices[3][4];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(480,400,image,screen);
 image=SDL_LoadBMP("inventory_lvl4_boots.bmp");
 apply_surface(480,440,image,screen);
 a=prices[4][4];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(480,520,image,screen);

 image=SDL_LoadBMP("inventory_lvl1_sword.bmp");
 apply_surface(640,80,image,screen);
 a=prices[1][5];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(640,160,image,screen);
 image=SDL_LoadBMP("inventory_lvl2_sword.bmp");
 apply_surface(640,200,image,screen);
 a=prices[2][5];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(640,280,image,screen);
 image=SDL_LoadBMP("inventory_lvl3_sword.bmp");
 apply_surface(640,320,image,screen);
 a=prices[3][5];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(640,400,image,screen);
 image=SDL_LoadBMP("inventory_lvl4_sword.bmp");
 apply_surface(640,440,image,screen);
 a=prices[4][5];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(640,520,image,screen);
 for(int y=1;y<=n;y++)
     for(int x=1;x<=m;x++)
         {
         	if(player1_items[x][y]==1)
         	   {
		    image=TTF_RenderText_Solid(font2,"x1",color2);
		    //apply_surface((y-1)*160,x*80+(x-1)*40-10,image,screen);
		    apply_surface((y-1)*160+160-20,x*80+(x-1)*40,image,screen);
         	   }
         }
 /**
 Potions and amulets
 **/
 image=SDL_LoadBMP("inventory_life_potion.bmp");
 apply_surface(0,560,image,screen);
 a=prices[5][1];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(0,640,image,screen);
 image=SDL_LoadBMP("inventory_mana_potion.bmp");
 apply_surface(160,560,image,screen);
 a=prices[5][2];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(160,640,image,screen);
 image=SDL_LoadBMP("inventory_amulet_of_Greed.bmp");
 apply_surface(320,560,image,screen);
 a=prices[5][3];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(320,640,image,screen);
 image=SDL_LoadBMP("inventory_amulet_of_FireRes.bmp");
 apply_surface(480,560,image,screen);
 a=prices[5][4];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(480,640,image,screen);
 image=SDL_LoadBMP("inventory_devil's_amulet.bmp");
 apply_surface(640,560,image,screen);
 a=prices[5][5];
 i=0,i1,j;
 if(a<0)
    a=0;
 v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
 v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
 while(a!=0)
       {
        i++;
        v[i]=a%10+'0';
        a/=10;
       }
 for(i1=0,j=i;j>=1;i1++,j--)
     v1[i1]=v[j];
 if(i==0)
    {
     i++;
     v1[i]='0';
    }
 image=TTF_RenderText_Solid(font1,v1,color1);
 apply_surface(640,640,image,screen);
 for(int y=1;y<=n;y++)
     for(int x=1;x<=m+1;x++)
         {
         	if(!(x==5 && y<=2))
         	   {
		    if(player1_items[x][y]==1)
         	       {
		        image=TTF_RenderText_Solid(font2,"x1",color2);
		        //apply_surface((y-1)*160,x*80+(x-1)*40-10,image,screen);
		        apply_surface((y-1)*160+160-20,x*80+(x-1)*40,image,screen);
         	       }
         	   }
         }
 for(int x=n;x<=n;x++)
     for(int y=1;y<=2;y++)
         {
          a=player1_items[x][y];
		i=0,i1,j;
		if(a<0)
		   a=0;
		v[0]=v[1]=v[2]=v[3]=v[4]=v[5]=v[6]=v[7]=v[8]=v[9]=0;
		v1[0]=v1[1]=v1[2]=v1[3]=v1[4]=v1[5]=v1[6]=v1[7]=v1[8]=v1[9]=0;
		while(a!=0)
			 {
			  i++;
			  v[i]=a%10+'0';
			  a/=10;
			 }
		for(i1=1,j=i;j>=1;i1++,j--)
		    v1[i1]=v[j];
		if(i1!=1)
		   v1[0]='x';
		image=TTF_RenderText_Solid(font2,v1,color2);
		apply_surface((y-1)*160+160-40,x*80+(x-1)*40,image,screen);
         }
}
void shop(int m,int n)
{
 int x=1,y=1,exit=0,down,up,left,right,enter;
 SDL_Color color1={255,194,10},color2={255,294,10};
 SDL_Surface *image;
 TTF_Font *font2=TTF_OpenFont("font2.ttf",20);
 while(exit==0)
	  {
	   exit=getkey(VK_ESCAPE);
	   down=up=left=right=0;
	   up=getkey('A');
	   down=getkey('D');
	   left=getkey('W');
	   right=getkey('S');
	   image=SDL_LoadBMP("vertical_black_item_layer.bmp");
	   apply_surface((y-1)*160,x*80+(x-1)*40,image,screen);
	   apply_surface((y-1)*160+160,x*80+(x-1)*40,image,screen);
	   image=SDL_LoadBMP("horizontal_black_item_layer.bmp");
	   apply_surface((y-1)*160,x*80+(x-1)*40,image,screen);
        apply_surface((y-1)*160,x*80+(x-1)*40+80-3,image,screen);
        if(up==1 && y>=2)
	      y--;
        if(left==1 && x>=2)
		 x--;
        if(down==1 && y<=n-1)
		 y++;
        if(right==1 && x<=m-1)
		 x++;
	   image=SDL_LoadBMP("vertical_item_layer.bmp");
	   apply_surface((y-1)*160,x*80+(x-1)*40,image,screen);
        apply_surface((y-1)*160+160,x*80+(x-1)*40,image,screen);
        image=SDL_LoadBMP("horizontal_item_layer.bmp");
	   apply_surface((y-1)*160,x*80+(x-1)*40,image,screen);
        apply_surface((y-1)*160,x*80+(x-1)*40+80-3,image,screen);
        SDL_Flip(screen);
        enter=getkey(VK_SPACE);
        if(enter==1)
           {
            if(player1_money>=prices[x][y] && player1_items[x][y]==0 && (x<=4 || (x==5 && y>2)))
			{
			 player1_money-=prices[x][y];
			 player1_items[x][y]=1;
			 print_player_info(false);
			 image=TTF_RenderText_Solid(font2,"x1",color2);
			 //apply_surface((y-1)*160,x*80+(x-1)*40-10,image,screen);
			 apply_surface((y-1)*160+160-20,x*80+(x-1)*40,image,screen);
			}
		  else
		     {
		      if(player1_money>=prices[x][y] && player1_items[x][y]<100 && x>4 && y<=2)
			    {
				player1_money-=prices[x][y];
				player1_items[x][y]++;
				print_player_info(false);
				image=SDL_LoadBMP("inventory_clear.bmp");
				apply_surface((y-1)*160+160-40,x*80+(x-1)*40,image,screen);
				int a=player1_items[x][y];
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
				v1[0]='x';
				if(i==0)
				   {
				    i++;
				    v1[i]='0';
				   }
                    image=TTF_RenderText_Solid(font2,v1,color2);
				//apply_surface((y-1)*160,x*80+(x-1)*40-10,image,screen);
				apply_surface((y-1)*160+160-40,x*80+(x-1)*40,image,screen);
			    }
		     }
           }
        SDL_Delay(100);
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
 for(int i=5;i<=5;i++)
     for(int j=1;j<=5;j++)
         {
         	fprintf(salvare,"%d\n",player1_items[i][j]);
         }
}
int main(int argc,char* args[])
{
 SDL_Init(SDL_INIT_EVERYTHING);
 screen=SDL_SetVideoMode(0,0,32,SDL_FULLSCREEN);
 background=SDL_LoadBMP("wooden_background.bmp");
 apply_surface(0,0,background,screen);
 //print_main_layer();
 load_prices();
 print_player_info(true);
 print_shop(4,5);
 SDL_Flip(screen);
 shop(5,5);
 save_player1("player1");
 //SDL_Delay(1000);
return 0;
}
