#include "CLASE_Pin.h"
#include "FuncionesGlobales.h"

Pin::Pin(byte numPin, bool invertir, byte modoPin)
    : numPin(numPin), invertir(invertir), pinValido(enRango(numPin, 0, NUM_DIGITAL_PINS - 1))
{
    if (this -> pinValido) {
        pinMode(numPin, modoPin);
    }
}

size_t Pin::printTo(Print& impresora) const {
    return (imprimirCabeceraJSON(impresora, F("Pin"))
        + imprimirVariableJSON(impresora, F("numPin"), this -> numPin) + impresora.print(JSON_SEPARADOR)
        + imprimirVariableJSON(impresora, F("invertir"), this -> invertir) + impresora.print(JSON_SEPARADOR)
        + imprimirVariableJSON(impresora, F("pinValido"), this -> pinValido) + impresora.print(JSON_CLAUSURA_OBJETO)
    );
}