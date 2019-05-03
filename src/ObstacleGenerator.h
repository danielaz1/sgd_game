//
// Created by daniela on 03.05.19.
//

#ifndef STRIKER_OBSTACLEGENERATOR_H
#define STRIKER_OBSTACLEGENERATOR_H

#include <list>
#include <iterator>
#include "Obstacle.h"

class ObstacleGenerator {
public:
    std::list<Obstacle> obstacles;
    int counter = 0;
public:ObstacleGenerator();
    void generate(int);
    float detectCollision(int player_x, int player_y);
    void drawAll(SDL_Renderer *, int);
};


#endif //STRIKER_OBSTACLEGENERATOR_H
