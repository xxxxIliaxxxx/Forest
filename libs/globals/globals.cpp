#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include "globals.h"




float std_fps = 60;
float fps = 60;
SDL_Window *window = SDL_CreateWindow("Forest", 500, 500, SDL_WINDOW_FULLSCREEN);
SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
TTF_TextEngine *text_engine = TTF_CreateRendererTextEngine(renderer);
TTF_Font* my_Font;
int ScWidth;
int ScHeight;
float x_offset = 0;
float y_offset = 0;
float worldangle = M_PI * 4 / 5;
float a_45 = M_PI / 4;          
float scale = 1;                        
const float max_scale = 1.5;
const float min_scale = 0.5;
const SDL_Color gray = {65, 90, 65, 250};
const SDL_Color green = {90, 255, 110, 250};
