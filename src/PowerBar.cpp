//
// Created by daniela on 15.04.19.
//

#include "PowerBar.h"
#include "GameConstants.h"

int power=20;
bool add = true;

int PowerBar::drawPowerBar(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle;

    int width = 200;
    int height = 30;
    int x = GameConstants::WINDOW_WIDTH/2 - width/2;
    int y = GameConstants::WINDOW_HEIGHT - 50;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 150, 100, 100, 255);
    SDL_Rect rectangle1;

    rectangle1.x = x + power;
    rectangle1.y = y + 5;
    rectangle1.w = 20;
    rectangle1.h = 20;
    SDL_RenderFillRect(renderer, &rectangle1);

    return power;
}

int PowerBar::increasePower(SDL_Renderer *renderer) {
    if (power == GameConstants::MAX_POWER) {
        add = false;
    } else if (power == GameConstants::MIN_POWER){
        add = true;
    }
    add ? power+=10 : power-=10;
    drawPowerBar(renderer);
    return power;
}
int PowerBar::increaseAngle(SDL_Renderer *renderer,int angle) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int start_y = GameConstants::WINDOW_HEIGHT - 50;

    int x = 100 * cos(toRadians(angle));
    int y = 100 * sin(toRadians(angle));

    SDL_Rect rectangle;

    int width = 100;
    int height = 200;
    int x1 = 0;
    int y1 = GameConstants::PLAYER_MIN_Y- height + 35;
    rectangle.x = x1;
    rectangle.y = y1 ;
    rectangle.w = width;
    rectangle.h = height;

    SDL_Point center;
    center.x = 50;
    center.y = 200;
    SDL_RenderCopyEx(renderer, texture.get(), NULL, &rectangle, 90 - angle, &center, SDL_FLIP_HORIZONTAL);

    return angle;
}

double PowerBar::toRadians(int angle) {
    return (angle * M_PI)/180;
}

PowerBar::PowerBar(SDL_Renderer *renderer) {
    texture = Player::loadTexture(renderer,"data/cannon.png");
}
