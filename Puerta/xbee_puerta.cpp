/* Este bloque contendrá el código que gestionará del módulo XBEE */

#include "xbee_puerta.h"

S2C::S2C() {}

/** Inicializamos la antena con la referencia de la antena y su coordinador de red */
S2C::S2C(const XBee &_antena, const XBeeAddress64 &_coodinador)
{
    xbee = _antena;
    coodinador = _coodinador;
}

/** Transformará el String del mensaje a un formato que se pueda enviar
 * por la antena ZigBee
*/
uint8_t S2C::serializar(String _mensaje)
{
    //TODO
    return sizeof(_mensaje);
}

/** Mandará el mensaje a receptor indicado */
bool S2C::mandarMensaje(const XBeeAddress64 &_destino, String _mensaje)
{
    bool exito = false;
    uint8_t sizePayload = serializar(_mensaje);
    zbTx = ZBTxRequest(_destino, msg, sizePayload);

    xbee.send(zbTx);

    //Esperamos respuesta
    if (xbee.readPacket(500))
    {
        if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)
        {
            xbee.getResponse().getZBTxStatusResponse(txStatus);

            // get the delivery status, the fifth byteat
            if (txStatus.getDeliveryStatus() == SUCCESS)
            {
                exito = true;
            }
        }
    }

    return exito;
}

/** Mandará el mensaje al coordinador configurado */
bool S2C::mandarMensaje(String _mensaje)
{
    return mandarMensaje(coordinador, _mensaje);
}
