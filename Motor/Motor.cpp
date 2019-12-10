#include "Motor.h"
#include <Arduino.h>
#include <stdbool.h>

SingleMotor::SingleMotor(int forwardPin, int backwardPin){
    this->forwardPin = forwardPin;
    this->backwardPin = backwardPin;
}

void SingleMotor::forward(){
    digitalWrite(forwardPin, HIGH);
    digitalWrite(backwardPin, LOW);
}

void SingleMotor::reverse(){
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, HIGH);
}

void SingleMotor::stop(){
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, LOW);
}

String SingleMotor::toString(){  
    return "forwardPin: " + String(forwardPin) + " backwardPin: " + String(backwardPin);
}

CarMotor::CarMotor(SingleMotor left, SingleMotor right) : left(left),right(right){}

void CarMotor::forward(){
    left.forward();
    right.forward();
}

void CarMotor::reverse(){
    left.reverse();
    right.reverse();
}

void CarMotor::stop(){
    left.stop();
    right.stop();
}

void CarMotor::leftActive(bool sharpTurn){
    if(sharpTurn){
        left.forward();
        right.reverse();
    }else{
        left.forward();
        right.stop();
    }
}

void CarMotor::rightActive(bool sharpTurn){
    if(sharpTurn){
        left.reverse();
        right.forward();
    }else{
        left.stop();
        right.forward();
    }
}

String CarMotor::toString(){
    return left.toString() + "\n" + right.toString();
}