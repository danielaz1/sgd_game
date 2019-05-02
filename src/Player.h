//
// Created by daniela on 15.04.19.
//

#ifndef SDLDEMO_PLAYER_H
#define SDLDEMO_PLAYER_H

#include <SDL2/SDL.h>
#include <cmath>
#include "lodepng.h"
#include "GameConstants.h"

#define TIME_INTERVAL 0.03
#define errcheck(e)                                                            \
  {                                                                            \
    if (e)                                                                     \
      throw std::invalid_argument(SDL_GetError());                             \
  }

class Player {

    int counter = 0;
    int distance_x = GameConstants::PLAYER_MIN_X;
    float gravity = 9.81;
    float time;


public:
    std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer *, std::string);

public:
    int throwRectangle(int angle, double power, SDL_Renderer *renderer);
    float increaseTime();

private:
    double toRadians(int angle);
    int calculateX(int angle, double power, int);
    int calculateY(int angle, double power, int);
};


#endif //SDLDEMO_PLAYER_H
