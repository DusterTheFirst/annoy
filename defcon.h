#ifndef DEFCON_h
#define DEFCON_h
#include <Arduino.h>

enum DEFCON { Five, Four, Three, Two, One, Cycle, Random };

class DEFCONLights {
  private:
    uint8_t one, two, three, four, five;

    uint8_t cycleInc = 1;
    uint8_t cycleStatus = DEFCON::Five;

    unsigned long preMillis = 0;
    DEFCON preStatus;

  public:
    DEFCON status;

    DEFCONLights(uint8_t five, uint8_t four, uint8_t three, uint8_t two, uint8_t one);
    void setDEFCON(DEFCON status);
    void update();
};

#endif