#ifndef WEB_h
#define WEB_h
#include "key.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <libb64/cdecode.h>
#include <base64.h>

extern ESP8266WebServer server;

// Load the root html page from the file
extern const char *rootHTML;

void handleNotFound();
bool is_auth();
void handleRoot();
void handleAction();

#endif