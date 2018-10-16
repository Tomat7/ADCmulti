/*
 * No reason to work with library if you need to collect data from ONE pin.
 * Just for testing!
 */
int Voltage;

#include "AMread.h"
AMread AnalogMultiRead;

int Pins[] = { A1 };
int Vals[] = { &Voltage };
const int numSensors = sizeof(Pins) / sizeof(int);

void setup()
{
  Serial.begin(115200);
  delay(500);

  AnalogMultiRead.init(numSensors, Pins, Vals);

  delay(500);
}

void loop()
{
  AnalogMultiRead.check();

  Serial.println(Voltage);
  Serial.println("+++");

  delay(1000);
}

