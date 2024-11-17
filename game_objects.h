#pragma once
#include "uLCD_4DGL.h"
#include <string>
#define SCREEN_SIZE 128
#define PI 3.14159265359


class GameObject {
    protected:
        float x, y;
        float size;
        int color;
        string objType;
        bool dead;
        float vx, vy;
        float drawX, drawY;

    public:
        // Constructors
        GameObject(float x, float y, float size, int color);
        GameObject();

        // Setters and Getters
        float getX() const;
        float getY() const;
        float getRadius() const;

        float getVX() const;
        float getVY() const;

        void setPosition(float x, float y);
        void setVelocity(float vx, float vy);

        void setType(string objType);
        string getType() const;

        // Other member functions
        virtual void update(float dt);

        virtual void blank(uLCD_4DGL& lcd);
        virtual void draw(uLCD_4DGL& lcd);

        virtual bool collides(GameObject* other);
        virtual void onCollide(GameObject* other);
};




