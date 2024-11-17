#include "game_engine.h"
#include "game_objects.h"
#include "asteroid.h"
#include "ship.h"
#include "mbed.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"

GameEngine::GameEngine(uLCD_4DGL& lcd, DigitalIn& left, DigitalIn& right, DigitalIn& click)
        : lcd(lcd), button_left(left), button_right(right), button_click(click) {

    button_left.mode(PullUp);
    button_right.mode(PullUp);
    button_click.mode(PullUp);

}
void GameEngine::run() {
    while (true) {
        // Part 1
        run_menu();
        for (int i = 0; i < gameObjects.size(); i++){
            gameObjects.erase(gameObjects.begin() + i);
            delete gameObjects[i];
        }
        gameObjects.clear();

        // Part 2
        asteroid_spawn_time = 0;
        score = 0;
        game_over = false;
        gameObjects.push_back(new Ship(0, RED)); 
        gameObjects[0] -> setPosition(SCREEN_SIZE/2, SCREEN_SIZE); //
        gameObjects[0] -> setVelocity(0, 0);




        int32_t t0 = us_ticker_read();
        // Generate use player delay as source of randomnes
        srand(t0);
        int32_t desired_dt_us = 100000;
        while (running()) {
            update();
            drawAll();

            int32_t t1 = us_ticker_read();
            int32_t dt = t1 - t0;
            if (dt < desired_dt_us) {
                wait_us(desired_dt_us - dt);
                t0 += desired_dt_us;
            }
            else {
                t0 = t1;
            }
        }

    }
}

void GameEngine::run_menu() {
    lcd.cls();
    lcd.printf("\n\n\n  ASTROID DODGER  \n    Main Menu\n\n     Buttons:\nLeft  Click  Right\n\n  Click to Start");
    for (int i = 0; i < 21; ++i) {
        lcd.printf("\n");
    }
    // Wait for button click
    while (button_click.read() == 1) {}
    while (button_click.read() == 0) {}
    lcd.cls();
}

bool GameEngine::running() {
    return !game_over;
}

void GameEngine::update() {
    // Update player velocity based on button presses.
    float dt = 0.1;
    float vx = gameObjects[0] -> getVX();
    float vy = gameObjects[0] -> getVY();
    if (button_left.read() == 0) {
        vx -= 10;
    }
    if (button_right.read() == 0) {
        vx += 10;
    }
    gameObjects[0] -> setVelocity(vx, vy);


    // Spawn asteroids.
    if (asteroid_spawn_time == 0) {
        asteroid_spawn_time = 20;
        int x = rand() % SCREEN_SIZE;

        float angle = (((rand() % 141) - 70) * PI / 180.0f); // +70 to -70 degrees
        float velocity = 30;
        gameObjects.push_back(new Asteroid(x, 0, 4, DGREY));
        gameObjects.back() -> setVelocity(velocity * sin(angle), velocity * cos(angle));

    }
    asteroid_spawn_time -= 1;
 
    // Update all objects
    for (int i = 0; i < gameObjects.size(); ++i) {
        // Update position of all objects
        gameObjects[i] -> update(dt);

        // Old collision detection code
        float minDist = (gameObjects[i] -> getRadius()) + (gameObjects[0] -> getRadius());

        // Check collision detection against player.
        float dx = (gameObjects[i] -> getX()) - (gameObjects[0] -> getX());
        float dy = (gameObjects[i] -> getY()) - (gameObjects[0] -> getY());
        // Pythagorean theorem.
        if (dx*dx + dy*dy < minDist*minDist) {
            game_over = true;
            run_game_over();
            break;
        }

        

        /*
        // Bounce against the walls.
        if ((gameObjects[i] -> getX()) < (gameObjects[i] -> getRadius())) {
            //x = 2*r - x;
            gameObjects[i] -> setPosition((2*(gameObjects[i] -> getRadius())-(gameObjects[i] -> getX())), (gameObjects[i] -> getY()));
            gameObjects[i] -> setVelocity(((gameObjects[i] -> getVX()) * -1), (gameObjects[i] -> getVY()));
        }
        else { 
            gameObjects[i] -> setPosition((gameObjects[i] -> getX()), (gameObjects[i] -> getY()));
        }
        if ((gameObjects[i] -> getX()) > (gameObjects[i] -> getRadius())) {
            //x = 2*(SCREEN_SIZE - r) - x;
            gameObjects[i] -> setPosition((2*(SCREEN_SIZE-(gameObjects[i] -> getRadius()))-(gameObjects[i] -> getX())), (gameObjects[i] -> getY()));
            gameObjects[i] -> setVelocity(gameObjects[i] -> getVX() * -1, gameObjects[i] -> getVY());
        }
        else { 
            gameObjects[i] -> setPosition((gameObjects[i] -> getX()), (gameObjects[i] -> getY()));
        }
        */

        // Handle asteroids that hit the bottom of the screen.
        if ((gameObjects[i] -> getY()) > SCREEN_SIZE) {
            gameObjects[i] -> blank(lcd);
            delete gameObjects[i];
            gameObjects.erase(gameObjects.begin() + i);
            ++score;
            break;
        }
        
    } 
    
}

void GameEngine::drawAll() {

    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i] -> blank(lcd);
        gameObjects[i] -> draw(lcd);
    }
}

void GameEngine::run_game_over() {
    
    for (int i = 0; i < gameObjects.size(); ++i) {
        delete gameObjects[i];
        gameObjects.erase(gameObjects.begin() + i);
    }
    
    gameObjects.clear();
    lcd.cls();
    lcd.printf("\n\n\n  ASTROID DODGER  \n    GAME OVER\n\n  Final Score: %d", score);
    lcd.printf("\n\n Click to Restart");
    for (int i = 0; i < 5; ++i) {
        lcd.printf("\n");
    }

    // Wait for button click.
    while (button_click.read() == 1) {}
    while (button_click.read() == 0) {}
}

