#include "web.h"
#include "lights.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char *ssid = "Diagon Alley";
const char *password = "Gringotts";

void ICACHE_RAM_ATTR buttonPush();

void setup() {
    // Begin serial transmission
    Serial.begin(115200);

    // Setup interrupt button
    pinMode(D1, INPUT);
    attachInterrupt(digitalPinToInterrupt(D1), buttonPush, RISING);

    // Shift out pins
    pinMode(D2, OUTPUT);
    pinMode(D4, OUTPUT);
    // Shift out latch
    pinMode(D7, OUTPUT);

    // Setup wifi as station (client)
    WiFi.mode(WIFI_STA);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Hang while connecting to wifi
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);

        digitalWrite(D7, LOW);
        shiftOut(D4, D2, LSBFIRST, ~defconLights.update().binary);
        digitalWrite(D7, HIGH);
    }
    defconLights.setDEFCON(DEFCON::Five);

    // Print out IP address
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    // Setup Multicast DNS
    if (MDNS.begin("annoy-zach")) {
        Serial.println("MDNS: started");
    } else {
        Serial.println("MDNS: failed to start");
    }

    // Setup server routing
    server.on("/", handleRoot);
    server.on("/act", handleAction);

    // Setup error handling
    server.onNotFound(handleNotFound);

    // Start the server
    server.begin();

    // Auth key
    Serial.print("Server started with secret key '");
    Serial.print(key);
    Serial.print("'");
}

uint32_t preDebounceMillis = 0;

void buttonPush() {
    uint32_t currentMillis = millis();

    if (currentMillis - preDebounceMillis > 200) {
        preDebounceMillis = currentMillis;

        Serial.println("tog");

        switch (defconLights.status) {
        case DEFCON::Five:
            defconLights.setDEFCON(DEFCON::Four);
            break;
        case DEFCON::Four:
            defconLights.setDEFCON(DEFCON::Three);
            break;
        case DEFCON::Three:
            defconLights.setDEFCON(DEFCON::Two);
            break;
        case DEFCON::Two:
            defconLights.setDEFCON(DEFCON::One);
            break;
        case DEFCON::One:
            defconLights.setDEFCON(DEFCON::Cycle);
            break;
        case DEFCON::Cycle:
            defconLights.setDEFCON(DEFCON::Random);
            break;
        case DEFCON::Random:
            defconLights.setDEFCON(DEFCON::Five);
            break;
        default:
            break;
        }
    }
}

uint32_t preMillis = 0;

byte cum = 0;

void loop() {
    uint32_t currentMillis = millis();

    if (currentMillis - preMillis > 100) {
        preMillis = currentMillis;

        byte data = 0b00000000;

        data |= 0b00011111 & ~defconLights.update().binary;
        data |= (0b01100000 & ~whiteStrobe.update());
        data |= (0b10000000 & ~blueStrobe.update());

        digitalWrite(D7, LOW);
        shiftOut(D4, D2, LSBFIRST, data);
        digitalWrite(D7, HIGH);
    }

    // Handle http clients
    server.handleClient();
    // Update Multicast DNS
    MDNS.update();
}