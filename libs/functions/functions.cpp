#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <vector>
#include "../globals/globals.h"

void CreateCircle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color clr)
{
  std::vector<SDL_FPoint> points;
  SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
  for (int w = 0; w <= radius * 2; w++)
  {
    for (int h = 0; h <= radius * 2; h++)
    {
      float dx = radius - w; // horizontal offset
      float dy = radius - h; // vertical offset
      if (dx * dx + dy * dy <= radius * radius)
          points.push_back({x + dx, y + dy * sin(worldangle)});
    }
  }
  SDL_RenderPoints(renderer, &points[0], points.size());
  points.clear();

}
