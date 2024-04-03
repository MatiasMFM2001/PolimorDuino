#include "CLASE_PinEntrada.h"
#include "InclusionLog4Arduino.h"

PinEntrada::PinEntrada(byte numPin, bool invertir, bool habilitarPullUp)
    : Pin(numPin, invertir, (habilitarPullUp ? INPUT_PULLUP : INPUT))
{}

bool PinEntrada::leer(void) {
    return (this -> pinValido) && ((digitalRead(this -> numPin) == HIGH) ^ (this -> invertir));
}

byte PinEntrada::getNumPCINT(void) {
    return (this -> pinValido) ? digitalPinToPinChangeInterrupt(this -> numPin) : NOT_AN_INTERRUPT;
}

void PinEntrada::vincularFuncionPCINT(callback funcion, byte modo) {
    LOG("EJECUTANDO PinEntrada::vincularFuncionPCINT(%d, %p, %d)", this -> numPin, funcion, modo);
    attachPinChangeInterrupt(this -> getNumPCINT(), funcion, modo);
}

void PinEntrada::desvincularFuncionPCINT(void) {
    LOG("EJECUTANDO PinEntrada::desvincularFuncionPCINT(%d)", this -> numPin);
    detachPinChangeInterrupt(this -> getNumPCINT());
}

void PinEntrada::habilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::habilitarInterrupcion(%d)", this -> numPin);
    enablePinChangeInterrupt(this -> getNumPCINT());
}

void PinEntrada::deshabilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::deshabilitarInterrupcion(%d)", this -> numPin);
    disablePinChangeInterrupt(this -> getNumPCINT());
}
