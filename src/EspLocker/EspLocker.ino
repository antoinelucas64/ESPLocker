#include <ESP8266WiFi.h>

String ssid = "Antoine & Associés";
String password = "987654321";
int pinDoor=4;
#define LED_BLUE  2
int nbClient;
IPAddress local_IP(10,10,10,10);
IPAddress subnet(255,255,255,0);

void openDoor(){
    digitalWrite(LED_BLUE, LOW);
    Serial.println("open\n");
    digitalWrite(pinDoor,HIGH);
    delay(10000);
    digitalWrite(pinDoor,LOW);
    digitalWrite(LED_BLUE, HIGH);
}

void checkDoor(){
 int current = WiFi.softAPgetStationNum();
  if( current > nbClient ) openDoor();
  nbClient = current;
}


void setup() {
  nbClient = 0;
  Serial.begin(115200);
  pinMode(pinDoor,OUTPUT);
  pinMode(LED_BLUE,OUTPUT);
  digitalWrite(LED_BLUE,LOW); // low allume la  led !!!
  digitalWrite(pinDoor,LOW);
  Serial.print("Start WiFi ... ");
  WiFi.softAPConfig(local_IP, local_IP, subnet) ;
  WiFi.softAP(ssid,password) ;
  delay(500); // pour voir la led allumee au demarrage
  digitalWrite(LED_BLUE,HIGH); // high eteint la  led !!!
}

void loop() {
  checkDoor();
  delay(1000);
 }
