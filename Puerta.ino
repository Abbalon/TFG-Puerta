/* Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#include "puerta.h"
#include "servo_puerta.h"

SG90 cerradura;
Servo servo;

// the setup function runs once when you press reset or power the board
void setup()
{
  cerradura = SG90(&servo);
  Serial.println(cerradura.getAngle());
  //Configuración del puerto serial
  Serial.begin(BAUDRATE);

  // Inicialización de los pin led
  pinMode(OK_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);
  pinMode(WARN_LED, OUTPUT);
  pinMode(MONITOR_LED, OUTPUT);

  cerradura.abrir();
  cerradura.cerrar();
  cerradura.abrir();

  Serial.println(allItWorks());
}

// the loop function runs over and over again forever
void loop()
{
  cerradura.abrir();

  digitalWrite(OK_LED, 1);
  delay(500);
  digitalWrite(OK_LED, 0);
  digitalWrite(WARN_LED, 1);
  delay(500);
  digitalWrite(WARN_LED, 0);
  digitalWrite(ERROR_LED, 1);
  delay(500);
  digitalWrite(ERROR_LED, 0);

  cerradura.cerrar();
  delay(5000);
}
