#pragma once


class Flora
{
public:
  float x_start_coord;
  float y_start_coord;

  Flora(float x, float y);
  virtual void Process() = 0;
  virtual void Render_Copy() = 0;
};




class FirTree : public Flora
{
  SDL_FRect Base;
  static const int texture_width = 70;
  static const int texture_height = 120;
public:
  static SDL_Texture* Texture;
  FirTree(int x, int y);
  void Render_Copy();
  void Process();
};


class FirTree2 : public Flora
{
  SDL_FRect Base;
  static const int texture_width = 70;
  static const int texture_height = 120;
public:
  static SDL_Texture* Texture;
  FirTree2(int x, int y);
  void Render_Copy();
  void Process();
};



class Log : public Flora
{
  SDL_FRect Base;
  static const int texture_width = 40;
  static const int texture_height = 20;
public:
  static SDL_Texture* Texture;
  Log(int x, int y);
  void Render_Copy();
  void Process();
};


class Log2 : public Flora
{
  SDL_FRect Base;
  static const int texture_width = 40;
  static const int texture_height = 20;
public:
  static SDL_Texture* Texture;
  Log2(int x, int y);
  void Render_Copy();
  void Process();
};





