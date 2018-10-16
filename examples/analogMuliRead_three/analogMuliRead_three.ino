
int Pressure, Voltage, Temperature;

#include "AMread.h"
AMread AnalogMultiRead;

int Pins[] = {A1, A2, A3};
int Vals[] = {&Pressure, &Voltage, &Temperature};
const int numberOfSensors = sizeof(Pins) / sizeof(int);

void setup()
{
  Serial.begin(115200);
  delay(500);

  AnalogMultiRead.init(numberOfSensors, Pins, Vals);

  delay(500);
}

void loop()
{
  AnalogMultiRead.check();

  Serial.println(Pressure);
  Serial.println(Voltage);
  Serial.println(Temperature);
  Serial.println("+++");

  delay(1000);
}

