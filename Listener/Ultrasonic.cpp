#include "Ultrasonic.h"
#include <Arduino.h>
unsigned long Ultrasonic::rawRead()const
{
    digitalWrite(this->uTrig, LOW);
    delayMicroseconds(2U);
    digitalWrite(this->uTrig, HIGH);
    delayMicroseconds(10U);
    digitalWrite(this->uTrig, LOW);
    return pulseIn(this->uEcho, HIGH);
}
Ultrasonic::Ultrasonic(uint8 Trig, uint8 Echo) : uTrig(Trig), uEcho(Echo) 
{
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);  
};
Ultrasonic::Ultrasonic(uint8 Vcc, uint8 Trig, uint8 Echo) : Ultrasonic(Trig, Echo)
{
    pinMode(Vcc, OUTPUT);
    digitalWrite(Vcc, HIGH);
};
Ultrasonic::Ultrasonic(uint8 Vcc, uint8 Trig, uint8 Echo, uint8 Gnd) : Ultrasonic(Vcc, Trig, Echo)
{
    pinMode(Gnd, OUTPUT);
    digitalWrite(Gnd, LOW);
};