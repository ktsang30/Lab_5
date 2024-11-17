#pragma once
#include "uLCD_4DGL.h"
#include "game_engine.h"
#include "game_objects.h"
#define SCREEN_SIZE 128
#define PI 3.14159265359


class Ship : public GameObject {
    private:
        //
    public:
        Ship(float x, int color);
        void draw(uLCD_4DGL& lcd);
        void blank(uLCD_4DGL& lcd);
        void update(float dt);
        bool collides(GameObject* other);
        void onCollide(GameObject* other);
};