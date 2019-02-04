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
  //Current displayed texture
  SDL_Texture* _texture = nullptr;
  //Window renderer
  SDL_Renderer* _renderer = NULL;
  
public:
  Graphics(const int &width, const int &height); //Starts SDL & creates a window
  SDL_Surface* loadIMG(const std::string &path); // Loads img onto surface
  void drawIMG(const std::string &path); // Draws img onto the screen
  void drawTexture(const std::string &path);
  SDL_Texture* loadTexture(const std::string &path);
  void updateScreen();
  ~Graphics(); // Frees media and shuts down SDL
};
