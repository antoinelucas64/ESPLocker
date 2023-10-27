#ifndef CONFIG_H
#define CONFIG_H

#include <WString.h>
#ifdef ESP32
#define LED_BLUE  13
#include <Preferences.h>
#else
#define LED_BLUE  2
#include "Preferences.h"
#endif


// pins possible: 2 (4) 12 13
#define RELAY_DOOR 4
#define DOOR_OPEN  HIGH
#define DOOR_CLOSE  LOW


class Config{
public:
   

  Config();
  ~Config(){};

  void init();

  void factoryReset();

  void writeConfig(const String & password);
  void writeConfig(const String & ssid, const String & password);
  void writeWWWConfig(const String & user,const String & password);
  
  inline const String & getSSID() const {
    return ssid;
  }
  inline const String & getPassword() const {
    return password;
  }
   
  inline const String & getWWWUser() const {
    return www_user;
  }  

  inline const String & getWWWPassword() const {
    return www_password;
  }  

private:
  void readConfig();
  void blink();

  String ssid = "Appartement Associes";
  String password = "totototo";

  String www_user = "admin";
  String www_password = "toto";

  const char * config_file = "config.txt";
  Preferences config;
};
#endif
