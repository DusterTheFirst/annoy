#include "web.h"

ESP8266WebServer server(80);
base64 encoder;

// Load the root html page from the file
const char *rootHTML =
#include "html/index.html.h"
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
        String encodedKey = encoder.encode(String(key), false);
        String auth = server.header("Authorization").substring(6);

        return auth == encodedKey;
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

void handleAction() {
    if (is_auth()) {
        Serial.println(server.args());
        for (uint8_t i = 0; i < server.args(); i++) {
            Serial.println(" " + server.argName(i) + ": " + server.arg(i));
        }
        server.send(200, "text/plain", "hi");
    } else {
        server.sendHeader(
            "WWW-Authenticate",
            R"(Basic realm="Access to the annoyinator 9001!!!", charset="UTF-8")");
        server.send(401, "text/plain", "You must login to access this website");
    }
}