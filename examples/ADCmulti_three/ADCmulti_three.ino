/*
	Three analog ports reading example
*/

#include "ADCmulti.h"
ADCmulti AnalogMulti(A1, A2, A3);

void setup()
{
  Serial.begin(115200);
  delay(500);

  AnalogMulti.init();

  delay(500);
}

void loop()
{
  AnalogMulti.check();

  Serial.println(AnalogMulti.read(A1));
  Serial.println(AnalogMulti.read(A2));
  Serial.println(AnalogMulti.read(A3));
  Serial.println("+++");

  delay(1000);
}
