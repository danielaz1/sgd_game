/**
 * This is the simple hello world for SDL2.
 *
 * You need C++14 to compile this.
 */

#include <SDL2/SDL.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
#include "GameConstants.h"
#include "Player.h"
#include "PowerBar.h"
#include "Obstacle.h"
#include "ObstacleGenerator.h"

// check for errors
#define errcheck(e)                                                            \
  {                                                                            \
    if (e) {                                                                   \
      cout << SDL_GetError() << endl;                                          \
      SDL_Quit();                                                              \
      return -1;                                                               \
    }                                                                          \
  }


int main(int, char **) {
    using namespace std;
    using namespace std::chrono;
    bool gameStarted = false;
    bool drawPowerBar = false;
    bool increasePower = false;
    bool throwRectangle = false;
    int distance=0;
    int power=0;
    int angle = 45;

    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

    shared_ptr<SDL_Window> window(SDL_CreateWindow(
            "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN),
                                  [=](auto w) { SDL_DestroyWindow(w); });

    errcheck(window == nullptr);

    shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(
            window.get(), -1, SDL_RENDERER_ACCELERATED), // SDL_RENDERER_PRESENTVSYNC
                                      [=](auto r) { SDL_DestroyRenderer(r); });
    errcheck(renderer == nullptr);

    PowerBar *powerBar = new PowerBar();
    Player *player = new Player();
    ObstacleGenerator *obstacleGenerator = new ObstacleGenerator();

    //auto dt = 15ms;
    milliseconds dt(15);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time
    for (bool game_active = true; game_active;) {

        SDL_SetRenderDrawColor(renderer.get(), 66, 128, 128, 255);
        SDL_RenderClear(renderer.get());

        SDL_Event event;
        while (SDL_PollEvent(&event)) { // check if there are some events
            switch (event.type) {
                case SDL_QUIT:
                    game_active = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) game_active = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (!gameStarted) {
                        gameStarted = true;
                        increasePower = true;
                        drawPowerBar = true;
                    }
                    break;
            }

            auto kstate = SDL_GetKeyboardState(nullptr);
            if (kstate[SDL_SCANCODE_SPACE]) {
                increasePower = false;
                throwRectangle = true;
                drawPowerBar = false;
            }
            if (kstate[SDL_SCANCODE_UP]){
                angle++;
                if(angle >= 90){
                    angle = 89;
                }
            }
            if(kstate[SDL_SCANCODE_DOWN]){
                angle--;
                if(angle <= 0){
                    angle = 1;
                }
            }
        }

        printf("%s %d","\n distance:", distance);

        if (increasePower) {
            power = powerBar->increasePower(renderer.get());
            powerBar->increaseAngle(renderer.get(),angle);
        } else if (drawPowerBar) {
            power = powerBar->drawPowerBar(renderer.get());
        }
        if(throwRectangle) {
            int shift = 0;
            if (distance >= GameConstants::WINDOW_WIDTH/2) {
                shift = distance - GameConstants::WINDOW_WIDTH/2;
            }

            obstacleGenerator->generate(distance);

            obstacleGenerator->drawAll(renderer.get(), shift);
            player->increaseTime();
            distance = player->throwRectangle(angle, power, renderer.get(), obstacleGenerator);

        }

        SDL_RenderPresent(renderer.get()); // draw frame to screen
        this_thread::sleep_until(current_time = current_time + dt);
    }
    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());
    SDL_Quit();
    return 0;
}
