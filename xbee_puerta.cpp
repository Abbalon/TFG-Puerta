/* Este bloque contendrá el código que gestionará del módulo XBEE */

#include "XBee.h"

S2C::S2C() {}

/** Inicializamos la antena con la referencia de la antena y su coordinador de red */
S2C::S2C(XBee *_antena, XBeeAddress64 *_coodinador) {
    xbee = *_antena;
    coodinador = *_coodinador;
}

/** Mandará el mensaje a receptor indicado */
bool S2C::mandarMensaje(XBeeAddress64 *_destino, String _mensaje)
{
    bool exito = false;
    serializar(mensaje);
    ZBTxRequest zbTx = ZBTxRequest(destino, value, sizePayload);

    //uint8_t payload[] = { 'H', 'o', 'l', 'a', ' ', 'P', 'C' };
    //ZBTxRequest zbTx = ZBTxRequest(destino, payload, sizeof(payload));

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
