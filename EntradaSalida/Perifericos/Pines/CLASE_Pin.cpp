#include "CLASE_Pin.h"
#include "../../../Utils/FuncionesGlobales.h"

Pin::Pin(byte numPin, byte modoPin, byte totalPines)
    : numPin(numPin), pinValido(enRango<byte>(numPin, 0, totalPines - 1))
{
    if (this -> pinValido) {
        pinMode(numPin, modoPin);
    }
}

size_t Pin::printTo(Print& impresora) const {
    return 0;
}
