#pragma once
#include <Arduino.h>

enum DEFCON { Five, Four, Three, Two, One, Cycle, Random };

struct DEFCONLightStruct {
  bool one : 1;
  bool two : 1;
  bool three : 1;
  bool four : 1;
  bool five : 1;
};

union DEFCONLightStatus {
  DEFCONLightStruct values;
  uint8_t binary;
};

class DEFCONLights {
  private:
    int8_t cycleInc = 1;
    uint8_t cycleStatus = DEFCON::Five;

    DEFCONLightStatus render(DEFCON status);

  public:
    DEFCON status;

    DEFCONLights();
    void setDEFCON(DEFCON status);
    DEFCONLightStatus update();
    bool changed();
};