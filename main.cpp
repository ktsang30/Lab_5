// Asteroids game program
#include "mbed.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"
#include "PinDetect.h"
#include "game_engine.h"

uLCD_4DGL uLCD(p9, p10, p11); // serial tx, serial rx, reset pin;

DigitalIn button_left(p21);
DigitalIn button_click(p22);
DigitalIn button_right(p23);
Speaker speaker(p25);

int main()
{
    uLCD.display_control(LANDSCAPE);
    uLCD.cls();
    uint32_t t = us_ticker_read();
    uLCD.printf("Dodge Asteroids\n", t);
    for (int i = 0; i < 15; ++i) {
        uLCD.printf("\n");
    }
    uLCD.baudrate(BAUD_3000000); //jack up baud rate to max for fast display
    wait(0.5);

    GameEngine game(uLCD, button_left, button_right, button_click);
    game.run();
}
