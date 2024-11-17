#include "game_objects.h"
#include "asteroid.h"
#include "uLCD_4DGL.h"


Asteroid::Asteroid(float x, float y, float size, int color) : GameObject(x, y, size, color) {
    setType("ASTEROID");
}

Asteroid::Asteroid() : GameObject() {
    setType("ASTEROID");
}

void Asteroid::update(float dt) {
    // Update position.
    x += dt*vx;
    y += dt*vy;

    // Bounce against the walls.
    if (x < size) {
        x = 2*size - x;
        setVelocity(vx * -1, vy);
    }
    if (x > SCREEN_SIZE - size) {
        x = 2*(SCREEN_SIZE - size) - x;
        setVelocity(vx * -1, vy);
    }

    // Set position.
    setPosition(x, y);
}

bool GameObject::collides(GameObject* other) {
    if (other->getType() == "ASTEROID") {
    
    }
}
void GameObject::onCollide(GameObject* other) {

}