#include <Motor.h>
#define motorRF 3
#define motorRB 4
#define motorLF 5
#define motorLB 6
#define trigPin 7
#define echoPin 8
const byte interruptPin = 2;
volatile byte state = LOW;

long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

SingleMotor rechts= SingleMotor(motorRF,motorRB);
SingleMotor links= SingleMotor(motorLF,motorLB);
CarMotor motor= CarMotor(links, rechts);

bool on = false;


void setup() {
Serial.begin (9600);

pinMode(trigPin, OUTPUT);

pinMode(echoPin, INPUT);

pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), onoff, RISING);
}

void loop() {
  if(on){
    motor.forward();
    // put your main code here, to run repeatedly:
    long duration, distance;

    digitalWrite(trigPin, LOW);

    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = (duration/2) / 29.1;

    if(distance<5){
      draai180();
    }

    
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
  motor.reverse();
  delay(1000);
  motor.leftActive(true);
  delay(1700);
  motor.forward();
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
