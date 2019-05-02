//
// Created by daniela on 15.04.19.
//

#include <memory>
#include <vector>
#include "Player.h"

std::shared_ptr<SDL_Texture> Player::loadTexture(SDL_Renderer *renderer, const std::string fname) {
    std::vector<unsigned char> image;
    unsigned width, height;
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

int Player::throwRectangle(int angle, double power, SDL_Renderer *renderer) {

    if (counter != 0) {
        power -= counter * 10;
        if (power < 0) {
            power = 0;
        }
    }

    int distance = calculateX(angle, power, distance_x);
    int position_y = calculateY(angle, power, GameConstants::PLAYER_MIN_Y);
    int position_x;

    if (position_y >= GameConstants::PLAYER_MIN_Y) {
        time = TIME_INTERVAL;
        distance_x = distance;
        counter++;
    }

    position_x = distance;
    if (position_x > GameConstants::WINDOW_WIDTH / 2) {
        position_x = GameConstants::WINDOW_WIDTH / 2;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rectangle;

    rectangle.x = position_x;
    rectangle.y = position_y;
    rectangle.w = 20;
    rectangle.h = 20;
    SDL_RenderFillRect(renderer, &rectangle);

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




