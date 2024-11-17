#pragma once
#include "uLCD_4DGL.h"
#include "game_engine.h"
#include "game_objects.h"
#define SCREEN_SIZE 128
#define PI 3.14159265359


class Asteroid : public GameObject {
    private:
        //
    public:
        Asteroid(float x, float y, float size, int color);
        Asteroid();
        void update(float dt);
        bool collides(GameObject* other);
        void onCollide(GameObject* other);

};