/**
  Controla las acciones del servo
*/

#include "servo_puerta.h"

//Servo sg90;

SG90::SG90() {}

SG90::SG90(Servo *_sg90)
{
  sg90 = *_sg90;
  sg90.attach(SERVO_PORT);
}

SG90::SG90(int port, Servo *_sg90)
{
  sg90 = *_sg90;
  sg90.attach(port);
}

void SG90::abrir()
{
  for (angle = CERRADO; angle < ABIERTO; angle += 2) { // goes from 180 degrees to 0 degrees
    sg90.write(angle);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
}

void SG90::cerrar()
{
  for (angle = ABIERTO; angle > CERRADO; angle -= 2) { // goes from 180 degrees to 0 degrees
    sg90.write(angle);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
}

int SG90::getAngle()
{
  return angle;
}
