//
// Created by daniela on 15.04.19.
//

#ifndef STRIKER_PLAYER_H
#define STRIKER_PLAYER_H

#include <SDL2/SDL.h>
#include <cmath>
#include "lodepng.h"
#include "GameConstants.h"
#include <memory>
#include <vector>
#include "Obstacle.h"
#include "ObstacleGenerator.h"

#define TIME_INTERVAL 0.05
#define errcheck(e)                                                            \
  {                                                                            \
    if (e)                                                                     \
      throw std::invalid_argument(SDL_GetError());                             \
  }

class Player {

    int counter = 0;
    int distance_x = GameConstants::PLAYER_MIN_X;
    int distance_y = GameConstants::PLAYER_MIN_Y;
    float gravity = 9.81;
    float time = 0;
    float powerFactor = 0;


public:
    std::shared_ptr<SDL_Texture> loadTexture(SDL_Renderer *, std::string);

public:
    int throwRectangle(int angle, double power, SDL_Renderer *renderer, ObstacleGenerator *);
    float increaseTime();

private:
    double toRadians(int angle);
    int calculateX(int angle, double power, int);
    int calculateY(int angle, double power, int);

    void calculateCollision(int x, int distance);
};


#endif //STRIKER_PLAYER_H
