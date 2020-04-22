#include "defcon.h"

DEFCONLights::DEFCONLights(uint8_t five, uint8_t four, uint8_t three, uint8_t two, uint8_t one) {
    pinMode(five, OUTPUT);
    pinMode(four, OUTPUT);
    pinMode(three, OUTPUT);
    pinMode(two, OUTPUT);
    pinMode(one, OUTPUT);

    this->status = DEFCON::Cycle;

    this->one = one;
    this->two = two;
    this->three = three;
    this->four = four;
    this->five = five;
}
void DEFCONLights::setDEFCON(DEFCON s) { this->status = s; }

void DEFCONLights::update() {
    // TODO: comments
    DEFCON status = this->status;
    unsigned long currentMillis = millis();

    if (this->status == DEFCON::Cycle) {
        if (currentMillis - this->preMillis > 100) {
            // FIXME:
            this->preMillis = currentMillis;

            if (this->cycleStatus >= DEFCON::One) {
                this->cycleInc = -1;
            } else if (this->cycleStatus <= DEFCON::Five) {
                this->cycleInc = 1;
            }

            this->cycleStatus += this->cycleInc;
            status = (DEFCON)this->cycleStatus;
        }
    } else if (this->status == DEFCON::Random) {
        if (currentMillis - this->preMillis > 100) {
            this->preMillis = currentMillis;

            digitalWrite(this->one, random(0, 2));
            digitalWrite(this->two, random(0, 2));
            digitalWrite(this->three, random(0, 2));
            digitalWrite(this->four, random(0, 2));
            digitalWrite(this->five, random(0, 2));
        }
    } else {
        // Save time by skipping redraw
        if (preStatus != status) {
            switch (status) {
            case DEFCON::Five:
                digitalWrite(this->four, HIGH);
            case DEFCON::Four:
                digitalWrite(this->three, HIGH);
            case DEFCON::Three:
                digitalWrite(this->two, HIGH);
            case DEFCON::Two:
                digitalWrite(this->one, HIGH);
            default:
                break;
            }

            switch (status) {
            case DEFCON::One:
                digitalWrite(this->one, LOW);
            case DEFCON::Two:
                digitalWrite(this->two, LOW);
            case DEFCON::Three:
                digitalWrite(this->three, LOW);
            case DEFCON::Four:
                digitalWrite(this->four, LOW);
            case DEFCON::Five:
                digitalWrite(this->five, LOW);
            default:
                break;
            }
        }
    }

    this->preStatus = status;
}