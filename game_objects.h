#pragma once
#include "uLCD_4DGL.h"
#define SCREEN_SIZE 128
#define PI 3.14159265359
#define SHIP_RADIUS 3

class GameObject {
    protected:
        float x, y;
        float size;
        int color;
        float vx, vy;

        float drawX, drawY;

    public:
        GameObject(float x, float y, float size, int color);
        GameObject();

        float getX() const;
        float getY() const;
        float getRadius() const;

        float getVX() const;
        float getVY() const;

        void setPosition(float x, float y);
        void setVelocity(float vx, float vy);

        void update(float dt);

        void blank(uLCD_4DGL& lcd) const;
        virtual void draw(uLCD_4DGL& lcd);
};

class Ship : public GameObject {
    private:
        //
    public:
        Ship(float x, int color);
};

class Asteroid : public GameObject {
    private:
        //
    public:
        Asteroid(float x, float y, float size, int color);

};
