/*
	Three analog ports reading example
*/

#include "ADCmulti.h"
ADCmulti AnalogMulti(A1, A2, A3);

long int msMillis;

void setup()
{
  Serial.begin(115200);
  delay(300);
  AnalogMulti.init();
  msMillis = millis();
  delay(200);
}

void loop()
{
  AnalogMulti.check();
  
  if ((millis() - msMillis) > 1000)
  {
    Serial.println(AnalogMulti.read(A1));
    Serial.println(AnalogMulti.read(A2));
    Serial.println(AnalogMulti.read(A3));
    Serial.println("+++");
    msMillis = millis();
  }
}
