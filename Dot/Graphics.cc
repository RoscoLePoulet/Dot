#include "Graphics.hh"

Graphics::Graphics(const int &width, const int &height) {
  //Initializes SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //printf = printformat. Use : printf("The string we want to print : %s" (%s = output a string from the variable list) , variable(s));           
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    //SDL.GetError returns the last error produced by a SDL function.
  }
  else {
    //Create window
    this->_window = SDL_CreateWindow("Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (this->_window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else {
      //Initialize PNG loading
      int imgFlags = IMG_INIT_PNG;
       if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
	 printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
       } else {
         //Get surface window
	 this->_screenSurface = SDL_GetWindowSurface(this->_window);
       }
    }
  }
}

SDL_Surface* Graphics::loadIMG(const std::string &path) {
  //Initialization of the new surface
  SDL_Surface* newSurface = nullptr;

  //Load image using its path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if ( loadedSurface == nullptr ) {
    printf("Unable to load image %s ! SDL_image Error: %s/n", path.c_str(), IMG_GetError() );
  }
  else {
    //Convert surface to screen format
    newSurface = SDL_ConvertSurface(loadedSurface, this->_screenSurface->format, NULL);
    if (newSurface == nullptr) {
      printf("Unable to load image %s ! SDL_image Error: %s/n", path.c_str(), IMG_GetError() );
    }
    //Delete old loaded surface
    SDL_FreeSurface(loadedSurface);
  }
  return newSurface;
}

void Graphics::drawIMG(const std::string &path) {
  SDL_BlitSurface( this->loadIMG(path), NULL, this->_screenSurface, NULL);
  SDL_UpdateWindowSurface(this->_window);
}

Graphics::~Graphics() {
  //Deallocates surface
  SDL_FreeSurface(this->_image);
  this->_image = NULL;

  //Destroy window
  SDL_DestroyWindow(this->_window);
  this->_window = NULL;

  //Quit SDL
  SDL_Quit();
}
