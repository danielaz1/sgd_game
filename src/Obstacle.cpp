//
// Created by daniela on 02.05.19.
//

#include "Obstacle.h"

Obstacle::Obstacle(Obstacle::Type type, int x) {
    this->width=10000;
    this->x=x;
    this->height=50;
    this->type = type;
    this->y=getY();
}

Obstacle::Obstacle(int x) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4);
    type = (Type) dist6(rng);
    this->x = x;
    this->y = getY();
}


int Obstacle::getPowerFactor() {
    switch (type) {
        case GROUND:
            return -20;
        case STONE:
            return -25;
        case SPRING:
            return 20;
        case SPONGE:
            return 5;
        case TRAMPOLINE:
            return 10;
        case CLOUD:
            return -180;
    }
}


int Obstacle::getY() {
    switch (type) {
        case GROUND:
            return GameConstants::PLAYER_MIN_Y+40;
        case STONE:
        case SPRING:
        case SPONGE:
        case TRAMPOLINE:
            return GameConstants::PLAYER_MIN_Y;
        case CLOUD:
            return 400;
    }
}


bool Obstacle::isCollision(int player_x, int player_y) {
    return player_x >= x && player_x <= x+width && player_y >= y-GameConstants::PLAYER_HEIGHT+5 && player_y <= y+height;
}

void Obstacle::draw(SDL_Renderer *renderer, int shift) {

    int red = getColorByType();
    SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(red), 100, 100, 255);

    SDL_Rect rectangle;

    rectangle.x = x - shift;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;
    SDL_RenderFillRect(renderer, &rectangle);

}

int Obstacle::getColorByType() {
    switch (type) {
        case GROUND:
            return 0;
        case STONE:
            return 50;
        case SPRING:
            return 200;
        case SPONGE:
            return 100;
        case TRAMPOLINE:
            return 255;
        case CLOUD:
            return 150;
    }
}






