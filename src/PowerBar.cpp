//
// Created by daniela on 15.04.19.
//

#include "PowerBar.h"

int power=20;
int max_power = 180;
int min_power = 0;

bool add = true;

int PowerBar::drawPowerBar(SDL_Renderer *renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rectangle;

    rectangle.x = 200;
    rectangle.y = 400;
    rectangle.w = 200;
    rectangle.h = 30;
    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 150, 100, 100, 255);
    SDL_Rect rectangle1;

    rectangle1.x = 200 + power;
    rectangle1.y = 405;
    rectangle1.w = 20;
    rectangle1.h = 20;
    SDL_RenderFillRect(renderer, &rectangle1);

    return power;
}

int PowerBar::increasePower(SDL_Renderer *renderer) {
    if (power == max_power) {
        add = false;
    } else if (power == min_power){
        add = true;
    }
    add ? power+=10 : power-=10;
    drawPowerBar(renderer);
    return power;
}

