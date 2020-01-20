#include <Motor.h>
#include <Wire.h>
#define buzz 2
#define motorRF 3
#define motorRB 4
#define motorLF 5
#define motorLB 6
#define trigPin 7
#define echoPin 8
#define trigPinR 9
#define echoPinR 10
#define trigPinL 11
#define echoPinL 12
#define reed 13
#define IrR A1
#define IrL A2
#define IrV A3
unsigned long previousMillis = 0;     //Timer 1, na 0,1s 90-draai
unsigned long previousMillis2 = 0;    //Timer 2, binnen 5s 180-draai

volatile byte state = LOW;
//bool on = false;
long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
int turn = 0;
int aan = 0;

//motor rijden
SingleMotor rechts= SingleMotor(motorRF,motorRB);
SingleMotor links= SingleMotor(motorLF,motorLB);
CarMotor motor= CarMotor(links, rechts);

//us sensors
long duration, distance;
long durationR, distanceR;
long durationL, distanceL;

void setup() {
Wire.begin(8);
Wire.onReceive(receiveEvents);
Wire.onRequest(requestEvents);
Serial.begin(9600);

//buzzer
pinMode (buzz, OUTPUT);

//reed sensor
pinMode (reed, INPUT);

//ir sensor 
pinMode (IrR, INPUT);
pinMode (IrL, INPUT);
pinMode (IrV, INPUT);

//us sensor voorkant
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

//us sensor rechts
pinMode(trigPinR,OUTPUT);
pinMode(echoPinR, INPUT);

//us sensor links
pinMode(trigPinL,OUTPUT);
pinMode(echoPinL, INPUT);


}
void loop() {
   unsigned long startMillis = millis();
   int reedValue = digitalRead(reed);
   if (aan == 1){                             //wanneer 1 wordt de automatische stand gestart
    drive();      
   }
   else{                                      //wanneer 0 wordt doet de robot niks en is deze beschikbaar voor handmatige opties
   }
   //Serial.println(aan);
    delay(1);
    Serial.println(reedValue);
   if (reedValue == LOW){
    motor.stop();
    aan = 0;
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
   }
}
void drive(){
     motor.forward();                         //vooruit rij funtie
     readus();                                //read de us  voorkant waarde en corrigeert wanneer nodig
     readusR();                               //read de rechter us waarde en corrigeert wanneer nodig
     readusL();                               //read de linker us waarde en corrigeert wanneer nodig
     readir();                                //read de ir waardes en corrigeert wanneer nodig
}

void draai90(){
  unsigned long startMillis = millis();
  
   if (startMillis - previousMillis >= 100){                              //functie zodat de robot een 90 draai maakt of 270 draai
    //Serial.println("Draaien 90");
    int statusSensorV = digitalRead (IrV);  
    motor.reverse();
    delay(750);
    motor.leftActive(true);
    delay(1375);
    motor.forward();
    previousMillis = startMillis;
      if (statusSensorV == 1 && startMillis - previousMillis2 <= 5000){   //als er binnen 5s weer een zwarte lijn/niks is wordt er een 180 draai achteraan gedaan, na 5s gaat de robot weer naar de loop
        motor.leftActive(true);
        delay(2250);
        motor.forward();
        //Serial.println("draaien 180");
       }
       else {                                                             //reset timers   
          previousMillis = startMillis;
          previousMillis2 = startMillis;
       }
   }
 }

void draai180(){                                                         //functie zodat de robot een 180 draai maakt
  motor.reverse();
  delay(750);
  motor.leftActive(true);
  delay(2250);
  motor.forward();
}
void corRechts(){
  //Serial.println("stukkie naar links");                                //functie zodat de robot van een rechter lijn/muur weg rijdt
  motor.leftActive(true);
  delay(200);
  motor.forward();
  delay(100);
  motor.rightActive(true);
  delay(50);
}
void corLinks(){                                                         //functie zodat de robot van een linker lijn/muur weg rijdt
  //Serial.println("stukkie naar rechts");
  motor.rightActive(true);
  delay(200);
  motor.forward();
  delay(100);
  motor.leftActive(true);
  delay(50);
}

void readir(){
  int statusSensorR = digitalRead (IrR);
  int statusSensorL = digitalRead (IrL);
  int statusSensorV = digitalRead (IrV);
   if (statusSensorR == 1 && statusSensorL ==1){      //zolang de linker en rechter ir 'iets' zien rijdt de robot vooruit
    statusSensorR = 0;
    statusSensorL = 0;
  }
   else if (statusSensorR == 1){                       //als rechter ir een zwarte lijn/niks ziet rijdt de robot een stukje naar links
    corRechts();
  }
   else if (statusSensorL == 1){                       //als linker ir een zwarte lijn/niks ziet rijdt de robot een stukje naar rechts
    corLinks();
  }
   if (statusSensorV == 1){                            //als de voorste ir een zwarte lijn/niks ziet maakt de robot een 90 draai (dit kan worden vervolgd door een 180 draai zie draai90 functie)
    //Serial.println("draai90");
    draai90();
  }
   else if(statusSensorV == 0){                        //zolang de voorste ir sensor 'iets' zijn rijdt de robot vooruit
    statusSensorR = 0;
    statusSensorL = 0;
  }
}


void readus(){                              //functie als er een object dichter dan 5cm bij de voorste us staat, dan 180 draai
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    //Serial.println(distance);
    if(distance<5){
      draai180();
    }
}
void readusR(){                            //functie als rechter us waarde kleiner dan 5cm wordt rijdt de robot een stukje naar links
    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    durationR = pulseIn(echoPinR, HIGH);
    distanceR = (durationR/2) / 29.1;
    //Serial.println(distanceR);
    if(distanceR<5){
      corRechts();
    }
}
void readusL(){                          //functie als linker us waarde kleiner dan 5cm wordt rijdt de robot een stukje naar rechts
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    durationL = pulseIn(echoPinL, HIGH);
    distanceL = (durationL/2) / 29.1;
    //Serial.println(distanceL);
    if(distanceL<5){
      corLinks();
    }
}
void receiveEvents(int x) {               //waardes via die esp binnen komen en doorkomen naar arduino (i2c)
  int input = Wire.read();
  //Serial.println(input);
    if (input == 0){                      //stopt alle motor
      motor.stop();
    }
    while (input == 1){                   //vooruit
      motor.forward();
      input = Wire.read();
    }
    while (input == 2){                   //achteruit
      motor.reverse();
      input = Wire.read();
    }
    while (input == 3){                   //draait naar rechts
      motor.rightActive(true);
      input = Wire.read();
    }
    while (input == 4){                   //draait naar links
      motor.leftActive(true);
      input = Wire.read();
    }
    if (input == 5){                      //gaat naar automatische stand
      //Serial.println("Automatisch");
      aan = 1;
    }
    if(input == 6){                       //gaat naar manual stand
      //Serial.println("Manual");
      aan = 0;
    }
}
void requestEvents(){
  Wire.write(9);
}
