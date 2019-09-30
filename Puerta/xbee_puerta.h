/* Este bloque contendrá el código que definirá la gestión del módulo XBEE */

#ifndef xbeePuerta_h
#define xbeePuerta_h
#include <Vector.h>
#include <XBee.h>
#include <Arduino.h>

// Constantes que recogen los tiempos de espera
const int MED_SEC = 500;
const int FIVE_SEC = 5000;

//Dirección del coordinador
const XBeeAddress64 BROADCAST = XBeeAddress64(0x00000000, 0x0000FFFF); //Este código de antena es siempre igual,
// mandará la señal a discrección, a cualquiera que pueda recibirla
const XBeeAddress64 COORDINADOR = XBeeAddress64(0x0013A200, 0x415135C7); //Ajustar en cada instalación
const XBeeAddress64 PROPIA = XBeeAddress64(0x0013A200, 0x41513615);      //Ajustar en cada instalación

//Codigos de respuesta
const int ACK_OK = 500;

//Elementos para el control del array de paquetes recibidos
const int ELEMENT_COUNT = 5;
//Opciones de salida de lectura
const int GOT_ACK = 0;
const int NOT_GOT_ACK = 1;
const int ERROR_RX = -2;

class S2C
{
public:
    S2C();

    /** Inicializamos la antena con la referencia de la antena*/
    S2C(const XBee &_antena);

    /** Mandará el mensaje a receptor indicado */
    bool mandarMensaje(const XBeeAddress64 &_destino, String _mensaje);

    /** Mandará el mensaje al coordinador configurado */
    bool mandarMensaje(String _mensaje);

    int leerMensaje();

private:
    XBee xbee = XBee();

    /************************************************************************/
    /* Funciones propias para el funcionamiento de la clase                 */
    /************************************************************************/
    void serializar(String _mensaje);

    /************************************************************************/
    //Objetos para recibir datos
    /************************************************************************/
    ZBRxResponse storage_array[ELEMENT_COUNT];
    Vector<ZBRxResponse> rxMsg;
    XBeeResponse response = XBeeResponse();
    ZBRxResponse rx = ZBRxResponse();

    ModemStatusResponse msr = ModemStatusResponse();

    /************************************************************************/
    // Objetos para mandar datos
    /************************************************************************/
    //Guarda los datos recibidos
    uint8_t *msg;
    uint8_t sizeMsg = 0;
    //Paquete a mandar
    ZBTxRequest zbTx = ZBTxRequest(COORDINADOR, msg, sizeMsg);
    /************************************************************************/

    //Estado del canal
    ZBTxStatusResponse txStatus = ZBTxStatusResponse();
};
#endif
