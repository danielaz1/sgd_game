//
// Created by daniela on 03.05.19.
//

#include "ObstacleGenerator.h"

ObstacleGenerator::ObstacleGenerator() {

    generate(0);

}

void ObstacleGenerator::generate(int distance) {

    if (counter == 0 || distance / counter > 2000) {
        auto obstacle1 = new Obstacle(Obstacle::Type::GROUND, counter*1000);
        obstacles.push_front(*obstacle1);
        for (int i = 0; i < 7; i++) {
            auto obstacle = new Obstacle(counter * 2000 + (i+1) * 400);
            obstacles.push_front(*obstacle);
            if (counter>3) {
                obstacles.pop_back();
            }
        }
        counter++;
    }
}

float ObstacleGenerator::detectCollision(int player_x, int player_y) {
    for (auto &obstacle : obstacles) {
        if (obstacle.isCollision(player_x, player_y)) {
            return obstacle.getPowerFactor();
        }
    }
    return 0;
}

void ObstacleGenerator::drawAll(SDL_Renderer *renderer, int shift) {
    for (auto &obstacle : obstacles) {
        obstacle.draw(renderer, shift);
    }
}


