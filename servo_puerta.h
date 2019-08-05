/**
  Controla las acciones del servo
*/
#ifndef servoPuerta_h
#define servoPuerta_h
#include <Servo.h>
#include <Arduino.h>

// Puerto del servo
const int SERVO_PORT = 3;
// Angulos de apertura de servo
const int ABIERTO = 165;
const int CERRADO = 15;

class SG90
{
  public:
    SG90();
    
    SG90(Servo *_sg90);

    SG90(int port, Servo *_sg90);

    void abrir();

    void cerrar();

    int getAngle();

  private:
    Servo sg90;
    int angle;
};
#endif
