#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define DEG180 1500

class SingleMotor{

    public:
    int forwardPin;
    int backwardPin;

    SingleMotor(int forwardPin, int backwardPin);
    void forward();
    void reverse();
    void stop();
    String toString();

};

class CarMotor{
    private:
    SingleMotor left;
    SingleMotor right;

    public:
    CarMotor(SingleMotor left, SingleMotor right);
    void forward();
    void reverse();
    void stop();
    void leftActive(bool sharpTurn);
    void rightActive(bool sharpTurn);
    String toString();
};

#endif