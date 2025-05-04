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

using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;
using std::cos;


enum directions {stat, up, upright, right, downright, down, downleft, left, upleft};

class PlayerCharacter
{
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
  float radius;
public:

  static directions direction;
  static SDL_Texture* bowmanleft;
  static SDL_Texture* bowmanright;
  static SDL_Texture* bowmandown;
  static SDL_Texture* bowmanup;
  static SDL_Texture* bowmanstatic;

  static float cur_stamina;
  static float max_stamina;
  static float cur_health;
  static float max_health;




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
  }

  float GetRadius()
  {
    return radius;
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

  void Draw_character()
  {
    if (direction == left)
      current = bowmanleft;
    else if (direction == upleft)
    {
      if (chng_texture_dir == false)
        current = bowmanleft;
      else
        current = bowmanup;
    }
    else if (direction == downleft)
    {
      if (chng_texture_dir == false)
        current = bowmanleft;
      else
        current = bowmandown;
    }
    else if (direction == right)
      current = bowmanright;
    else if (direction == upright)
    {
      if (chng_texture_dir == false)
        current = bowmanup;
      else
        current = bowmanright;
    }
    else if (direction == downright)
    {
      if (chng_texture_dir == false)
        current = bowmandown;
      else
        current = bowmanright;
    }
    else if (direction == down)
      current = bowmandown;
    else if (direction == up)
      current = bowmanup;

    if (direction != stat)
      frame++;
    DrawCircle(renderer, ScWidth / 2, ScHeight / 2, radius, gray);
    SDL_RenderTexture(renderer, current, &Clip[frame / int(fps / 4)], &base);

    if (frame >= fps)
    {
      frame = 0;
      chng_texture_dir = !chng_texture_dir;
    }
  }
  
};


class KeyHandler
{
  unordered_map <SDL_Keycode,bool> key;
  SDL_Event event;
  float speed;
  const float walk = 2.5 * std_fps / fps;
  const float sprint = 3.5 * std_fps / fps;

public:

  void Zoom()
  {
    if (event.type == SDL_EVENT_MOUSE_WHEEL)
    {
      if ((event.wheel.y > 0) && (scale <= max_scale)) // Zoom in
      {
        scale += 0.05;
      }
      else if ((event.wheel.y < 0) && (scale >= min_scale)) // Zoom out
      {  
        scale -= 0.05;
      }
    }
  }


  KeyHandler()
  {
    speed = walk;
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


  void MovePlayer()
  {

    if ((PlayerCharacter::direction == stat) 
      && (PlayerCharacter::cur_stamina < PlayerCharacter::max_stamina))
    {  
      PlayerCharacter::cur_stamina += 0.35 * std_fps / fps;
      return;
    }

    if (key[SDLK_LSHIFT] == true)
    {
      if (PlayerCharacter::cur_stamina > 0)
      {
        speed = sprint * scale;
        PlayerCharacter::cur_stamina -= 0.45 * std_fps / fps;
      }
      else
        speed = walk * scale;   
    }
    else
    {
      speed = walk * scale;
      if (PlayerCharacter::cur_stamina < PlayerCharacter::max_stamina)
        PlayerCharacter::cur_stamina += 0.1 * std_fps / fps;
    }

      switch(PlayerCharacter::direction)
      {
        case left:
          x_offset += speed;
          break;
        case right:
          x_offset -= speed;
          break;
        case up:
          y_offset += speed * sin(worldangle);
          break;
        case down:
          y_offset -= speed * sin(worldangle);
          break;
        case downright:
          y_offset -= speed * sin(worldangle) * sin(a_45);
          x_offset -= speed * cos(a_45);
          break;
        case upright:
          y_offset += speed * sin(worldangle) * sin(a_45);
          x_offset -= speed * cos(a_45);
          break;
        case downleft:
          y_offset -= speed * sin(worldangle) * sin(a_45);
          x_offset += speed * cos(a_45);
          break;
        case upleft:
          y_offset += speed * sin(worldangle) * sin(a_45);
          x_offset += speed * cos(a_45);
          break;
      }

    PlayerCharacter::direction = stat;
  } 

  void ProcessKeyEvents()
  {
    if (key[SDLK_ESCAPE])
      exit(0);
    
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
  }
};




directions PlayerCharacter::direction = stat;
float PlayerCharacter::max_stamina = 120;
float PlayerCharacter::cur_stamina = 120;
float PlayerCharacter::max_health = 100;
float PlayerCharacter::cur_health = 100;

SDL_Texture* PlayerCharacter::bowmanleft = IMG_LoadTexture(renderer, "graphics/images/bowmanleft.png" );
SDL_Texture* PlayerCharacter::bowmanright = IMG_LoadTexture(renderer, "graphics/images/bowmanright.png" );
SDL_Texture* PlayerCharacter::bowmandown = IMG_LoadTexture(renderer, "graphics/images/bowmandown.png" );
SDL_Texture* PlayerCharacter::bowmanup = IMG_LoadTexture(renderer, "graphics/images/bowmanup.png" );
SDL_Texture* PlayerCharacter::bowmanstatic = IMG_LoadTexture(renderer, "graphics/images/bowmanstatic.png" );


struct FPS_Controller
{
  std::chrono::time_point<std::chrono::steady_clock> start, end;
  std::chrono::duration<double> wait_time;
  TTF_Text* fps_text;

