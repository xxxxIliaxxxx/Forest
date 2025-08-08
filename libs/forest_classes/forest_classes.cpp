#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include "forest_classes.h"
#include "../globals/globals.h"
#include "../functions/functions.h"





  Flora::Flora(float x, float y)
  {
    x_start_coord = x;
    y_start_coord = y;
  }



  void FirTree::Process()
  {
    Base.w = texture_width * scale;
    Base.h = texture_height * scale;
    Base.x = (x_start_coord + x_offset) * scale + ScWidth * (1 - scale) / 2 - Base.w / 2 ;
    Base.y = (y_start_coord + y_offset) * scale + ScHeight * (1 - scale) / 2 - Base.h * 9 / 10;
    float radius = round(texture_width * 3 / 10) * scale;

    CreateCircle(renderer, Base.x + Base.w / 2, Base.y + Base.h * 9 / 10, radius, green);
  }


  FirTree::FirTree(int x, int y) : Flora(x, y)
  {
    SDL_SetTextureAlphaMod(Texture, 200);
  }

  void FirTree::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr,  &Base);
  }


  void FirTree2::Process()
  {
    Base.w = texture_width * scale;
    Base.h = texture_height * scale;
    Base.x = (x_start_coord + x_offset) * scale + ScWidth * (1 - scale) / 2 - Base.w / 2;
    Base.y = (y_start_coord + y_offset) * scale + ScHeight * (1 - scale) / 2 - Base.h * 9 / 10;
    float radius = round(texture_width * 3 / 10) * scale;

    CreateCircle(renderer, Base.x + Base.w / 2, Base.y + Base.h * 9 / 10, radius, green);
  }


  FirTree2::FirTree2(int x, int y) : Flora(x, y)
  {
    SDL_SetTextureAlphaMod(Texture, 200);
  }

  void FirTree2::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr,  &Base);
  }



  Log::Log(int x, int y): Flora(x, y)
  {
    SDL_SetTextureAlphaMod(Texture, 170);
  }

  void Log::Process()
  {
    Base.w = texture_width * scale;
    Base.h = texture_height * scale;
    Base.x = (x_start_coord + x_offset) * scale + ScWidth * (1 - scale) / 2 - Base.w / 2;;
    Base.y = (y_start_coord + y_offset) * scale + ScHeight * (1 - scale) / 2 - Base.h / 2;;
  }

  void Log::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr, &Base);
  }


  Log2::Log2(int x, int y): Flora(x, y)
  {
    SDL_SetTextureAlphaMod(Texture, 170);
  }

  void Log2::Process()
  {
    Base.w = texture_width * scale;
    Base.h = texture_height * scale;
    Base.x = (x_start_coord + x_offset) * scale + ScWidth * (1 - scale) / 2 - Base.w / 2;;
    Base.y = (y_start_coord + y_offset) * scale + ScHeight * (1 - scale) / 2 - Base.h / 2;;
  }

  void Log2::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr, &Base);
  }


SDL_Texture*  Log:: Texture = IMG_LoadTexture(renderer, "../../graphics/images/log.png" );
SDL_Texture*  Log2:: Texture = IMG_LoadTexture(renderer, "../../graphics/images/log2.png" );
SDL_Texture*  FirTree::Texture = IMG_LoadTexture(renderer, "../../graphics/images/FirTree.png" );
SDL_Texture*  FirTree2::Texture = IMG_LoadTexture(renderer, "../../graphics/images/FirTree2.png" );
