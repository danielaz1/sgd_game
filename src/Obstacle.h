//
// Created by daniela on 02.05.19.
//

#ifndef STRIKER_OBSTACLE_H
#define STRIKER_OBSTACLE_H

#include <random>
#include <SDL2/SDL.h>
#include "GameConstants.h"


class Obstacle {
public:
    enum Type {
        GROUND, STONE, SPRING, SPONGE, TRAMPOLINE
    } type;

private:
    int x;
    int y  = GameConstants::PLAYER_MIN_Y;
    int width = 40;
    int heigth = 30;


public:
    Obstacle(Type);
    Obstacle(int);

public:
    int getPowerFactor();
    bool isCollision(int player_x, int player_y);

    void draw(SDL_Renderer *, int);

    void colorByType(SDL_Renderer *renderer);

    int getColorByType();
};



#endif //STRIKER_OBSTACLE_H
