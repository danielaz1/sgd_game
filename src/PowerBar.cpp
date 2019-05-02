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

    int x = 100 * cos(toRadians(angle));
    int y = 100 * sin(toRadians(angle));

    SDL_RenderDrawLine(renderer, 30, 400,30 + x , 400 - y );

    printf("%s %d","\n x:", x );
    printf("%s %d","\n y:", y );
    //SDL_RenderDrawLine(renderer, 30, 400, 130, 400);
    SDL_RenderDrawLine(renderer, 0, 400, 640, 400);

    return angle;
}


double PowerBar::toRadians(int angle) {
    return (angle * M_PI)/180;
}
