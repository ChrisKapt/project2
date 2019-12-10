#include <Motor.h>
#define motorRF 3
#define motorRB 4
#define motorLF 5
#define motorLB 6
#define trigPin 7
#define echoPin 8
#define echoPinR 10
#define trigPinR 9
#define echoPinL 12
#define trigPinL 11

//button variabelen
const byte interruptPin = 2;
volatile byte state = LOW;
bool on = false;
long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

//motor rijden
SingleMotor rechts= SingleMotor(motorRF,motorRB);
SingleMotor links= SingleMotor(motorLF,motorLB);
CarMotor motor= CarMotor(links, rechts);

//us sensors
long duration, distance;
long durationR, distanceR;
long durationL, distanceL;

void setup() {
Serial.begin(9600);

//us sensors
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(trigPinR,OUTPUT);
pinMode(echoPinR, INPUT);

pinMode(trigPinL,OUTPUT);
pinMode(echoPinL, INPUT);

//voor de button aan en uit
pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), onoff, RISING);
}

void loop() {
  Serial.println("print ik iets?");
  if(on){
    motor.forward();
    readus();
    readusR();
  }else{
    motor.stop();
  }
}

void onoff(){
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    on=!on;
    Serial.println("nu aan of uit");
    last_micros = micros();
  }
}

void draai180(){
  Serial.println("draaien");
  motor.reverse();
  delay(1000);
  motor.leftActive(true);
  delay(1700);
  motor.forward();
}
void corRechts(){
  Serial.println("stukkie naar links");
  motor.leftActive(true);
  delay(500);
  motor.forward();
  delay(1000);
  motor.rightActive(true);
  delay(500);
}
void corLinks(){
  Serial.println("stukkie naar rechts");
  motor.rightActive(true);
  delay(500);
  motor.forward();
  delay(1000);
  motor.leftActive(true);
  delay(500);
}

void readus(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    
    distance = (duration/2) / 29.1;

    Serial.println(distance);
    
    if(distance<5){
      draai180();
    }
}
void readusR(){
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    durationR = pulseIn(echoPinR, HIGH);
    distanceR = (durationR/2) / 29.1;
    Serial.println(distanceR);
    if(distanceR<5){
      corRechts();
    }
}
void readusL(){
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    durationL = pulseIn(echoPinL, HIGH);
    distanceL = (durationL/2) / 29.1;
    Serial.println(distanceL);
    if(distanceL<5){
      corLinks();
    }
}
/*
  void loop()

if(
{ long duration, distance;

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance = (duration/2) / 29.1;

if (distance < 5)
}
*/
