//
// Created by daniela on 15.04.19.
//

#ifndef SDLDEMO_POWERBAR_H
#define SDLDEMO_POWERBAR_H

#include <SDL2/SDL.h>
#include "GameConstants.h"
#include <memory>
#include "Player.h"

class PowerBar {

public:std::shared_ptr<SDL_Texture> texture;
public:int drawPowerBar(SDL_Renderer* renderer);
public:int increasePower(SDL_Renderer* renderer);
public:int increaseAngle(SDL_Renderer* renderer,int angle);
private:double toRadians(int angle);

public:PowerBar(SDL_Renderer* renderer);
};


#endif //SDLDEMO_POWERBAR_H
