#include "RGB.h"

RGB::RGB(uint8_t rPin, uint8_t gPin, uint8_t bPin) {
    // Save RGB Pins
    this->rPin = rPin;
    this->gPin = gPin;
    this->bPin = bPin;
    this->set(0, 0, 0);
}

byte asc2byte(char chr) {
    byte rVal = 0;
    if (isdigit(chr)) {
        rVal = chr - '0';
    } else if (chr >= 'a' && chr <= 'f') {
        rVal = chr + 10 - 'a';
    }
    return rVal;
}

void RGB::set(String hex) {
    // Set the RGB values
    this->set(asc2byte(hex[0]) << 4 | asc2byte(hex[1]),
              asc2byte(hex[2]) << 4 | asc2byte(hex[3]),
              asc2byte(hex[4]) << 4 | asc2byte(hex[5]));
}

void RGB::set(uint8_t r, uint8_t g, uint8_t b) {
    // Write PWM values out
    analogWrite(this->rPin, r);
    analogWrite(this->gPin, g);
    analogWrite(this->bPin, b);
}