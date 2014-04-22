LFLAGS=-L/Library/Frameworks/SDL_image.framework/ -lSDL2 -lSDL_image
CFLAGS=-Wall -g -I/Library/Frameworks/SDL2.framework/Headers/  -I/Library/Frameworks/SDL_image.framework/Headers/ 

Play_RotW:	main.cxx graphics.o
	#g++ $(CFLAGS) $(LFLAGS)  -o $@

graphics.o: main.cxx /tmp/
	echo $^