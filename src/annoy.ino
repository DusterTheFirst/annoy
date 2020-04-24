#include "RGB.h"
#include "defcon.h"
#include "web.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char *ssid = "Diagon Alley";
const char *password = "Gringotts";

const char *key =
#include "key.h"
    ;

DEFCONLights lights;
RGB rgb(D8, D6, D5);

void ICACHE_RAM_ATTR IncDEFCON();

void setup() {
    // Begin serial transmission
    Serial.begin(115200);

    // Setup interrupt button
    pinMode(D1, INPUT);
    attachInterrupt(digitalPinToInterrupt(D1), IncDEFCON, RISING);

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
        shiftOut(D4, D2, LSBFIRST, ~lights.update().binary);
        digitalWrite(D7, HIGH);
    }
    lights.setDEFCON(DEFCON::Five);

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

    // Setup error handling
    server.onNotFound(handleNotFound);

    // Start the server
    server.begin();

    Serial.print("Server started with secret key '");
    Serial.print(key);
    Serial.print("'");
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

byte cum = 0;

void loop() {
    uint32_t currentMillis = millis();

    if (currentMillis - preMillis > 100) {
        preMillis = currentMillis;

        byte data = 0b00000000;

        data |= 0b00011111 & ~lights.update().binary;

        cum++;

        data |= (0b00000111 & cum) << 5;

        rgb.set(random(0, 255), random(0, 255), random(0, 255));

        digitalWrite(D7, LOW);
        shiftOut(D4, D2, LSBFIRST, data);
        digitalWrite(D7, HIGH);
    }

    // Handle http clients
    server.handleClient();
    // Update Multicast DNS
    MDNS.update();
}