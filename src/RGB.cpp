#include "RGB.h"

RGB::RGB(uint8_t rPin, uint8_t gPin, uint8_t bPin) {
    // Save RGB Pins
    this->rPin = rPin;
    this->gPin = gPin;
    this->bPin = bPin;
}

void RGB::set(uint8_t r, uint8_t g, uint8_t b) {
    // Write PWM values out
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);
}