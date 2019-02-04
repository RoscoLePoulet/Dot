#include "Graphics.hh"

Graphics::Graphics(const int &width, const int &height) {
  //Initializes SDL
  if (SDL_Init(SDL_INIT_VIDEO)<0) {
    //printf = printformat. Use : printf("The string we want to print : %s" (%s = output a string from the variable list) , variable(s));           
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    //SDL.GetError returns the last error produced by a SDL function.
  }
  else {
    //Create window
    _window = SDL_CreateWindow("Dot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (_window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else {
      //Create the renderer for the window
      _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED);
	if(_renderer == nullptr){
	  printf("Renderer could not be created! SDL Error : %s\n", SDL_GetError());
	}
	else {
	  //Initialize renderer color
	  SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);	  
	  //Initialize PNG loading
	  int imgFlags = IMG_INIT_PNG;
	  if(!(IMG_Init(imgFlags)&imgFlags)) {
	    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	  }
	  else {
	    //Get surface window
	    _screenSurface = SDL_GetWindowSurface(_window);
	  }
	}
    }
  }
}

SDL_Texture* Graphics::loadTexture (const std::string &path) {
  //Initialization of the new texture
  SDL_Texture* newTexture = nullptr;
  //Load the image
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s ! SDL_image Error: %s/n", path.c_str(), IMG_GetError());
  }
  else {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(_renderer,loadedSurface);
    if(newTexture == nullptr) {
      printf("Unable to load image %s ! SDL_Image Error : %s\n", path.c_str(), IMG_GetError());
    }
    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
}

SDL_Surface* Graphics::loadIMG(const std::string &path) {
  //Initialization of the new surface
  SDL_Surface* newSurface = nullptr;

  //Load image using its path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == nullptr) {
    printf("Unable to load image %s ! SDL_image Error: %s/n", path.c_str(), IMG_GetError());
  }
  else {
    //Convert surface to screen format
    newSurface = SDL_ConvertSurface(loadedSurface,  _screenSurface->format, NULL);
    if (newSurface == nullptr) {
      printf("Unable to load image %s ! SDL_image Error: %s/n", path.c_str(), IMG_GetError());
    }
    //Delete old loaded surface
    SDL_FreeSurface(loadedSurface);
  }
  return newSurface;
}

void Graphics::drawIMG(const std::string &path){
  SDL_BlitSurface(loadIMG(path), NULL, _screenSurface, NULL);
  SDL_UpdateWindowSurface(_window);
}

void Graphics::drawTexture(const std::string &path){
  _texture = loadTexture(path);
  if(_texture == nullptr){
    printf("Failed to load texture image!\n");
  }
}

void Graphics::updateScreen() {
  //Clear screen
  SDL_RenderClear(_renderer);
  
  //Render texture to screen
  SDL_RenderCopy(_renderer, _texture, NULL, NULL);
  
  //Update screen
  SDL_RenderPresent(_renderer); 
}

Graphics::~Graphics() {
  //Deallocates surface
  SDL_FreeSurface(_image);
  _image = NULL;
  SDL_DestroyTexture(_texture);
  _texture = NULL;

  //Destroy window
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow( _window);
  _window = NULL;
  _renderer = NULL;

  //Quit SDL
  IMG_Quit();
  SDL_Quit();
}
