#pragma once
#include <Arduino.h>

class Strobe {
  private:
    bool enable;
    uint8_t count;

  public:
    Strobe();
    void on();
    void off();
    uint8_t update();
};