//Using stdio.h and SDL2
#include "Graphics.hh"

//Window size constants
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//SDL requires this type of main so it is compatible with multiple platforms.
int main(int argc, char* args[]) {
  bool quit = false;
  SDL_Event e;
  Graphics g = Graphics(WINDOW_WIDTH, WINDOW_HEIGHT);
  g.drawIMG("test.png");
  while (!quit) {
    while( SDL_PollEvent( &e ) != 0 ) {
      //User requests quit
      if( e.type == SDL_QUIT )
	quit = true;
    }
  }
  return 0;
}

  