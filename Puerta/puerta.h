/**
   Libreria que recoge las constantes de los leds, los mensages, los angulos de apertura del servo
*/
#ifndef puerta_h
#define puerta_h
#include <Arduino.h>

// Comunicación por los seriales
const int BAUDRATE = 9600;

// Id's de los leds
const int OK_LED = 4;
const int MONITOR_LED = 13;
const int WARN_LED = 5;
const int ERROR_LED = 6;

int allItWorks();

void controlLed(int pin, int times, int wait);

#endif
