#include "defcon.h"

DEFCONLights lights;

void ICACHE_RAM_ATTR IncDEFCON();

void setup() {
    Serial.begin(115200);

    pinMode(D1, INPUT);
    attachInterrupt(digitalPinToInterrupt(D1), IncDEFCON, RISING);

    pinMode(D2, OUTPUT);
    pinMode(D4, OUTPUT);

    pinMode(D7, OUTPUT);
}

uint32_t preDebounceMillis = 0;

void IncDEFCON() {
    uint32_t currentMillis = millis();

    if (currentMillis - preDebounceMillis > 200) {
        preDebounceMillis = currentMillis;

        Serial.println("tog");

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
}

uint32_t preMillis = 0;

byte lightsData = 0b00000000;
byte cum = 0;

void loop() {
    uint32_t currentMillis = millis();

    byte data = 0b00000000;

    if (currentMillis - preMillis > 100) {
        preMillis = currentMillis;

        lightsData = 0b00011111 & ~lights.update().binary;

        cum++;
    }

    data |= lightsData;

    data |= (0b00000111 & cum) << 5;

    digitalWrite(D7, LOW);
    shiftOut(D4, D2, LSBFIRST, data);
    digitalWrite(D7, HIGH);
}