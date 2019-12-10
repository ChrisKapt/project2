#include <Motor.h>

#define motorRF 2
#define motorRB 3
#define motorLF 4
#define motorLB 5

SingleMotor rechts= SingleMotor(motorRF,motorRB);
SingleMotor links= SingleMotor(motorLF,motorLB);
CarMotor motor= CarMotor(links, rechts);

void setup() {
  // put your setup code here, to run once:
  
  //motor.forward();
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.forward();
  delay(1000);
  motor.reverse();
  delay(1000);
  motor.stop();
  delay(1000);
  motor.leftActive(true);
  delay(1000);
  motor.rightActive(true);
  delay(1000);
}
