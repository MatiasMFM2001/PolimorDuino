#include "CLASE_PinEntrada.h"
#include "InclusionLog4Arduino.h"

PinEntrada::PinEntrada(byte numPin, bool invertir, bool habilitarPullUp)
    : Pin(numPin, invertir, (habilitarPullUp ? INPUT_PULLUP : INPUT))
{}

bool PinEntrada::leer() {
    return (this -> pinValido) && ((digitalRead(this -> numPin) == HIGH) ^ (this -> invertir));
}

byte PinEntrada::getNumPCINT() {
    return (this -> pinValido) ? digitalPinToPinChangeInterrupt(this -> numPin) : NOT_AN_INTERRUPT;
}

void PinEntrada::vincularFuncionPCINT(callback funcion, byte modo) {
    LOG("EJECUTANDO PinEntrada::vincularFuncionPCINT(%d, %p, %d)", this -> numPin, funcion, modo);
    attachPinChangeInterrupt(this -> getNumPCINT(), funcion, modo);
}

void PinEntrada::desvincularFuncionPCINT() {
    LOG("EJECUTANDO PinEntrada::desvincularFuncionPCINT(%d)", this -> numPin);
    detachPinChangeInterrupt(this -> getNumPCINT());
}

void PinEntrada::habilitarInterrupcion() {
    LOG("EJECUTANDO PinEntrada::habilitarInterrupcion(%d)", this -> numPin);
    enablePinChangeInterrupt(this -> getNumPCINT());
}

void PinEntrada::deshabilitarInterrupcion() {
    LOG("EJECUTANDO PinEntrada::deshabilitarInterrupcion(%d)", this -> numPin);
    disablePinChangeInterrupt(this -> getNumPCINT());
}