  void DrawFPS()
  {
    char fps_str[8] = "fps~";
    char fps_num[5];
    sprintf(fps_num, "%d", int(round(fps)));
    strcat(fps_str, fps_num);
    TTF_SetFontSize(my_Font, 18);
    fps_text = TTF_CreateText(text_engine, my_Font, fps_str, 0);
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

    end = std::chrono::steady_clock::now();
    wait_time = end - start;
    std::cout << "Frame interval " << wait_time.count() << "\n";

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



  vector<FirTree> Firvector;
  Firvector.reserve(100);
  Firvector.emplace_back(10, 100);
  Firvector.emplace_back(100, 180);
  Firvector.emplace_back(400, 200);
  Firvector.emplace_back(45, 500);
  Firvector.emplace_back(75, 300);
  Firvector.emplace_back(210, 100);
  Firvector.emplace_back(310, 150);
  Firvector.emplace_back(420, 300);
  Firvector.emplace_back(620, 310);
  Firvector.emplace_back(660, 280);
  Firvector.emplace_back(1000, 280);
  Firvector.emplace_back(900, 580);
  Firvector.emplace_back(520, 780);
  Firvector.emplace_back(200, 930);
  Firvector.emplace_back(700, 880);
  Firvector.emplace_back(1600, 1080);
  Firvector.emplace_back(1740, 850);
  Firvector.emplace_back(-100, -100);
  Firvector.emplace_back(-200, -70);
  Firvector.emplace_back(-270, -170);
  Firvector.emplace_back(-270, 570);
  Firvector.emplace_back(-290, -570);
  Firvector.emplace_back(1000, -530);
  Firvector.emplace_back(110, -230);
  Firvector.emplace_back(990, -170);
  Firvector.emplace_back(860, -230);
  Firvector.emplace_back(910, 430);
  Firvector.emplace_back(610, -145);


  vector<Log> Logvector;
  Logvector.emplace_back(450, 160);
  Logvector.emplace_back(480, 90);
  Logvector.emplace_back(250, 280);
  Logvector.emplace_back(30, 60);
  Logvector.emplace_back(50, 470);
  Logvector.emplace_back(505, 60);
  Logvector.emplace_back(80, 810);
  Logvector.emplace_back(50, 360);
  Logvector.emplace_back(350, 160);
  Logvector.emplace_back(70, 110);
  Logvector.emplace_back(770, 310);

  vector<Log2> Logvector2;
  Logvector2.emplace_back(140, 160);
  Logvector2.emplace_back(280, 90);
  Logvector2.emplace_back(20, 280);
  Logvector2.emplace_back(300, 60);
  Logvector2.emplace_back(145, 450);
  Logvector2.emplace_back(300, 60);
  Logvector2.emplace_back(185, 650);
  Logvector2.emplace_back(485, 670);
  Logvector2.emplace_back(-50, -150);

  while(1)
  {
    FPS_Controller fpsc;
    SDL_RenderClear(renderer);

    KeyHandlerMain.GetKeyEvents();
    KeyHandlerMain.MovePlayer();
    KeyHandlerMain.ProcessKeyEvents();
    KeyHandlerMain.Zoom();


    for (int i = 0; i < Logvector.size(); i++)
    {
      Logvector[i].Move();
      Logvector[i].Render_Copy();
    }
    for (int i = 0; i < Logvector2.size(); i++)
    {
      Logvector2[i].Move();
      Logvector2[i].Render_Copy();
    }
    Player.Zoom();
    Player.Draw_character();
    for (int i = 0; i < Firvector.size(); i++)
    {
      Firvector[i].Move();
      Firvector[i].Render_Copy(); 
    }
    
    Player.Draw_stamina_bar();
    Player.Draw_health_bar();
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
