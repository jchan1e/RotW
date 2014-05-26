/*
************************************************
***		MAIN LOOP AND INPUT RECOGNITION		***
************************************************

Initializes stu1a and is the overarching structure for the everything

Compile with the following command:
g++ -I/Library/Frameworks/SDL2.framework/Headers/ -L /Library/Frameworks/SDL2.framework/ -l SDL2 -Wall -g main.cxx -o Play_RotW

*/

#include <cstdlib>
#include <string>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

bool init();			//Starts up SDL and creates window
bool loadMedia();		//Loads media
void close();			//Frees media and shuts down SDL
SDL_Surface* loadSurface( std::string path ); 	//Loads a single image

//Key press surfaces constants
enum KeyPressSurface
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 256;
SDL_Window* gWindow = NULL;				//The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL;		//The surface contained by the window
SDL_Surface* gCurrentSurface = NULL;		//Currently displayed image
SDL_Surface* gKeyPressSurface [KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gBackground = NULL;			//The background image


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
			SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );
			//main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ];

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
						quit = true;
					else if (e.type == SDL_KEYDOWN)
					{
					//	SDL_Rect rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
					//	SDL_FillRect(gCurrentSurface, &rect, SDL_MapRGB(gCurrentSurface->format, 0x00, 0x00, 0x00));
						switch (e.key.keysym.sym)
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_DOWN ];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_RIGHT ];
							break;

							default:
							gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
						}
					}
					else if (e.type == SDL_KEYUP)
					{
					//	SDL_Rect rect = {0,0,256,256};
					//	SDL_FillRect(gCurrentSurface, &rect, SDL_MapRGB(gCurrentSurface->format, 0x00, 0x00, 0x00));
						gCurrentSurface = gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ];
					}
				}
				//Apply the image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
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
		  gWindow = SDL_CreateWindow( "Move the Cat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
/*	gBackground = IMG_Load( "Assets/Backgrounds/Gradient.png" );
	if( gBackground == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "Assets/Backgrounds/Gradient.png", SDL_GetError() );
		success = false;
	} */
	 //Load default surface
	gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "assets/sprites/cat_mid.png" );
	if( gKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

    //Load up surface
	gKeyPressSurface[ KEY_PRESS_SURFACE_UP ] = loadSurface( "assets/sprites/cat_up.png" );
	if( gKeyPressSurface[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load up image!\n" );
		success = false;
	}

    //Load down surface
	gKeyPressSurface[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "assets/sprites/cat_down.png" );
	if( gKeyPressSurface[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load down image!\n" );
		success = false;
	}

    //Load left surface
	gKeyPressSurface[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "assets/sprites/cat_left.png" );
	if( gKeyPressSurface[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

    //Load right surface
	gKeyPressSurface[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "assets/sprites/cat_right.png" );
	if( gKeyPressSurface[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}

SDL_Surface* loadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
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

