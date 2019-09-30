/* Este bloque contendrá el código que gestionará del módulo XBEE */

#include "xbee_puerta.h"

S2C::S2C() {}

/** Inicializamos la antena con la referencia de la antena, coordinador por defecto*/
S2C::S2C(const XBee &_antena)
{
    xbee = _antena;
    rxMsg.setStorage(storage_array);
    xbee.readPacket();
    rx.getZBRxResponse(xbee.getResponse());
    rx.setAvailable(true);
}

/** Transformará el String del mensaje a un formato que se pueda enviar
 * por la antena ZigBee
*/
void S2C::serializar(String _mensaje)
{
    sizeMsg = _mensaje.length();
    msg = new uint8_t[sizeMsg];
    for (int i = 0; i < sizeMsg; i++)
    {
        msg[i] = _mensaje[i];
    }
}

/** Mandará el mensaje a receptor indicado */
bool S2C::mandarMensaje(const XBeeAddress64 &_destino, String _mensaje)
{
    bool exito = false;
    serializar(_mensaje);
    zbTx = ZBTxRequest(_destino, msg, sizeMsg);

    xbee.send(zbTx);

    //Esperamos respuesta
    if (xbee.readPacket(MED_SEC))
    {
        //La respuesta ha de ser ZB_TX_STATUS_RESPONSE
        if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)
        {
            xbee.getResponse().getZBTxStatusResponse(txStatus);

            //Esperamos que el estado del envio sea correcto
            if (txStatus.getDeliveryStatus() == SUCCESS)
            {
                exito = true;
            }
        }
    }

    return exito;
}

/** Mandará el mensaje en broadcast */
bool S2C::mandarMensaje(String _mensaje)
{
    return mandarMensaje(BROADCAST, _mensaje);
}

int S2C::leerMensaje()
{
    int exito = -1;
    //Esperamos a obtener un mensaje
    xbee.readPacket(FIVE_SEC);
    rx.getZBRxResponse(xbee.getResponse());
    rx.setAvailable(true);

    if (xbee.getResponse().isAvailable())
    {
        // got something

        if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
        {
            // got a zb rx packet

            // now fill our zb rx class
            xbee.getResponse().getZBRxResponse(rx);

            if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)
            {
                // the sender got an ACK
                exito = GOT_ACK;
            }
            else
            {
                // we got it (obviously) but sender didn't get an ACK
                exito = NOT_GOT_ACK;
            }
            // set dataLed PWM to value of the first byte in the data
            rxMsg.push_back(rx);
        }
        else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE)
        {
            xbee.getResponse().getModemStatusResponse(msr);
            // the local XBee sends this response on certain events, like association/dissociation

            if (msr.getStatus() == ASSOCIATED)
            {
                // yay this is great.  flash led
                exito = ASSOCIATED;
            }
            else if (msr.getStatus() == DISASSOCIATED)
            {
                // this is awful.. flash led to show our discontent
                exito = DISASSOCIATED;
            }
            else
            {
                // another status
                exito = -3;
            }
        }
        else
        {
            // not something we were expectin
            exito = -4;
        }
    }
    else if (xbee.getResponse().isError())
    {
        //nss.print("Error reading packet.  Error code: ");
        //nss.println(xbee.getResponse().getErrorCode());
        exito = ERROR_RX;
    }
    else
    {
        exito = -5;
    }

    return exito;
}