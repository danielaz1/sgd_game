//
// Created by daniela on 15.04.19.
//


#include "Player.h"

std::shared_ptr<SDL_Texture> Player::loadTexture(SDL_Renderer *renderer, const std::string fname) {
    std::vector<unsigned char> image;
    unsigned width=20, height=20;
    errcheck(lodepng::decode(image, width, height, fname));

    SDL_Surface *bitmap = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
                                                         SDL_PIXELFORMAT_RGBA32);
    std::copy(image.begin(), image.end(), (unsigned char *) bitmap->pixels);
    errcheck(bitmap == nullptr);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, bitmap);

    errcheck(tex == nullptr);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    std::shared_ptr<SDL_Texture> texture(
            tex, [](SDL_Texture *ptr) { SDL_DestroyTexture(ptr); });
    SDL_FreeSurface(bitmap);
    return texture;
}

int Player::throwRectangle(int angle, double power, SDL_Renderer *renderer, ObstacleGenerator *obstacleGenerator) {

    if (power+powerFactor < 0) {
        power = 0;
    } else {
        power += powerFactor;
    }

    int distance = calculateX(angle, power, distance_x);
    int position_y = calculateY(angle, power, distance_y);
    int position_x;

    float newPowerFactor = obstacleGenerator->detectCollision(distance, position_y);
    powerFactor+=newPowerFactor;

    if (newPowerFactor != 0) {
        distance_x = distance;
        distance_y = position_y;
        time = 0;
    }

    position_x = distance;
    if (position_x > GameConstants::WINDOW_WIDTH / 2) {
        position_x = GameConstants::WINDOW_WIDTH / 2;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rectangle;

    rectangle.x = position_x;
    rectangle.y = position_y;
    rectangle.w = GameConstants::PLAYER_WIDTH;
    rectangle.h = GameConstants::PLAYER_HEIGHT;
   // SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderCopy(renderer, texture.get(), NULL, &rectangle);
    return distance;
}


double Player::toRadians(int angle) {
    return (angle * M_PI) / 180;
}

int Player::calculateX(int angle, double power, int start_x) {
    double vx = power * cos(toRadians(angle));

    int position_x = start_x + vx * time;

    return position_x;
}

int Player::calculateY(int angle, double power, int start_y) {
    double vy = power * sin(toRadians(angle));
    int position_y = start_y - (vy * time - (gravity / 2) * time * time);
    return position_y;
}

float Player::increaseTime() {
    return time += TIME_INTERVAL;
}

void Player::calculateCollision(int position_y, int distance) {
    if (position_y >= GameConstants::PLAYER_MIN_Y) { //ground
        time = 0;
        distance_x = distance;
        distance_y =  GameConstants::PLAYER_MIN_Y;
        counter++;
    }
}

Player::Player(SDL_Renderer *renderer) {
    texture = loadTexture(renderer, "data/kula.png");
}




