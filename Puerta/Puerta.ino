/** Sketch del sistema de control de acceso.
 * A traves de un lector de targetas RFID, capturará quien quiere acceder al recinto
 * enviará el código al servidor, que comprobará su autenticidad y los permisos que tenga
 * asociados y devolverá la respuesta adecuada. 
 * Si la respuesta recibida es satisfactoria, el sistema actuará sobre la cerradura electrónica,
 * ordenando la apertura, en otro caso, no realizará ninguna acción.
 */

#include "puerta.h"
#include "servo_puerta.h"

SG90 cerradura;
Servo servo;

// the setup function runs once when you press reset or power the board
void setup()
{
  cerradura = SG90(servo);
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
