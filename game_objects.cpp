#include "game_objects.h"
#include "uLCD_4DGL.h"

// Constructors
GameObject::GameObject(float x, float y, float size, int color)
    : size(size), color(color), drawX(x), drawY(y) {
    setPosition(x, y);
    setType("object");
    dead = true;
}

GameObject::GameObject(){
    
}

// Setters and Getters
float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }
float GameObject::getRadius() const { return size; };


float GameObject::getVX() const { return vx; };
float GameObject::getVY() const { return vy; };


void GameObject::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameObject::setVelocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

void GameObject::setType(string objType) {
    this->objType = objType;
}
string GameObject::getType() const {
    return objType;
}

// Other member functions
void GameObject::update(float dt) {
    x += dt*vx;
    y += dt*vy;
    setPosition(this->x, this->y);
    setVelocity(this->vx, this->vy);
}

void GameObject::blank(uLCD_4DGL& lcd) {
    lcd.filled_circle(drawX, drawY, size, BLACK);
}

void GameObject::draw(uLCD_4DGL& lcd) {
    lcd.filled_circle(x, y, size, color);
    drawX = x;
    drawY = y;
}

bool GameObject::collides(GameObject* other) {
    
}
void GameObject::onCollide(GameObject* other) {

}



