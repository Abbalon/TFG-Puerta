/* Este bloque contendrá el código que definirá la gestión del módulo XBEE */

#ifndef xbeePuerta_h
#define xbeePuerta_h

#include <Arduino.h>
#include <Printers.h>
#include <XBee.h>

//Dirección del coordinador
const XBeeAddress64 BROADCAST = XBeeAddress64(0x00000000, 0x0000FFFF);
// XBeeAddress64 coordinador = XBeeAddress64(0x0013A200, 0x415135C7); //Ajustar en cada instalación

//Codigos de respuesta
const int ACK_OK = 500;

class S2C
{
public:
    S2C();

    /** Inicializamos la antena con la referencia de la antena y su coordinador de red */
    S2C(XBee &_antena, XBeeAddress64 &_coodinador);

    /** Mandará el mensaje a receptor indicado */
    bool mandarMensaje(XBeeAddress64 &_destino, String _mensaje);

    /** Mandará el mensaje al coordinador configurado */
    bool mandarMensaje(String _mensaje);

private:
    XBee xbee = XBee();
    //Objetos para recibir datos
    XBeeResponse response = XBeeResponse();
    ZBRxResponse rx = ZBRxResponse();

    ModemStatusResponse msr = ModemStatusResponse();

    // Objetos para mandar datos
    //Dirección de envio
    XBeeAddress64 coordinador;
    XBeeAddress64 destino;
    //Paquete a mandar
    ZBTxRequest zbTx = ZBTxRequest(coordinador, payload, sizeof(payload));

    //Guarda los datos recibidos
    uint8_t *value;
    uint8_t sizePayload = 0;

    //Estado del canal
    ZBTxStatusResponse txStatus = ZBTxStatusResponse();
};
#endif
