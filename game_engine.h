#pragma once
#include <vector>
#include "game_objects.h"
#include "mbed.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"

#define SCREEN_SIZE 128
#define PI 3.14159265359
#define SHIP_RADIUS 3

class GameEngine {
    private:
        uLCD_4DGL lcd;
        DigitalIn button_left;
        DigitalIn button_right;
        DigitalIn button_click;

        //vector<GameObject> asteroids;
        vector<GameObject*> gameObjects;
        GameObject player;
        bool game_over;

        int asteroid_spawn_time;
        int score;

        void run_menu();
        bool running();
        void update();
        void draw();
        void run_game_over();

    public:

        GameEngine(uLCD_4DGL&, DigitalIn& left, DigitalIn& right, DigitalIn& click);
        void run();

};