#include <Arduino.h>
#define SWITCH_PIN_DAY   3
#define SWITCH_PIN_NIGHT 2
//#define ADDITIONAL_LEDS // Uncomment to control additional leds

unsigned long uTime; 
bool          bUpdate;
const unsigned long DURATION  =  23 * 1000;//23sec

#ifdef ADDITIONAL_LEDS
unsigned int LightsPins[12] = {
  13, 12, 11,
  10,  9,  8,
   7,  6,  5,
   4
};
const size_t TotalPins = sizeof(LightsPins) / sizeof(LightsPins[0]);
#else
unsigned int *LightsPins = nullptr;
const size_t TotalPins = 0;
#endif

void setup()
{
    pinMode(SWITCH_PIN_DAY, OUTPUT);
    pinMode(SWITCH_PIN_NIGHT, OUTPUT);
    uTime = millis();
    bUpdate = rand() % 2 == 0;

    for (size_t i = 0; i < TotalPins; i++)
    {
       pinMode(LightsPins[i], OUTPUT);
    }

    if (bUpdate){//Day
       SetDay();
    } else {
       SetNight();
    }
}

void swap (unsigned int& a, unsigned int& b)
{
    unsigned int c = a;
    a = b;
    b = c;
}

void shuffle(unsigned int *arr, size_t len)
{
    if (len < 1 || !arr) 
    {
        return;
    }
    for (size_t i = 0; i < len; i++) 
    {
        size_t j = rand() % len;
        swap(arr[i], arr[j]);
    }
}

void SetDay()
{
    digitalWrite(SWITCH_PIN_DAY, HIGH);
    digitalWrite(SWITCH_PIN_NIGHT, LOW);

    shuffle(LightsPins, TotalPins);
    for (size_t i = 0; i < TotalPins; i++)
    {
        digitalWrite(LightsPins[i], HIGH);
        delay(250);
    }
}
void SetNight()
{
    digitalWrite(SWITCH_PIN_DAY, LOW);
    digitalWrite(SWITCH_PIN_NIGHT, HIGH);

    shuffle(LightsPins, TotalPins);
    for (size_t i = 0; i < TotalPins; i++)
    {
        digitalWrite(LightsPins[i], LOW);
        delay(250);
    }
}

void updateAndWriteDate()
{
    unsigned long uNow = millis();
    if (uNow - uTime > DURATION){
        if (bUpdate) {//Day
            SetDay();
        } else {
            SetNight();
        }
        bUpdate = !bUpdate;
        uTime = uNow;
    }
}

void loop()
{
    updateAndWriteDate();
    delay(250);   
}
