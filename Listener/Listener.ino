#include "Ultrasonic.h"
// Time of the previous millis() read
uint64 uOldTime = 0;
// The maximun time the object can stay active with no one watching
uint64 uMaxTimeOpen = 20 * 1000;
bool   bIsRunning = true; // Records if the object is open
bool   bLeft = true;

#define RELAY_PIN 7
#define ULTRASONIC_1_PINS 9, 10, 11, 12
#define EMULATE_VCC_PIN

//#define ULTRASONIC_2_PINS 12, 13 // Uncomment if you have two sensors
//#define USE_SERIAL // Uncomment to log data on serial


#define OPEN LOW
#define CLOSED HIGH

void setup()
{
    bIsRunning = true;
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, CLOSED);
    uOldTime = millis();
#ifdef USE_SERIAL
    Serial.begin(9600);
#endif
}

///
/// Gloabal variables here
///
Ultrasonic left(ULTRASONIC_1_PINS);
#ifdef ULTRASONIC_2_PINS
    Ultrasonic right(ULTRASONIC_2_PINS)
#endif

void loop()
{
#ifdef ULTRASONIC_2_PINS
    float fRead = bLeft ? left.read_m() : right.read_m();
#else
    float fRead = left.read_m();
#endif

#ifdef USE_SERIAL
    Serial.print(bLeft ? "Left: " : "Right: ");
    Serial.print(fRead);
    Serial.println(bIsRunning ? "\tStatus: Running" : "\tStatus: Shut");
#endif

#ifdef ULTRASONIC_2_PINS
    bLeft = !bLeft;
#endif

    if (fRead < 0.5F)
    {
        // Someone is in front of the diorama
        uOldTime = static_cast<uint64>(millis());
        if (!bIsRunning)
        {
            // It is shut down -> we start it
#ifdef USE_SERIAL
            Serial.println("-------------------------------------");
            Serial.println("           LIGHTING NOW");
            Serial.println("-------------------------------------");
#endif
            bIsRunning = true;
            digitalWrite(RELAY_PIN, CLOSED); //Close the switch (start it)
        }
    } else {
        // No one is in front of the diorama
        if (static_cast<uint64>(millis()) - uOldTime > uMaxTimeOpen)
        {
            if (bIsRunning)
            {
                // It is on -> we shut it down
#ifdef USE_SERIAL
                Serial.println("-------------------------------------");
                Serial.println("           SHUTTING NOW");
                Serial.println("-------------------------------------");
#endif
                bIsRunning = false;
                digitalWrite(RELAY_PIN, OPEN); // Open the switch (shut it down)
            }
        }
    }
    delay(200);
}