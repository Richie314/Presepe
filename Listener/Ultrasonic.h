#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "Types.h"
class Ultrasonic
{
    uint8 uTrig, uEcho;
public:
    /*
     * @param Trig The trigger pin for the sensor
     * @param Echo The echo pin for the sensor
     */
    Ultrasonic(uint8 Trig, uint8 Echo);
    /*
     * @param Vcc The pin for the Vcc input of the sensor: it is set to OUTPUT and and HIGH is written to it 
     * @param Trig The trigger pin for the sensor
     * @param Echo The echo pin for the sensor
     */
    Ultrasonic(uint8 Vcc, uint8 Trig, uint8 Echo);
    /*
     * @param Vcc The pin for the Vcc input of the sensor: it is set to OUTPUT and and HIGH is written to it 
     * @param Trig The trigger pin for the sensor
     * @param Echo The echo pin for the sensor
     * @param Gnd The pin for the Groung of the sensor: it is set to OUTPUT and and LOW is written to it 
     */
    Ultrasonic(uint8 Vcc, uint8 Trig, uint8 Echo, uint8 Gnd);
private:
    unsigned long rawRead()const;
public:
    inline float32 read_m()const
    {
        return this->rawRead() / 5820.0F;
    }
    constexpr inline float32 read_cm()const
    {
        return this->rawRead() / 58.2F;
    }
    inline float32 read_mm()const
    {
        return this->rawRead() / 5.82F;
    }
    inline Ultrasonic& operator = (const Ultrasonic& sensor)
    {
        this->uEcho = sensor.uEcho;
        this->uTrig = sensor.uTrig;
        return *this;
    }
    constexpr inline float32 operator () () const
    {
        return this->read_cm();
    }
};
inline float32& operator >> (const Ultrasonic& sensor, float& fNumber)
{
    fNumber = sensor.read_cm();
    return fNumber;
}
#endif
