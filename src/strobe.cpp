#include "strobe.h"

Strobe::Strobe() {
    this->enable = false;
    this->count = 0;
}

void Strobe::off() { this->enable = false; }

void Strobe::on() { this->enable = true; }

uint8_t Strobe::update() {
    if (this->enable) {
        this->count++;
        if (this->count == 100) {
            this->off();
        } else if (this->count % 2 == 0) {
            return 0b11111111;
        }
    }

    return 0b00000000;
}