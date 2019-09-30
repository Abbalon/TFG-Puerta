/**

*/

#include "puerta.h"

int allItWorks()
{
  //Comprobaciones de funcionamiento
  Serial.println("Hola User");
  controlLed(MONITOR_LED, 2, 100);
  controlLed(OK_LED, 2, 100);
  controlLed(WARN_LED, 2, 100);
  controlLed(ERROR_LED, 2, 100);

  return 1;
}

void controlLed(int pin, int times, int wait)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(pin, 1);
    //analogWrite(pin, 200);
    delay(wait);
    digitalWrite(pin, 0);
    //analogWrite(pin, 0);

    if (i + 1 < times)
    {
      delay(wait);
    }
  }
}
