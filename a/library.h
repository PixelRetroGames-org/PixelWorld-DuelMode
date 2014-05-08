#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include<string>
#include<cstdio>
#include<ctime>
void get_string_input(char *s,int &lenght)
{
 if(event.key.keysym.unicode==(Uint16)' ')
    {
	//Append the character
	lenght++;
	s[lenght]=(char)event.key.keysym.unicode;
    }
 else
    if((event.key.keysym.unicode>=(Uint16)'0') && (event.key.keysym.unicode<=(Uint16)'9'))
	  {
	   //Append the character
	   lenght++;
	   s[lenght]=(char)event.key.keysym.unicode;
	  }
 if(event.key.keysym.unicode!=(Uint16)'\n')
    get_string_input(s,lenght);
 else
    return;
}
