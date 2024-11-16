#include "game_engine.h"
#include "game_objects.h"
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
        
        // Part 2
        Ship* player =  new Ship(0, RED); 
        gameObjects.push_back(player);
        asteroid_spawn_time = 0;
        score = 0;
        game_over = false;
        gameObjects[0] -> setPosition(SCREEN_SIZE/2, SCREEN_SIZE);
        gameObjects[0] -> setVelocity(0, 0);
        lcd.printf("\nship created\n");

        // all of these print 0
        int a = 3;
        lcd.printf("fstring test: %5.2f\n", 6);
        lcd.printf("fstring test: %f\n", a);
        lcd.printf("player x: %f\n", int(player -> getX()));
        lcd.printf("size of vector: %f\n", gameObjects.size());


        int32_t t0 = us_ticker_read();
        // Generate use player delay as source of randomnes
        srand(t0);
        int32_t desired_dt_us = 100000;
        while (running()) {
            //lcd.printf("inside running loop\n");
            update();
            //lcd.printf("updated\n");
            draw();

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

        // Part 3
        run_game_over();
    }
}

void GameEngine::run_menu() {
    lcd.cls();
    lcd.printf("press enter\nto start");
    for (int i = 0; i < 15; ++i) {
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
    //lcd.printf("inside update\n");
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
    //lcd.printf("ship buttons\n");

    // Spawn asteroids.
    if (asteroid_spawn_time == 0) {
        asteroid_spawn_time = 20;
        int x = rand() % SCREEN_SIZE;

        float angle = ((rand() % 141) - 70) * PI / 180.0f; // +70 to -70 degrees
        float velocity = 30;
        Asteroid* newAsteroid =  new Asteroid(x, 0, 4, BLUE);
        lcd.printf("astr x: %\n", int(newAsteroid -> getX()));
        lcd.printf("astr y: %\n", int(newAsteroid -> getY()));
        newAsteroid -> setVelocity(velocity * sin(angle), velocity * cos(angle));
        gameObjects.push_back(newAsteroid);
    }
    asteroid_spawn_time -= 1;
    //lcd.printf("asteroids spawned\n");

    // Update all objects
    // ----------------------
    // Update player
    gameObjects[0] -> update(dt);
    float playerX = gameObjects[0] -> getX();
    float playerY = gameObjects[0] -> getY();
    float playerR = gameObjects[0] -> getRadius();
    // Don't run off the screen.
    if (playerX < playerR) {
        playerX = playerR;
        gameObjects[0] -> setVelocity(0, 0);
    }
    if (playerX > SCREEN_SIZE - playerR) {
        playerX = SCREEN_SIZE - playerR;
        gameObjects[0] -> setVelocity(0, 0);
    }
    gameObjects[0] -> setPosition(playerX, playerY);
    //lcd.printf("player updated\n");

    // Update asteroids
    for (int i = 1; i < gameObjects.size();) {
        lcd.printf("inside astr update loop\n");
        //GameObject& asteroid = gameObjects[i];
        gameObjects[i] -> update(dt);

        float x = gameObjects[i] -> getX();
        float y = gameObjects[i] -> getY();
        float r = gameObjects[i] -> getRadius();
        float minDist = r + playerR;
        lcd.printf("check 1\n");


        // Check collision detection against player.
        float dx = x - playerX;
        float dy = y - playerY;
        // Pythagorean theorem.
        if (dx*dx + dy*dy < minDist*minDist) {
            game_over = true;
            break;
        }
        lcd.printf("check 2\n");
        lcd.printf("y val: %\n", y);

        // Handle asteroids that hit the bottom of the screen.
        if (y > SCREEN_SIZE) {
            gameObjects[i] -> blank(lcd);
            delete gameObjects[i];
            lcd.printf("astr delete\n");
            //gameObjects.erase(gameObjects.begin() + i);
            ++score;
            break;
        }
        ++i;

        // Bounce against the walls.
        if (x < r) {
            x = 2*r - x;
            gameObjects[i] -> setVelocity(gameObjects[i] -> getVX() * -1, gameObjects[i] -> getVY());
        }
        if (x > SCREEN_SIZE - r) {
            x = 2*(SCREEN_SIZE - r) - x;
            gameObjects[i] -> setVelocity(gameObjects[i] -> getVX() * -1, gameObjects[i] -> getVY());
        }
        gameObjects[i] -> setPosition(x, y);
        lcd.printf("check 3\n");
    }
}

void GameEngine::draw() {
    lcd.printf("inside draw\n");
    //gameObjects[i] -> blank(lcd);
    //gameObjects[i] -> draw(lcd);
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i] -> blank(lcd);
        gameObjects[i] -> draw(lcd);
    }
}

void GameEngine::run_game_over() {
    //asteroids.clear();
    for (int i = 0; i < gameObjects.size(); ++i) {
        delete gameObjects[i];
    }

    lcd.cls();
    lcd.printf("you died...\nscore:\n%d", score);
    for (int i = 0; i < 14; ++i) {
        lcd.printf("\n");
    }

    // Wait for button click.
    while (button_click.read() == 1) {}
    while (button_click.read() == 0) {}
}

