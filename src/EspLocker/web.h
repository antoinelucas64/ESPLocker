#ifndef WEB_A_A
#define WEB_A_A

#include "config.h"
#ifdef ESP32
#include <WebServer.h>
#else
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#endif

class Web {
public:
  Web(Config& config);
  ~Web(){};

  void init();
  void handleClient();
  bool haveToReboot();
private:
  Config& config;
  bool wantReboot;
  String incorrectPassword();
  String createAdminPage();
  String formWifiPage() ;
  String formAdminPage() ;
  String info();
  String responseHTML();
  String headHtml();
  void handleLogin();
};
#endif