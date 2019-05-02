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
    std::copy(image.begin(), image.end(), (unsigned char *)bitmap->pixels);
    errcheck(bitmap == nullptr);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, bitmap);

    errcheck(tex == nullptr);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    std::shared_ptr<SDL_Texture> texture(
            tex, [](SDL_Texture *ptr) { SDL_DestroyTexture(ptr); });
    SDL_FreeSurface(bitmap);
    return texture;
}

void Player::throwRectangle(int angle, int power, double time, SDL_Renderer *renderer) {
    double vx = power * cos(toRadians(angle));
    double vy = power * sin(toRadians(angle));

    int position_x = start_position_x + vx *time;
    int position_y = start_position_y - (vy * time - (gravity/2)*time*time);


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rectangle;

    rectangle.x = position_x;
    rectangle.y = position_y;
    rectangle.w = 20;
    rectangle.h = 20;
    SDL_RenderFillRect(renderer, &rectangle);
}

double Player::toRadians(int angle) {
    return (angle * M_1_PI)/180;
}




