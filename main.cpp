#include <iostream>
#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "libs/globals/globals.h"
#include "libs/functions/functions.h"
#include "libs/forest_classes/forest_classes.h"
#include <chrono>
#include <thread>
#include <string>
#include <random>
#include <algorithm>
using std::cout;
using std::endl;
using std::unordered_map;
using std::cos;

enum directions {stat, up, upright, right, downright, down, downleft, left, upleft};

class PlayerCharacter
{
  float speed;
  const float walk = 1.8 * std_fps / fps;
  const float sprint = 2.6 * std_fps / fps;
  const int texture_width = 45;
  const int texture_height = 60;
  const int centre_x = ScWidth / 2;
  const int centre_y = ScHeight / 2;
  const int base_radius = texture_width * 3 / 10;
  
  int frame = 0;
  SDL_FRect Clip[4];
  SDL_FRect base;
  SDL_FRect stamina_bar;
  SDL_FRect cur_stamina_bar;
  SDL_FRect health_bar;
  SDL_FRect cur_health_bar;
  SDL_Texture* current;
  bool chng_texture_dir;
  float max_stamina = 120;
  float cur_stamina = 120;
  float max_health = 100;
  float cur_health = 100;

public:
  float radius;
  static bool run;
  static directions direction;
  static SDL_Texture* bowmanleft;
  static SDL_Texture* bowmanright;
  static SDL_Texture* bowmandown;
  static SDL_Texture* bowmanup;
  static SDL_Texture* bowmanstatic;





  PlayerCharacter()
  {
    for (int i = 0; i < 4; i++)
    {  
      Clip[i].x = texture_width * i;
      Clip[i].y = 0;
      Clip[i].w = scale * texture_width;
      Clip[i].h = scale * texture_height;
    }
    radius = base_radius * scale;
    current = bowmanright;
    base.x = (ScWidth / 2 - texture_width / 2) * scale;
    base.y = (ScHeight / 2 - texture_height * 9 / 10) * scale;
    base.w = texture_width * scale;
    base.h = texture_height * scale;

    stamina_bar.x = 10;
    stamina_bar.y = 40;
    stamina_bar.w = 200;
    stamina_bar.h = 20;
    cur_stamina_bar = stamina_bar;

    health_bar.x = 10;
    health_bar.y = 10;
    health_bar.w = 250;
    health_bar.h = 25;
    cur_health_bar = health_bar;

    SDL_SetTextureAlphaMod(bowmanright, 200);
    SDL_SetTextureAlphaMod(bowmanleft, 200);
    SDL_SetTextureAlphaMod(bowmanup, 200);
    SDL_SetTextureAlphaMod(bowmandown, 200);
    chng_texture_dir = false;

    speed = walk;
  }

  void Zoom()
  {
    radius = base_radius * scale;
    base.x = ScWidth / 2 - base.w / 2;
    base.y = ScHeight / 2 - base.h * 9 / 10;

    base.w = texture_width * scale;
    base.h = texture_height * scale;
  }

  void Draw_health_bar()
  {
    SDL_SetRenderDrawColor(renderer, 255, 75, 75, 200);
    cur_health_bar.w = health_bar.w * float(cur_health / max_health);
    SDL_RenderRect(renderer, &cur_health_bar);
    SDL_RenderRect(renderer, &health_bar);
    SDL_RenderFillRect(renderer, &cur_health_bar);
  }

