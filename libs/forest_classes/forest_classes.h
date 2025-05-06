#pragma once

class FirTree
{
  SDL_FRect Base;
  static const int texture_width = 70;
  static const int texture_height = 120;
  static const int base_radius = round(texture_width * 3 / 10);

  float x_world_coord;
  float y_world_coord;
  float radius;
  float centre_x;
  float centre_y;

public:
  static SDL_Texture* Texture;


  FirTree(int x, int y);
  FirTree (const FirTree & f);
  void Move();
  void Render_Copy();
};


class Log
{
  SDL_FRect Base;
  static const int texture_width = 40;
  static const int texture_height = 20;
  float x_world_coord;
  float y_world_coord;

public:
  static SDL_Texture* Texture;
  Log(int x, int y);
  void Move();
  void Render_Copy();
};


class Log2
{
  SDL_FRect Base;
  static const int texture_width = 40;
  static const int texture_height = 20;
  float x_world_coord;
  float y_world_coord;

public:
  static SDL_Texture* Texture;
  Log2(int x, int y);
  void Move();
  void Render_Copy();
};




