LFLAGS=-L/opt/local/lib/ -lSDL2 -lSDL2_image
CFLAGS=-Wall -g -I/opt/local/include/SDL2/

all: Play_RotW

Play_RotW:	main.cxx
	g++ $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	rm -r Play_RotW Play_RotW.dSYM
