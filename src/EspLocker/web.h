#ifndef WEB_A_A
#define WEB_A_A

#include "config.h"
#ifdef ESP32
#include <WebServer.h>
#else
#include <ESP8266WebServer.h>
#endif

class Web {
public:
  Web(Config& config);
  ~Web(){};

  void init();
  void handleClient();
private:
  Config& config;
#ifdef ESP32
WebServer server;
#else
ESP8266WebServer server;
#endif  

  String createAdminPage();
  String formWifiPage() ;
};
#endif