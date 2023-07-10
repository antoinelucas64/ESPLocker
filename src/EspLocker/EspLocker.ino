// ligne a commenter en cas d'un ESP8266
//#define ESP32 1 

#ifdef ESP32
#include <WiFi.h>  // il s’agit d’un ESP32
#define NOTIFICATION_CONNECTION_WIFI SYSTEM_EVENT_AP_STACONNECTED
#define LED_BLUE  13
#else
#include <ESP8266WiFi.h>
#define NOTIFICATION_CONNECTION_WIFI WIFI_EVENT_SOFTAPMODE_DISTRIBUTE_STA_IP
#define LED_BLUE  2
#endif
#define RELAY_DOOR 4

String ssid = "Antoine & Associés";
String password = "9876543210";
IPAddress local_IP(192,168,0,0);
IPAddress subnet(255,255,255,0);
bool openTheDoor=false;

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
  pinMode(RELAY_DOOR,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  digitalWrite(LED_BLUE,LOW); // low allume la  led !!!
  digitalWrite(RELAY_DOOR,LOW);
  Serial.print("Start WiFi ... ");
  WiFi.softAPConfig(local_IP, local_IP, subnet) ;
  WiFi.onEvent([](WiFiEvent_t a) {openTheDoor=true;},NOTIFICATION_CONNECTION_WIFI);
  WiFi.softAP(ssid.c_str(),password.c_str()) ;
  delay(500); // pour voir la led allumee au demarrage
  digitalWrite(LED_BLUE,HIGH); // high eteint la  led !!!
}

void loop() {
  if(openTheDoor) openDoor();
  delay(100);
 }
