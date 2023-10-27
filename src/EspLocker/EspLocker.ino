// ligne a commenter en cas d'un ESP8266
//#define ESP32 1 

#ifdef ESP32
#include <WiFi.h>  // il s’agit d’un ESP32
#define NOTIFICATION_CONNECTION_WIFI SYSTEM_EVENT_AP_STACONNECTED
#else
#include <ESP8266WiFi.h>
#define NOTIFICATION_CONNECTION_WIFI WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP
#endif
#include <DNSServer.h>
#include "config.h"
#include "web.h"
Config myConfig;
Web web(myConfig);

const byte DNS_PORT = 53;  // Capture DNS requests on port 53
IPAddress local_IP(192, 168, 0, 1);
IPAddress subnet(255,255,255,0);
bool openTheDoor=false;
DNSServer dnsServer;

void openDoor(){
    digitalWrite(LED_BLUE, LOW);
    Serial.println("open");
    digitalWrite(RELAY_DOOR,HIGH);
    delay(10000);
    digitalWrite(RELAY_DOOR,LOW);
    digitalWrite(LED_BLUE, HIGH);
    openTheDoor = false;
}



void setup() {
  Serial.begin(9600);
  myConfig.init();
  pinMode(RELAY_DOOR,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  digitalWrite(LED_BLUE,LOW); // low allume la  led !!!
  digitalWrite(RELAY_DOOR,LOW);
  Serial.print("Start WiFi ... ");
  WiFi.softAPConfig(local_IP, local_IP, subnet) ;
  WiFi.onEvent([](WiFiEvent_t a) {openTheDoor=true;},NOTIFICATION_CONNECTION_WIFI);
  WiFi.softAP(myConfig.getSSID().c_str(), myConfig.getPassword().c_str());
  dnsServer.start(DNS_PORT, "*", local_IP);
  web.init();

  delay(500); // pour voir la led allumee au demarrage
  digitalWrite(LED_BLUE,HIGH); // high eteint la  led !!!
}


void loop() {
  if(openTheDoor) openDoor();
  int nbClient = WiFi.softAPgetStationNum();
  char msg [8];
  sprintf(msg,"gpio %d", digitalRead(0));
  if(digitalRead(0) == 0){
    myConfig.factoryReset();
  }
  //String msg = "gpio 0 "+ digitalRead(0);
  //Serial.println(msg);
  if (nbClient > 0) {
    dnsServer.processNextRequest();
    web.handleClient();
  } else{
      if(web.haveToReboot()){
        ESP.restart();
      }
     delay(500);
  }

 }
