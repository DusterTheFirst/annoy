#include "web.h"
#include "lights.h"

ESP8266WebServer server(80);
base64 encoder;

// Load the root html page from the file
const char *rootHTML =
#include "web/index.html.h"
    ;

// Load the scripts
const char *scripts =
#include "web/scripts.js.h"
    ;

// Load the styles
const char *styles =
#include "web/styles.css.h"
    ;

void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

// Check if header is present and correct
bool is_auth() {
    if (server.hasHeader("Authorization")) {
        return server.header("Authorization").substring(6) ==
               encoder.encode(String(key), false);
    }
    return false;
}

void handleRoot() {
    if (is_auth()) {
        server.send(200, "text/html", rootHTML);
    } else {
        server.sendHeader(
            "WWW-Authenticate",
            R"(Basic realm="Access to the annoyinator 9001!!!", charset="UTF-8")");
        server.send(401, "text/plain", "You must login to access this website");
    }
}

void handleStyles() { server.send(200, "text/css", styles); }
void handleScripts() { server.send(200, "text/javascript", scripts); }

long lastDefcon = 0;
long lastRgb = 0;
unsigned long lastAction = 0;

void handleAction() {
    if (is_auth()) {
        lastAction = millis();

        if (server.hasArg("rgb")) {
            long currRgb = server.arg("created").toInt();
            // Ignore out of order req
            if (currRgb > lastRgb) {
                lastRgb = currRgb;
                rgb.set(server.arg("rgb"));
            }
        } else if (server.hasArg("defcon")) {
            long currDefcon = server.arg("created").toInt();
            // Ignore out of order req
            if (currDefcon > lastDefcon) {
                lastDefcon = currDefcon;
                defconLights.setDEFCON((DEFCON)server.arg("defcon").toInt());
            }
        } else if (server.hasArg("strobe")) {
            whiteStrobe.on();
        } else if (server.hasArg("blueStrobe")) {
            blueStrobe.on();
        }

        server.send(200, "text/plain", "hi");
    } else {
        server.sendHeader(
            "WWW-Authenticate",
            R"(Basic realm="Access to the annoyinator 9001!!!", charset="UTF-8")");
        server.send(401, "text/plain", "You must login to access this website");
    }
}

bool buttonPressed = false;
DEFCON cachedState;

void handleButton() {
    if (buttonPressed) {
        server.send(200, "text/plain", "yes");
        buttonPressed = false;
        defconLights.setDEFCON(cachedState);
    } else {
        server.send(200, "text/plain", "no");
    }
}