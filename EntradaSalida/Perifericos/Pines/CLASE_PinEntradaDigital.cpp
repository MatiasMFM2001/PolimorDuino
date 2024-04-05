#include "CLASE_PinEntradaDigital.h"
#include "InclusionLog4Arduino.h"

PinEntradaDigital::PinEntradaDigital(byte numPin, bool invertir, bool habilitarPullUp)
    : Pin(numPin, (habilitarPullUp ? INPUT_PULLUP : INPUT), NUM_DIGITAL_PINS)
    , EntradaDigital(invertir)
{}

bool PinEntradaDigital::leerBajoNivel(void) {
    return (this -> pinValido) && (digitalRead(this -> numPin) == HIGH);
}

byte PinEntradaDigital::getNumPCINT(void) {
    return (this -> pinValido) ? digitalPinToPinChangeInterrupt(this -> numPin) : NOT_AN_INTERRUPT;
}

void PinEntradaDigital::vincularFuncionPCINT(callback funcion, byte modo) {
    LOG("EJECUTANDO PinEntrada::vincularFuncionPCINT(%d, %p, %d)", this -> numPin, funcion, modo);
    attachPinChangeInterrupt(this -> getNumPCINT(), funcion, modo);
}

void PinEntradaDigital::desvincularFuncionPCINT(void) {
    LOG("EJECUTANDO PinEntrada::desvincularFuncionPCINT(%d)", this -> numPin);
    detachPinChangeInterrupt(this -> getNumPCINT());
}

void PinEntradaDigital::habilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::habilitarInterrupcion(%d)", this -> numPin);
    enablePinChangeInterrupt(this -> getNumPCINT());
}

void PinEntradaDigital::deshabilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::deshabilitarInterrupcion(%d)", this -> numPin);
    disablePinChangeInterrupt(this -> getNumPCINT());
}
