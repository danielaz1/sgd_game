//
// Created by daniela on 02.05.19.
//

#ifndef STRIKER_GAMECONSTANTS_H
#define STRIKER_GAMECONSTANTS_H


class GameConstants {
public:
    static const int MIN_POWER = 0;
    static const int MAX_POWER = 180;

    static const int WINDOW_HEIGHT = 768;
    static const int WINDOW_WIDTH = 1024;

    static const int PLAYER_MIN_X = 30;
    static const int PLAYER_MIN_Y = WINDOW_HEIGHT - 80;
    static const int PLAYER_MAX_X = 620;
    static const int PLAYER_MAX_Y = 20;

    static const int PLAYER_HEIGHT = 20;
    static const int PLAYER_WIDTH = 20;
};


#endif //STRIKER_GAMECONSTANTS_H
