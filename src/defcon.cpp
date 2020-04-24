#include "defcon.h"

DEFCONLights::DEFCONLights() { this->status = DEFCON::Cycle; }
void DEFCONLights::setDEFCON(DEFCON s) { this->status = s; }

DEFCONLightStatus DEFCONLights::update() {
    // Custom status handlers
    if (this->status == DEFCON::Cycle) {
        // Reverse direction if on a boundary
        if (this->cycleStatus >= DEFCON::One) {
            this->cycleInc = -1;
        } else if (this->cycleStatus <= DEFCON::Five) {
            this->cycleInc = 1;
        }

        // Increment saved status
        this->cycleStatus += this->cycleInc;
        // Update rendered status
        return this->render((DEFCON)this->cycleStatus);
    } else if (this->status == DEFCON::Random) {
        // Skip update, uses custom system
        return {{.one = (bool)(random(0, 2)),
                 .two = (bool)(random(0, 2)),
                 .three = (bool)(random(0, 2)),
                 .four = (bool)(random(0, 2)),
                 .five = (bool)(random(0, 2))}};
    } else {
        // Normal render for other statuses
        return this->render(this->status);
    }
}

DEFCONLightStatus DEFCONLights::render(DEFCON status) {
    // Start with all lights off
    DEFCONLightStruct lights = {.one = false,
                                .two = false,
                                .three = false,
                                .four = false,
                                .five = false};

    // Switch the lights on if they need to be
    switch (status) {
    case DEFCON::One:
        lights.one = true;
    case DEFCON::Two:
        lights.two = true;
    case DEFCON::Three:
        lights.three = true;
    case DEFCON::Four:
        lights.four = true;
    case DEFCON::Five:
        lights.five = true;
    default:
        break;
    }

    // Wrap the result in the union
    return {lights};
}