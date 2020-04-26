#ifndef WEB_h
#define WEB_h
#include "key.h"
#include "defcon.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <libb64/cdecode.h>
#include <base64.h>

extern ESP8266WebServer server;

extern unsigned long lastAction;
extern long lastDefcon;
extern long lastRgb;

extern bool buttonPressed;
extern DEFCON cachedState;

void handleNotFound();
bool is_auth();
void handleRoot();
void handleStyles();
void handleScripts();
void handleAction();
void handleButton();

#endif