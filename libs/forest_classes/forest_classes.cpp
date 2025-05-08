#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include "forest_classes.h"
#include "../globals/globals.h"
#include "../functions/functions.h"



  FirTree::FirTree(int x, int y)
  {

    x_world_coord = x;
    y_world_coord = y;
    Base.x = (x_world_coord - texture_width / 2) * scale;
    Base.y = (y_world_coord - texture_height / 2) * scale;
    Base.w = texture_width * scale;
    Base.h = texture_height * scale;
    SDL_SetTextureAlphaMod(Texture, 180);
    centre_x = Base.x + Base.w / 2;
    centre_y = Base.y + Base.h * 9 / 10;
    radius = base_radius * scale;
  }


  FirTree::FirTree (const FirTree & f)
  {
    x_world_coord = f.x_world_coord;
    y_world_coord = f.y_world_coord;
    Base.x = (f.x_world_coord - f.texture_width / 2) * scale;
    Base.y = (f.y_world_coord - f.texture_height / 2) * scale;
    Base.w = f.texture_width * scale;
    Base.h = f.texture_height * scale;
    centre_x = f.Base.x + f.Base.w / 2;
    centre_y = f.Base.y + f.Base.h * 9 / 10;
    radius = f.base_radius * scale;
    std::cout << "copy" << std::endl;
  }





  void FirTree::Move()
  {
    Base.w = texture_width * scale;
    Base.h = texture_height * scale; 
    Base.x = (x_world_coord  + x_offset - ScWidth / 2) * scale - Base.w / 2 + ScWidth / 2;
    Base.y = (y_world_coord + y_offset - ScHeight / 2) * scale - Base.h / 2 + ScHeight / 2;
    centre_x = Base.x + Base.w / 2;
    centre_y = Base.y + Base.h * 9 / 10;
    radius = base_radius * scale;

    //CreateCircle(renderer, centre_x, centre_y, radius, green);
  }

  void FirTree::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr, &Base);
  }



  Log::Log(int x, int y): x_world_coord(x), y_world_coord(y),
    Base{int(round((x_world_coord - texture_width / 2) * scale)),
         int(round((y_world_coord - texture_height / 2) * scale)),
         int(round(texture_width * scale)),
         int(round(texture_height * scale))}
  {
    SDL_SetTextureAlphaMod(Texture, 170);
  }

  void Log::Move()
  {
    Base.w = round(texture_width * scale);
    Base.h = round(texture_height * scale); 
    Base.x = round((x_world_coord  + x_offset - ScWidth / 2) * scale - Base.w / 2 + ScWidth / 2);
    Base.y = round((y_world_coord + y_offset - ScHeight / 2) * scale - Base.h / 2 + ScHeight / 2);
  }

  void Log::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr, &Base);
  }


  Log2::Log2(int x, int y): x_world_coord(x), y_world_coord(y),
    Base{int(round((x_world_coord - texture_width / 2) * scale)),
         int(round((y_world_coord - texture_height / 2) * scale)),
         int(round(texture_width * scale)),
         int(round(texture_height * scale))}
  {
    SDL_SetTextureAlphaMod(Texture, 170);
  }

  void Log2::Move()
  {
    Base.w = round(texture_width * scale);
    Base.h = round(texture_height * scale); 
    Base.x = round((x_world_coord  + x_offset - ScWidth / 2) * scale - Base.w / 2 + ScWidth / 2);
    Base.y = round((y_world_coord + y_offset - ScHeight / 2) * scale - Base.h / 2 + ScHeight / 2);
  }

  void Log2::Render_Copy()
  {
    SDL_RenderTexture(renderer, Texture, nullptr, &Base);
  }


SDL_Texture*  Log:: Texture = IMG_LoadTexture(renderer, "../../graphics/images/log.png" );
SDL_Texture*  Log2:: Texture = IMG_LoadTexture(renderer, "../../graphics/images/log2.png" );
SDL_Texture*  FirTree::Texture = IMG_LoadTexture(renderer, "../../graphics/images/FirTree.png" );
