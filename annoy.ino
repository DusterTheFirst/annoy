#include "defcon.h"

DEFCONLights lights;

void ICACHE_RAM_ATTR IncDEFCON();

void setup() {
    Serial.begin(115200);
    pinMode(D2, INPUT);
    attachInterrupt(digitalPinToInterrupt(D2), IncDEFCON, RISING);
}

void IncDEFCON() {
    switch (lights.status) {
    case DEFCON::Five:
        lights.setDEFCON(DEFCON::Four);
        break;
    case DEFCON::Four:
        lights.setDEFCON(DEFCON::Three);
        break;
    case DEFCON::Three:
        lights.setDEFCON(DEFCON::Two);
        break;
    case DEFCON::Two:
        lights.setDEFCON(DEFCON::One);
        break;
    case DEFCON::One:
        lights.setDEFCON(DEFCON::Cycle);
        break;
    case DEFCON::Cycle:
        lights.setDEFCON(DEFCON::Random);
        break;
    case DEFCON::Random:
        lights.setDEFCON(DEFCON::Five);
        break;
    default:
        break;
    }
}

uint32_t preMillis = 0;

void loop() {
    uint32_t currentMillis = millis();

    if (currentMillis - preMillis > 1000) {
        preMillis = currentMillis;

        Serial.println(lights.update().binary, BIN);
    }
}