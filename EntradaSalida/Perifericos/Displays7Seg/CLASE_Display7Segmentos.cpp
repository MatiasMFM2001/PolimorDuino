#include "CLASE_Display7Segmentos.h"

Display7Segmentos::Display7Segmentos(byte numeroInicial, bool estadoInicial)
    , numeroInicial(numeroInicial)
{
    Pulsable::Pulsable(estadoInicial);
}
