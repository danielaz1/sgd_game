//
// Created by daniela on 15.04.19.
//

#ifndef SDLDEMO_PLAYER_H
#define SDLDEMO_PLAYER_H

#include <SDL2/SDL.h>
#include <cmath>
#include "lodepng.h"
#define errcheck(e)                                                            \
  {                                                                            \
    if (e)                                                                     \
      throw std::invalid_argument(SDL_GetError());                             \
  }

class Player {

int start_position_x = 30;
int start_position_y = 400;
float gravity = 9.81;



public:std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer *, std::string);

public:void throwRectangle(int angle, int power, double time, SDL_Renderer *renderer);

private:double toRadians(int angle);
};


#endif //SDLDEMO_PLAYER_H
