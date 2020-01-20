#include <ESP8266WiFi.h>
#include <Wire.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "69WwIT9hc4VvB0oDyXua-YPRAsnKufww"; //nog invullen (auth key)

char ssid[] = "Tesla IoT";
char pass[] = "fsL6HgjN";


void setup()
{
  Serial.begin(9600);
  Wire.begin(D1, D2);
  Blynk.begin(auth, ssid, pass);
}


void loop()
{
  Blynk.run();
 
}


//Vooruit:
BLYNK_WRITE(V0) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(1); 
  Wire.endTransmission();    /* stop transmitting */  
}
//Achteruit:
BLYNK_WRITE(V3) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(2);  
  Wire.endTransmission();    /* stop transmitting */
}
//Links:
BLYNK_WRITE(V1) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(3);  
  Wire.endTransmission();    /* stop transmitting */
}
//Rechts:
BLYNK_WRITE(V2) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(4);  
  Wire.endTransmission();    /* stop transmitting */
}
//Stoppen:
BLYNK_WRITE(V4) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(0);  
  Wire.endTransmission();    /* stop transmitting */
}
//Manual:
BLYNK_WRITE(V5) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(5);  
  Wire.endTransmission();    /* stop transmitting */
}
//Achteruit:
BLYNK_WRITE(V6) {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write(6);  
  Wire.endTransmission();    /* stop transmitting */
}
