#include "game_objects.h"
#include "ship.h"
#include "uLCD_4DGL.h"

Ship::Ship(float x, int color)  : GameObject(x, SCREEN_SIZE, SHIP_RADIUS, color) {
    setType("SHIP");
}

void Ship::draw(uLCD_4DGL &lcd) {
    lcd.triangle(x+4, 128, x-4, 128, x, 120, color);
    lcd.triangle(x+3, 128, x-3, 128, x, 122, color);
    lcd.triangle(x+2, 128, x-2, 128, x, 124, color);
    lcd.triangle(x+1, 128, x-1, 128, x, 126, color);
    lcd.triangle(x, 128, x, 128, x, 128, color);
    lcd.filled_rectangle(x, 128, x, 120, color);
    drawX = x;

    
}

void Ship::blank(uLCD_4DGL &lcd) {
    lcd.triangle(drawX+5, 128, drawX-5, 128, drawX, 118, BLACK);
    lcd.triangle(drawX+4, 128, drawX-4, 128, drawX, 120, BLACK);
    lcd.triangle(drawX+3, 128, drawX-3, 128, drawX, 122, BLACK);
    lcd.triangle(drawX+2, 128, drawX-2, 128, drawX, 124, BLACK);
    lcd.triangle(drawX+1, 128, drawX-1, 128, drawX, 126, BLACK);
    lcd.triangle(drawX, 128, drawX, 128, drawX, 128, BLACK);
    lcd.filled_rectangle(drawX, 128, drawX, 120, BLACK);
}

void Ship::update(float dt) {
    // Update position.
    x += dt*vx;
    y += dt*vy;

    // Don't run off the screen.
    if (x < size) {
        setPosition(size, y);
        setVelocity(0, 0);
    }
    if (x > SCREEN_SIZE - size) {
        setPosition(SCREEN_SIZE - size, y);
        setVelocity(0, 0);
    }

    // Set position.
    setPosition(x, y);
}

bool GameObject::collides(GameObject* other) {
    
}
void GameObject::onCollide(GameObject* other) {

}