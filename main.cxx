/*
************************************************
***		MAIN LOOP AND INPUT RECOGNITION		***
************************************************

Initializes stu1a and is the overarching structure for the everything

Compile with the following command:
g++ -I/Library/Frameworks/SDL2.framework/Headers/ -L /Library/Frameworks/SDL2.framework/ -l SDL2 -Wall -g main.cxx -o Play_RotW

*/

#include <cstdlib>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

bool init();			//Starts up SDL and creates window
bool loadMedia();		//Loads media
void close();			//Frees media and shuts down SDL

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;				//The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;		//The surface contained by the window
SDL_Surface* gBackground = NULL;			//The image we will load and show on the screen

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );
			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}

   //Free resources and close SDL
	close();

	return 0;

/*	
	draw menu background

	menu_loop
	{

	}

	draw game screen

	event_loop
	{

	}*/

}

bool init()
{
	 //Initialization flag
	 bool success = true;

	 //Initialize SDL
	 if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	 {
		  printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		  success = false;
	 }
	 else
	 {
		  //Create window
		  gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		  if( gWindow == NULL )
		  {
				printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				success = false;
		  }
		  else
		  {
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
		  }
	 }

	 return success;
}

bool loadMedia()
{
	 //Loading success flag
	 bool success = true;

	 //Load splash image
	 gBackground = IMG_Load( "Backgrounds/Gradient.png" );
	 if( gBackground == NULL )
	 {
		  printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		  success = false;
	 }

	 return success;
}

void close()
{
	 //Deallocate surface
	 SDL_FreeSurface( gBackground );
	 gBackground = NULL;

	 //Destroy window
	 SDL_DestroyWindow( gWindow );
	 gWindow = NULL;

	 //Quit SDL subsystems
	 SDL_Quit();
}