  void Draw_stamina_bar()
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
    cur_stamina_bar.w = stamina_bar.w * float(cur_stamina / max_stamina);
    SDL_RenderRect(renderer, &cur_stamina_bar);
    SDL_RenderRect(renderer, &stamina_bar);
    SDL_RenderFillRect(renderer, &cur_stamina_bar);
  }


  void DrawZoom()
  {
    char scale_str[7] = "x ";
    char scale_num[5];
    sprintf(scale_num, "%.2f", scale);
    strcat(scale_str, scale_num);
    TTF_SetFontSize(my_Font, 20);
    TTF_Text* fps_text = TTF_CreateText(text_engine, my_Font, scale_str, 0);
    TTF_SetTextColor(fps_text, 255, 255, 0, 200);
    TTF_DrawRendererText(fps_text, ScWidth - 75, 20);
  }

  void MovePlayer()
  {

    if ((direction == stat) && (cur_stamina < max_stamina))
    {
      cur_stamina += 0.35 * std_fps / fps;
    }

    if (run)
    {
      if (cur_stamina > 0)
      {
        speed = sprint * scale;
        cur_stamina -= 0.45 * std_fps / fps;
      }
      else
        speed = walk * scale;
    }
    else
    {
      speed = walk * scale;
      if (cur_stamina < max_stamina)
        cur_stamina += 0.1 * std_fps / fps;
    }

    if (frame >= fps)
    {
      frame = 0;
      chng_texture_dir = !chng_texture_dir;
    }

    switch(direction)
    {
    case left:
      current = bowmanleft;
      x_offset += speed;
      break;
    case right:
      current = bowmanright;
      x_offset -= speed;
      break;
    case up:
      current = bowmanup;
      y_offset += speed * sin(worldangle);
      break;
    case down:
      current = bowmandown;
      y_offset -= speed * sin(worldangle);
      break;
    case downright:
      y_offset -= speed * sin(worldangle) * sin(a_45);
      x_offset -= speed * cos(a_45);
      current = (!chng_texture_dir) ? bowmandown : bowmanright;
      break;
    case upright:
      y_offset += speed * sin(worldangle) * sin(a_45);
      x_offset -= speed * cos(a_45);
      current = (!chng_texture_dir) ? bowmanup : bowmanright;
      break;
    case downleft:
      y_offset -= speed * sin(worldangle) * sin(a_45);
      x_offset += speed * cos(a_45);
      current = (!chng_texture_dir) ? bowmandown : bowmanleft;
      break;
    case upleft:
      y_offset += speed * sin(worldangle) * sin(a_45);
      x_offset += speed * cos(a_45);
      current = (!chng_texture_dir) ? bowmanleft : bowmanup;
    };

    if (direction != stat)
      frame++;

    CreateCircle(renderer, ScWidth / 2, ScHeight / 2, radius, gray);
    SDL_RenderTexture(renderer, current, &Clip[frame / int(fps / 4)], &base);

  }


  
};


class KeyHandler
{
  unordered_map <SDL_Keycode,bool> key;
  SDL_Event event;

public:

  void Zoom()
  {
    if (event.type == SDL_EVENT_MOUSE_WHEEL)
    {
      if ((event.wheel.y > 0) && (scale <= max_scale)) // Zoom in
      {
        scale += 0.03;
      }
      else if ((event.wheel.y < 0) && (scale >= min_scale)) // Zoom out
      {  
        scale -= 0.03;
      }
    }
  }



  KeyHandler()
  {
    key[SDLK_W] = 0;
    key[SDLK_A] = 0;
    key[SDLK_S] = 0;
    key[SDLK_D] = 0;
    key[SDLK_UP] = 0;
    key[SDLK_DOWN] = 0;
    key[SDLK_LEFT] = 0;
    key[SDLK_RIGHT] = 0;
    key[SDLK_ESCAPE] = 0;
    key[SDLK_LSHIFT] = 0;
  }

  void GetKeyEvents()
  {
    SDL_PollEvent(&event);
    for (auto it = key.begin(); it != key.end(); it++)
    {
      if (event.key.key == it->first)
      {
        if (event.type == SDL_EVENT_KEY_DOWN) 
          it->second = true;
        else if(event.type == SDL_EVENT_KEY_UP) 
          it->second = false;        
      }
    }
  };




  void ProcessKeyEvents()
  {
    if (key[SDLK_ESCAPE])
      exit(0);

    if (key[SDLK_LSHIFT])
      PlayerCharacter::run = true;
    else
      PlayerCharacter::run = false;
    
    if ((key[SDLK_W] || key[SDLK_UP]) && (key[SDLK_A] || key[SDLK_LEFT]))
    {
      PlayerCharacter::direction = upleft;
    }
    else if ((key[SDLK_W] || key[SDLK_UP]) && (key[SDLK_D] || key[SDLK_RIGHT]))
    {
      PlayerCharacter::direction = upright;
    }
    else if ((key[SDLK_S] || key[SDLK_DOWN]) && (key[SDLK_A] || key[SDLK_LEFT]))
    {
      PlayerCharacter::direction = downleft;
    }
    else if ((key[SDLK_S] || key[SDLK_DOWN]) && (key[SDLK_D] || key[SDLK_RIGHT]))
    {
      PlayerCharacter::direction = downright;
    }
    else if (key[SDLK_W] || key[SDLK_UP])
    {
      PlayerCharacter::direction = up;
    }
    else if (key[SDLK_S] || key[SDLK_DOWN])
    {
      PlayerCharacter::direction = down;
    }
    else if (key[SDLK_A] || key[SDLK_LEFT])
    {
      PlayerCharacter::direction = left;
    }
    else if (key[SDLK_D] || key[SDLK_RIGHT])
    {
      PlayerCharacter::direction = right;
    }
    else
      PlayerCharacter::direction = stat;
  }
};

