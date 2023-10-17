#ifndef CONFIG_H
#define CONFIG_H

#include <WString.h>
#ifdef ESP32
#include <Preferences.h>
#else
#include "Preferences.h"
#endif
#define SIM800L_RX     27
#define SIM800L_TX     26
#define SIM800L_PWRKEY 4
#define SIM800L_RST    5
#define SIM800L_POWER  23


// pins possible: 2 (4) 12 13
#define RELAY_DOOR 4
#define DOOR_OPEN  HIGH
#define DOOR_CLOSE  LOW
#define POWER_ON  LOW
#define POWER_OFF  HIGH


class Config{
public:
   

  Config();
  ~Config(){};

  void init();
  void writeConfig(const String & password);
  void writePowerState(bool powerState);
  inline bool getPowerState() const{
    return powerState;
  }
  inline const String & getSSID() const {
    return ssid;
  }
  inline const String & getPassword() const {
    return password;
  }
   
  inline const String & getWWWPassword() const {
    return www_password;
  }  

  inline const String & getWWWUser() const {
    return www_username;
  }
private:
  void readConfig();
  void readPowerState();
  bool powerState = 0;

  String ssid = "Appartement Associes";
  String password = "motComplique";

  String www_username = "admin";
  String www_password = "motComplique2";

  const char * config_file = "config.txt";
  const char * power_file = "power.txt";
  Preferences config;
  Preferences powerperf;
};
#endif
