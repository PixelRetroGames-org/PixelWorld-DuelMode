#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<cstdio>
#include<ctime>
#define SLEEP 100
SDL_Surface *screen,*image;
int table[10][10],table_copy[10][10];
long long Score,HiScore,NewScore,Undo=1;
int pp;
int LM=1; //LastMove
bool up,down,right,left,undo;
TTF_Font *font=NULL,*font1=NULL;
SDL_Color color={0,900,0},color1={255,4,0},color2={255,216,0};
Uint8 *keystates=SDL_GetKeyState(NULL);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
 SDL_Rect offset;
 offset.x=x;
 offset.y=y;
 SDL_BlitSurface(source,NULL,destination,&offset);
}
SDL_Surface *get_image(int name)
{
 int x=0;
 int v1[5]={0,0,0,0,0};
 while(name!=0)
       {
        x++;
        v1[x]=name%10;
        name/=10;
       }
 int y=0;
 char v[5]={0,0,0,0,0};
 for(;x>=1;x--)
     {
      v[y]=v1[x]+'0';
      y++;
	}
 if(y==0)
    {
    	v[0]='0';
     y=1;
    }
 v[y]='.';
 v[y+1]='b';
 v[y+2]='m';
 v[y+3]='p';
 SDL_Surface *image=SDL_LoadBMP(v);
 return image;
}
void print_table()
{
 SDL_Surface *image=NULL;
 int i,j;
 for(i=1;i<=4;i++)
     for(j=1;j<=4;j++)
         {
          image=get_image(table[i][j]);
          apply_surface((j-1)*160,(i-1)*160,image,screen);
         }
 SDL_Flip(screen);
}
void move_pieces(int direction)
{
 int i,j;
 int state=0;
 switch(direction)
 {
  //up
  case 1:
         {
         	for(j=1;j<=4;j++)
         	    {
         	     for(i=2;i<=4;i++)
			    {
			    	int ci=i;
			    	while(table[ci-1][j]==0 && ci>=2)
			    	      {
			    	       if(table[ci][j]!=0)
			    	          state=1;
				       table[ci-1][j]=table[ci][j];
				       table[ci][j]=0;
				       ci--;
			    	      }
			    }
			if(table[2][j]==table[1][j])
			   {
			    state=1;
			    table[1][j]+=table[2][j];
			    Score+=table[1][j];
			    table[2][j]=0;
			   }
			if(table[3][j]==table[2][j])
			   {
			    state=1;
			    table[2][j]+=table[3][j];
			    Score+=table[2][j];
			    table[3][j]=0;
			   }
			if(table[4][j]==table[3][j])
			   {
			    state=1;
			    table[3][j]+=table[4][j];
			    Score+=table[3][j];
			    table[4][j]=0;
			   }
			for(i=2;i<=4;i++)
			    {
			    	int ci=i;
			    	while(table[ci-1][j]==0 && ci>=2)
			    	      {
			    	       if(table[ci][j]!=0)
			    	          state=1;
				       table[ci-1][j]=table[ci][j];
				       table[ci][j]=0;
				       ci--;
			    	      }
			    }
         	    }
         	break;
	    }
  //down
  case 2:
         {
         	for(j=1;j<=4;j++)
         	    {
         	     for(i=3;i>=1;i--)
			    {
			    	int ci=i;
			    	while(table[ci+1][j]==0 && ci<=3)
			    	      {
			    	       if(table[ci][j]!=0)
			    	          state=1;
				       table[ci+1][j]=table[ci][j];
				       table[ci][j]=0;
				       ci++;
			    	      }
			    }
			if(table[4][j]==table[3][j])
			   {
			    state=1;
			    table[4][j]+=table[3][j];
			    Score+=table[4][j];
			    table[3][j]=0;
			   }
			if(table[3][j]==table[2][j])
			   {
			    state=1;
			    table[3][j]+=table[2][j];
			    Score+=table[3][j];
			    table[2][j]=0;
			   }
			if(table[2][j]==table[1][j])
			   {
			    state=1;
			    table[2][j]+=table[1][j];
			    Score+=table[2][j];
			    table[1][j]=0;
			   }
			for(i=3;i>=1;i--)
			    {
			    	int ci=i;
			    	while(table[ci+1][j]==0 && ci<=3)
			    	      {
			    	       if(table[ci][j]!=0)
			    	          state=1;
				       table[ci+1][j]=table[ci][j];
				       table[ci][j]=0;
				       ci++;
			    	      }
			    }
         	    }
         	break;
	    }
  //left
  case 3:
         {
         	for(i=1;i<=4;i++)
         	    {
         	    	for(j=2;j<=4;j++)
         	    	    {
         	    	    	int cj=j;
			    	while(table[i][cj-1]==0 && cj>=2)
			    	      {
			    	       if(table[i][cj]!=0)
			    	          state=1;
				       table[i][cj-1]=table[i][cj];
				       table[i][cj]=0;
				       cj--;
			    	      }
         	    	    }
			if(table[i][1]==table[i][2])
         	    	   {
         	    	    state=1;
			    table[i][1]+=table[i][2];
			    Score+=table[i][1];
			    table[i][2]=0;
         	    	   }
         	    	if(table[i][2]==table[i][3])
         	    	   {
         	    	    state=1;
			    table[i][2]+=table[i][3];
			    Score+=table[i][2];
			    table[i][3]=0;
         	    	   }
         	    	if(table[i][3]==table[i][4])
         	    	   {
         	    	    state=1;
			    table[i][3]+=table[i][4];
			    Score+=table[i][3];
			    table[i][4]=0;
         	    	   }
         	    	for(j=2;j<=4;j++)
         	    	    {
         	    	    	int cj=j;
			    	while(table[i][cj-1]==0 && cj>=2)
			    	      {
			    	       if(table[i][cj]!=0)
			    	          state=1;
				       table[i][cj-1]=table[i][cj];
				       table[i][cj]=0;
				       cj--;
			    	      }
         	    	    }
         	    }
         	break;
         }
  //right
  case 4:
         {
         	for(i=1;i<=4;i++)
         	    {
         	     for(j=3;j>=1;j--)
			    {
			    	int cj=j;
			    	while(table[i][cj+1]==0 && cj<=3)
			    	      {
			    	       if(table[i][cj]!=0)
			    	          state=1;
				       table[i][cj+1]=table[i][cj];
				       table[i][cj]=0;
				       cj++;
			    	      }
			    }
			if(table[i][3]==table[i][4])
         	    	   {
         	    	    state=1;
			    table[i][4]+=table[i][3];
			    Score+=table[i][4];
			    table[i][3]=0;
         	    	   }
         	    	if(table[i][2]==table[i][3])
         	    	   {
         	    	    state=1;
			    table[i][3]+=table[i][2];
			    Score+=table[i][3];
			    table[i][2]=0;
         	    	   }
         	    	if(table[i][1]==table[i][2])
         	    	   {
         	    	    state=1;
			    table[i][2]+=table[i][1];
			    Score+=table[i][2];
			    table[i][1]=0;
         	    	   }
         	    	for(j=3;j>=1;j--)
			    {
			    	int cj=j;
			    	while(table[i][cj+1]==0 && cj<=3)
			    	      {
			    	       if(table[i][cj]!=0)
			    	          state=1;
				       table[i][cj+1]=table[i][cj];
				       table[i][cj]=0;
				       cj++;
			    	      }
			    }
         	    }
         	break;
         }
 }
 //return state;
}
bool more_moves(int direction)
{
 int v[10][10];
 int i,j;
 int state=0;
 for(i=1;i<=4;i++)
     for(j=1;j<=4;j++)
         v[i][j]=table[i][j];
 switch(direction)
 {
  //up
  case 1:
         {
         	for(j=1;j<=4;j++)
         	    {
         	     for(i=2;i<=4;i++)
			    {
			    	int ci=i;
			    	while(v[ci-1][j]==0 && ci>=2)
			    	      {
			    	       if(v[ci][j]!=0)
			    	          state=1;
				       v[ci-1][j]=v[ci][j];
				       v[ci][j]=0;
				       ci--;
			    	      }
			    }
			if(v[2][j]==v[1][j])
			   {
			    state=1;
			    v[1][j]+=v[2][j];
			    //Score+=v[1][j];
			    v[2][j]=0;
			   }
			if(v[3][j]==v[2][j])
			   {
			    state=1;
			    v[2][j]+=v[3][j];
			    //Score+=v[2][j];
			    v[3][j]=0;
			   }
			if(v[4][j]==v[3][j])
			   {
			    state=1;
			    v[3][j]+=v[4][j];
			    //Score+=v[3][j];
			    v[4][j]=0;
			   }
			for(i=2;i<=4;i++)
			    {
			    	int ci=i;
			    	while(v[ci-1][j]==0 && ci>=2)
			    	      {
			    	       if(v[ci][j]!=0)
			    	          state=1;
				       v[ci-1][j]=v[ci][j];
				       v[ci][j]=0;
				       ci--;
			    	      }
			    }
         	    }
         	break;
	    }
  //down
  case 2:
         {
         	for(j=1;j<=4;j++)
         	    {
         	     for(i=3;i>=1;i--)
			    {
			    	int ci=i;
			    	while(v[ci+1][j]==0 && ci<=3)
			    	      {
			    	       if(v[ci][j]!=0)
			    	          state=1;
				       v[ci+1][j]=v[ci][j];
				       v[ci][j]=0;
				       ci++;
			    	      }
			    }
			if(v[4][j]==v[3][j])
			   {
			    state=1;
			    v[4][j]+=v[3][j];
			    //Score+=v[4][j];
			    v[3][j]=0;
			   }
			if(v[3][j]==v[2][j])
			   {
			    state=1;
			    v[3][j]+=v[2][j];
			    //Score+=v[3][j];
			    v[2][j]=0;
			   }
			if(v[2][j]==v[1][j])
			   {
			    state=1;
			    v[2][j]+=v[1][j];
			    //Score+=v[2][j];
			    v[1][j]=0;
			   }
			for(i=3;i>=1;i--)
			    {
			    	int ci=i;
			    	while(v[ci+1][j]==0 && ci<=3)
			    	      {
			    	       if(v[ci][j]!=0)
			    	          state=1;
				       v[ci+1][j]=v[ci][j];
				       v[ci][j]=0;
				       ci++;
			    	      }
			    }
         	    }
         	break;
	    }
  //left
  case 3:
         {
         	for(i=1;i<=4;i++)
         	    {
         	    	for(j=2;j<=4;j++)
         	    	    {
         	    	    	int cj=j;
			    	while(v[i][cj-1]==0 && cj>=2)
			    	      {
			    	       if(v[i][cj]!=0)
			    	          state=1;
				       v[i][cj-1]=v[i][cj];
				       v[i][cj]=0;
				       cj--;
			    	      }
         	    	    }
			if(v[i][1]==v[i][2])
         	    	   {
         	    	    state=1;
			    v[i][1]+=v[i][2];
			    //Score+=v[i][1];
			    v[i][2]=0;
         	    	   }
         	    	if(v[i][2]==v[i][3])
         	    	   {
         	    	    state=1;
			    v[i][2]+=v[i][3];
			    //Score+=v[i][2];
			    v[i][3]=0;
         	    	   }
         	    	if(v[i][3]==v[i][4])
         	    	   {
         	    	    state=1;
			    v[i][3]+=v[i][4];
			    //Score+=v[i][3];
			    v[i][4]=0;
         	    	   }
         	    	for(j=2;j<=4;j++)
         	    	    {
         	    	    	int cj=j;
			    	while(v[i][cj-1]==0 && cj>=2)
			    	      {
			    	       if(v[i][cj]!=0)
			    	          state=1;
				       v[i][cj-1]=v[i][cj];
				       v[i][cj]=0;
				       cj--;
			    	      }
         	    	    }
         	    }
         	break;
         }
  //right
  case 4:
         {
         	for(i=1;i<=4;i++)
         	    {
         	     for(j=3;j>=1;j--)
			    {
			    	int cj=j;
			    	while(v[i][cj+1]==0 && cj<=3)
			    	      {
			    	       if(v[i][cj]!=0)
			    	          state=1;
				       v[i][cj+1]=v[i][cj];
				       v[i][cj]=0;
				       cj++;
			    	      }
			    }
			if(v[i][3]==v[i][4])
         	    	   {
         	    	    state=1;
			    v[i][4]+=v[i][3];
			    //Score+=v[i][4];
			    v[i][3]=0;
         	    	   }
         	    	if(v[i][2]==v[i][3])
         	    	   {
         	    	    state=1;
			    v[i][3]+=v[i][2];
			    //Score+=v[i][3];
			    v[i][2]=0;
         	    	   }
         	    	if(v[i][1]==v[i][2])
         	    	   {
         	    	    state=1;
			    v[i][2]+=v[i][1];
			    //Score+=v[i][2];
			    v[i][1]=0;
         	    	   }
         	    	for(j=3;j>=1;j--)
			    {
			    	int cj=j;
			    	while(v[i][cj+1]==0 && cj<=3)
			    	      {
			    	       if(v[i][cj]!=0)
			    	          state=1;
				       v[i][cj+1]=v[i][cj];
				       v[i][cj]=0;
				       cj++;
			    	      }
			    }
         	    }
         	break;
         }
 }
 return state;
}
void load_hiscore()
{
 FILE *save=fopen("highscore.txt","r");
 if(save==NULL)
    {
    	save=fopen("highscore.txt","w");
    	fprintf(save,"0");
     HiScore=0;
    	fclose(save);
    }
 else
    {
    	fscanf(save,"%I64d",&HiScore);
    	fclose(save);
    }
}
void save_hiscore()
{
 FILE *fout=fopen("highscore.txt","w");
 fprintf(fout,"%I64d",HiScore);
 fclose(fout);
}
void print_scores()
{
 image=TTF_RenderText_Solid(font,"Score:",color);
 apply_surface(640,0,image,screen);
 int c=Score,j=0;
 char aux[10],v[10]={0,0,0,0,0,0,0,0,0,0};
 v[0]='0';
 while(c!=0)
	  {
	   j++;
	   aux[j]=c%10;
	   c/=10;
	  }
 while(j>0)
	  {
	   v[c]=aux[j]+'0';
	   j--;
	   c++;
	  }
 image=SDL_LoadBMP("score_clear.bmp");
 apply_surface(640,80,image,screen);
 image=TTF_RenderText_Solid(font,v,color1);
 apply_surface(640,80,image,screen);
 image=TTF_RenderText_Solid(font,"Highscore:",color);
 apply_surface(640,160,image,screen);
 c=HiScore,j=0;
 memset(v,0,10);
 v[0]='0';
 while(c!=0)
	  {
	   j++;
	   aux[j]=c%10;
	   c/=10;
	  }
 while(j>0)
	  {
	   v[c]=aux[j]+'0';
	   j--;
	   c++;
	  }
 image=SDL_LoadBMP("score_clear.bmp");
 apply_surface(640,240,image,screen);
 image=TTF_RenderText_Solid(font,v,color1);
 apply_surface(640,240,image,screen);
 image=TTF_RenderText_Solid(font1,"Undos:",color2);
 apply_surface(640,320,image,screen);
 c=Undo,j=0;
 memset(v,0,10);
 v[0]='0';
 while(c!=0)
	  {
	   j++;
	   aux[j]=c%10;
	   c/=10;
	  }
 while(j>0)
	  {
	   v[c]=aux[j]+'0';
	   j--;
	   c++;
	  }
 image=SDL_LoadBMP("score_clear.bmp");
 apply_surface(640,360,image,screen);
 image=TTF_RenderText_Solid(font1,v,color2);
 apply_surface(640,360,image,screen);
}
void copy_table()
{
 for(int i=1;i<=4;i++)
     for(int j=1;j<=4;j++)
         {
         	table_copy[i][j]=table[i][j];
         }
}
int main(int argc,char* args[])
{
 first:
 int x=0,i=0,j=0,frecv=0,x1=0;
 SDL_Init(SDL_INIT_EVERYTHING);
 TTF_Init();
 font=TTF_OpenFont("font.ttf",80);
 font1=TTF_OpenFont("font.ttf",40);
 load_hiscore();
 screen=SDL_SetVideoMode(1240,640,32,SDL_SWSURFACE);
 srand(time(NULL));
 i=rand()%4+1;
 j=rand()%4+1;
 while(table[i][j]!=0)
	  {
	   i=rand()%4+1;
	   j=rand()%4+1;
	  }
 if(rand()%2==1)
    table[i][j]=4;
 else
    table[i][j]=2;
 i=rand()%4+1;
 j=rand()%4+1;
 while(table[i][j]!=0)
	  {
	   i=rand()%4+1;
	   j=rand()%4+1;
	  }
 if(rand()%2==1)
    table[i][j]=4;
 else
    table[i][j]=2;
 print_table();
 print_scores();
 while(pp==0)
       {
        x=0;
        x1=0;
        pp=keystates[SDLK_ESCAPE];
        up=keystates[SDLK_UP];
        down=keystates[SDLK_DOWN];
        left=keystates[SDLK_LEFT];
        right=keystates[SDLK_RIGHT];
        undo=keystates[SDLK_BACKSPACE];
        if(keystates[SDLK_r]==1)
	      {
	       save_hiscore();
	       SDL_Quit();
	       for(i=1;i<=4;i++)
	           for(j=1;j<=4;j++)
			     table[i][j]=0;
	       Score=0;
	       pp=0;
	       goto first;
	      }
	   if(undo==1 && Undo!=0)
	      {
	       Undo--;
	       print_scores();
            for(int i=1;i<=4;i++)
			 for(int j=1;j<=4;j++)
			     {
				 table[i][j]=table_copy[i][j];
				}
	      }
        if(up==1)
           {
            copy_table();
            move_pieces(1);
		  x=1;
           }
        if(down==1)
           {
            if(x==0)
               copy_table();
		  move_pieces(2);
		  x=1;
           }
        if(left==1)
           {
            if(x==0)
               copy_table();
		  move_pieces(3);
		  x=1;
           }
        if(right==1)
           {
            if(x==0)
               copy_table();
		  move_pieces(4);
		  x=1;
           }
        if(x==1)
           {
            x=0;
            for(int i=1;i<=4;i++)
			 for(int j=1;j<=4;j++)
			     {
				 if(table[i][j]!=table_copy[i][j])
				    {
				    	x=1;
				    }
				}
           }
        print_table();
        for(i=1;i<=4;i++)
            for(j=1;j<=4;j++)
                {
                 if(table[i][j]==0)
                    {
                     x1=1;
                    }
                 if(table[i][j]==2048)
                    x1=2;
                }
        if(x1==0)
           {
            x1+=more_moves(1);
		  x1+=more_moves(2);
		  x1+=more_moves(3);
		  x1+=more_moves(4);
		  if(x1!=0)
		     x1=3;
           }
        if(x==1 && (x1==1 || x1==3))
           {
            if(Score>HiScore)
               {
			 HiScore=Score;
			 if(NewScore==0)
			    {
			     image=TTF_RenderText_Solid(font1,"New Highscore!",color2);
			     apply_surface(640,440,image,screen);
			    }
			 NewScore=1;
               }
            if(x1==1)
               {
			 frecv++;
			 i=rand()%4+1;
			 j=rand()%4+1;
			 while(table[i][j]!=0)
				  {
				   i=rand()%4+1;
				   j=rand()%4+1;
                      }
			 if(frecv%7==0)
			    {
				table[i][j]=4;
				frecv=0;
				image=SDL_LoadBMP("score_clear.bmp");
                    apply_surface(640,440,image,screen);
			    }
			 else
			    table[i][j]=2;
               }
            print_scores();
           }
        if(x1==0)
           pp=2;
        if(x1==2)
           pp=3;
        SDL_Delay(SLEEP);
        SDL_PumpEvents();
       }
 save_hiscore();
 if(pp==2)
    {
    	image=TTF_RenderText_Solid(font1,"You loose!",color1);
	apply_surface(640,420,image,screen);
	image=TTF_RenderText_Solid(font1,"Press R to reset the game!",color1);
	apply_surface(640,500,image,screen);
	SDL_Flip(screen);
	while(keystates[SDLK_RETURN]==0 && keystates[SDLK_r]==0 && keystates[SDLK_ESCAPE]==0)
	      SDL_PumpEvents();
	if(keystates[SDLK_r]==1)
	   {
	    SDL_Quit();
	    for(i=1;i<=4;i++)
	        for(j=1;j<=4;j++)
			  table[i][j]=0;
	    Score=0;
	    pp=0;
	    goto first;
	   }
    }
 if(pp==3)
    {
    	image=TTF_RenderText_Solid(font1,"You win!",color1);
	apply_surface(640,420,image,screen);
     SDL_Flip(screen);
     while(keystates[SDLK_RETURN]==0)
	      SDL_PumpEvents();
    }
 return 0;
}
