CC = g++
CFLAGS = -ggdb -Wall
CPPFLAGS = -I/usr/include/SDL2
OBJS = AnimacaoPOC.cpp AnimacaoPOCException.cpp main.cpp Ninja.cpp SpriteSheet.cpp stdafx.cpp 
LDFLAGS = -lSDL2 -lSDL2_image

all: catninja

# --------------
# Binary
# --------------

catninja: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o catninja $(OBJS) $(LDFLAGS)
    
# --------------
# Clean
# --------------

clean:
	$(RM) *.o catninja