bool PlayerCharacter::run = false;
directions PlayerCharacter::direction = stat;
SDL_Texture* PlayerCharacter::bowmanleft = IMG_LoadTexture(renderer, "graphics/images/bowmanleft.png" );
SDL_Texture* PlayerCharacter::bowmanright = IMG_LoadTexture(renderer, "graphics/images/bowmanright.png" );
SDL_Texture* PlayerCharacter::bowmandown = IMG_LoadTexture(renderer, "graphics/images/bowmandown.png" );
SDL_Texture* PlayerCharacter::bowmanup = IMG_LoadTexture(renderer, "graphics/images/bowmanup.png" );
SDL_Texture* PlayerCharacter::bowmanstatic = IMG_LoadTexture(renderer, "graphics/images/bowmanstatic.png" );


struct FPS_Controller
{
  std::chrono::time_point<std::chrono::steady_clock> start, end;
  std::chrono::duration<double> wait_time;


  void DrawFPS()
  {
    char fps_str[8] = "fps ";
    char fps_num[5];
    sprintf(fps_num, "%d", int(round(fps)));
    strcat(fps_str, fps_num);
    TTF_SetFontSize(my_Font, 20);
    TTF_Text* fps_text = TTF_CreateText(text_engine, my_Font, fps_str, 0);
    TTF_SetTextColor(fps_text, 255, 255, 0, 200);
    TTF_DrawRendererText(fps_text, ScWidth - 75, 5);

  }

  FPS_Controller() : start(std::chrono::steady_clock::now())
  {
  }

  ~FPS_Controller()
  {
    end = std::chrono::steady_clock::now();
    wait_time = end - start;


    if( (1.0 / fps > wait_time.count()))
    {
      /*
      do
      {
        wait_time = std::chrono::steady_clock::now() - start;
      }
      while(wait_time.count() < 1.0 / fps);
      */
      std::this_thread::sleep_for(std::chrono::duration<double>(1.0 / fps) - wait_time);
      fps = std_fps;
    }
    else
      fps = 1.0 / wait_time.count();
  }
};

int main(int argc, char *argv[])
{
  SDL_GetCurrentRenderOutputSize(renderer, &ScWidth, &ScHeight);
  
  ///////////////////////////////////Initializing SDL//////////////////////////
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); 

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
      SDL_GetError());
    return 3;
  }

  ////////////////////////////Initializing SDL_TTF/////////////////////////////
  if (TTF_Init() == -1)
    cout << "Could not initialize SDL3_ttf, error:" << SDL_GetError() << "\n";
  else
    cout << "SDL3_ttf system ready to go!";

  my_Font = TTF_OpenFont("graphics/fonts/DroidSans.ttf", 32);
  if (my_Font == nullptr)
  {
    cout << "could not load font\n";
    exit(1);
  }

  ///////////////////////////////Main cycle////////////////////////////////////

  KeyHandler KeyHandlerMain;
  PlayerCharacter Player;
  x_offset = ScWidth / 2;
  y_offset = ScHeight / 2;

  std::vector<std::unique_ptr<Flora>> Forest;
  Forest.reserve(300);

  std::random_device rd;  // obtain a seed from the OS
  std::mt19937 gen(rd()); // Standard Mersenne Twister engine
  std::uniform_int_distribution<> distrib(-800, 800);
  std::uniform_int_distribution<> Flora_type(0, 3);


  for (int i = 0; i < 150; ++i)
  {
    switch(Flora_type(gen))
    {
    case 0:
      Forest.push_back(std::make_unique<FirTree>(distrib(gen), distrib(gen)));
      break;
    case 1:
      Forest.push_back(std::make_unique<FirTree2>(distrib(gen), distrib(gen)));
      break;
    case 2:
      Forest.push_back(std::make_unique<Log>(distrib(gen), distrib(gen)));
      break;
    case 3:
      Forest.push_back(std::make_unique<Log2>(distrib(gen), distrib(gen)));
      break;
    }
  }
  std::sort(Forest.begin(), Forest.end(),
            [](std::unique_ptr<Flora>& one, std::unique_ptr<Flora>& two) { return one->y_start_coord < two->y_start_coord; });

  while(1)
  {
    FPS_Controller fpsc;
    SDL_RenderClear(renderer);

    KeyHandlerMain.GetKeyEvents();
    KeyHandlerMain.ProcessKeyEvents();
    KeyHandlerMain.Zoom();

    Player.Zoom();

    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<double> wait_time;
    start = std::chrono::steady_clock::now();

    for (int i = 0; i < Forest.size(); i++)
    {
      Forest[i]->Process();
      Forest[i]->Render_Copy();
    }
    end = std::chrono::steady_clock::now();
    wait_time = end - start;
    cout << wait_time.count() << std::endl;

    Player.MovePlayer();
    Player.Draw_stamina_bar();
    Player.Draw_health_bar();
    Player.DrawZoom();
    fpsc.DrawFPS();
    SDL_SetRenderDrawColor(renderer, 7, 180, 95, 100);
    SDL_RenderPresent(renderer);
  }
  ////////////////////////Exiting program//////////////////////////////////////
  TTF_CloseFont(my_Font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
