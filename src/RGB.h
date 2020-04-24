#ifndef RGB_h
#define RGB_h
#include <Arduino.h>

class RGB {
    private:
        uint8_t rPin, gPin, bPin;

    public:
        RGB(uint8_t rPin, uint8_t gPin, uint8_t bPin);
        void set(uint8_t r, uint8_t g, uint8_t b);
};

#endif