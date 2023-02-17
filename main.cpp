#include "raylib.h"

int main()
{
  // Initialization of game constants
  const int window_width{640};
  const int window_height{480};
  const char* game_title{"Mighty dasher"};
  const Color game_background{WHITE};
  const int game_gravity{1'000}; // pixel/sec value
  const int obj_jump_velocity{-600}; // pixel/sec value

  InitWindow(window_width,window_height,game_title);
  SetTargetFPS(120);

  // Define nebula sprites
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebula_rec{0.00, 0.00, static_cast<float>(nebula.width)/8, static_cast<float>(nebula.height)/8};
  Vector2 nebula_pos{window_width, window_height - nebula_rec.height};
  
  int nebula_velocity{-200}; // moving to the left by default
  int nebula_frame{};
  float nebula_running_time{};
  
  // Define nebula sprites 2
  Rectangle nebula2_rec{0.00, 0.00, static_cast<float>(nebula.width)/8, static_cast<float>(nebula.height)/8};
  Vector2 nebula2_pos{window_width + 300, window_height - nebula_rec.height};

  int nebula2_frame{};
  float nebula2_animation_update_time(1.00/16.00);
  float nebula2_running_time{};

  // Define hero sprites
  Texture2D hero = LoadTexture("textures/scarfy.png");
  Rectangle hero_rec{0.00, 0.00, static_cast<float>(hero.width)/6, static_cast<float>(hero.height)};
  Vector2 hero_pos{window_width/2 - hero_rec.width/2, window_height - hero_rec.height};

  int hero_velocity{0};
  bool hero_isInAir{};
  int hero_frame{}; // animation frame
  const float animation_update_time{1.0/12.0}; // how much times animation should be updated per second
  float hero_running_time{};

  while (!WindowShouldClose())
  {
    const float delta_time{GetFrameTime()};

    BeginDrawing();
    ClearBackground(game_background);
    
    if (hero_pos.y >= window_height - hero_rec.height)
    {
      // reset velocity to make object fall to the ground
      hero_velocity = 0;
      hero_pos.y = window_height - hero_rec.height; // help to not stick below surface
      hero_isInAir = false;
    }
    else
    {
      // apply gravity to velocity. > 0 will keep object stay down
      hero_velocity += game_gravity * delta_time; // change game physics to work as pixels per sec insted of frame time, increase accuracy of physics
      hero_isInAir = true; // prevent double jumping of the object
    }
    
    if (!hero_isInAir && IsKeyDown(KEY_SPACE))
    {
      hero_velocity += obj_jump_velocity;
    }

    // Update nebula position
    nebula_pos.x += nebula_velocity * delta_time;
    // Update nebula2 position
    nebula2_pos.x += nebula_velocity * delta_time;
    // Update hero position
    hero_pos.y += hero_velocity * delta_time; // change game physics to work as pixels per sec insted of frame time, increase accuracy of physics
    
    // Update hero animation time
    if (!hero_isInAir)
    {
      hero_running_time += delta_time;
      if (hero_running_time >= animation_update_time)
      {
        hero_running_time = 0.0;
        hero_rec.x = hero_frame * hero_rec.width;
        hero_frame++;
        if (hero_frame > 5)
        {
          hero_frame = 0;
        }
      }
    }

    // Update nebula animation time
    nebula_running_time += delta_time;
    if (nebula_running_time >= animation_update_time)
    {
      nebula_running_time = 0.00;
      nebula_rec.x = nebula_frame * nebula_rec.width;
      nebula_frame++;
      if (nebula_frame > 7)
      {
        nebula_frame = 0;
      }
    }

    // Update nebula2 animation time
    nebula2_running_time += delta_time;
    if (nebula2_running_time >= nebula2_animation_update_time)
    {
      nebula2_running_time = 0.00;
      nebula2_rec.x = nebula2_frame * nebula2_rec.width;
      nebula2_frame++;
      if (nebula2_frame > 7)
      {
        nebula2_frame = 0;
      }
    }
    
    // Draw nebula
    DrawTextureRec(nebula, nebula_rec, nebula_pos, game_background);

    // Draw nebula2
    DrawTextureRec(nebula, nebula2_rec, nebula2_pos, RED);

    // Draw hero
    DrawTextureRec(hero, hero_rec, hero_pos, game_background);

    EndDrawing();
  }
  
  UnloadTexture(hero);
  UnloadTexture(nebula);
  CloseWindow();
}