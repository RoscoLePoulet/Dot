#pragma once

#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include<stdio.h>
#include<string>

class Graphics {
private:
  //The window                                                               
  SDL_Window* _window = nullptr;
  // The surface contained by the window, it is a 2D image                     
  SDL_Surface* _screenSurface = nullptr;
  //the image we will load and show on the screen
  SDL_Surface* _image = nullptr;
public:
  Graphics(const int &width, const int &height); //Starts SDL & creates a window
  SDL_Surface* loadIMG(const std::string &path); // Loads img onto surface
  void drawIMG(const std::string &path); // Draws img onto the screen
  ~Graphics(); // Frees media and shuts down SDL
};