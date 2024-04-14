#include "CLASE_PinEntradaDigital.h"
#include <log4arduino.h>

#ifdef __AVR__
    #include <PinChangeInterrupt.h>
#endif

PinEntradaDigital::PinEntradaDigital(byte numPin, bool invertir, bool habilitarPullUp)
    : Pin(numPin, (habilitarPullUp ? INPUT_PULLUP : INPUT), NUM_DIGITAL_PINS)
    , EntradaDigital(invertir)
{}

bool PinEntradaDigital::leerBajoNivel(void) {
    return (this -> pinValido) && (digitalRead(this -> numPin) == HIGH);
}

byte PinEntradaDigital::getNumPCINT(void) {
    return (this -> pinValido) ?
        #ifdef __AVR__
            digitalPinToPinChangeInterrupt(this -> numPin) : NOT_AN_INTERRUPT;
        #else
            digitalPinToInterrupt(this -> numPin) : -1;
        #endif
}

void PinEntradaDigital::vincularFuncionPCINT(void(*funcion)(void), byte modo) {
    LOG("EJECUTANDO PinEntrada::vincularFuncionPCINT(%d, %p, %d)", this -> numPin, funcion, modo);
    
    #ifdef __AVR__
        attachPinChangeInterrupt
    #else
        attachInterrupt
    #endif
        (this -> getNumPCINT(), funcion, modo);
}

void PinEntradaDigital::desvincularFuncionPCINT(void) {
    LOG("EJECUTANDO PinEntrada::desvincularFuncionPCINT(%d)", this -> numPin);
    
    #ifdef __AVR__
        detachPinChangeInterrupt
    #else
        detachInterrupt
    #endif
        (this -> getNumPCINT());
}

void PinEntradaDigital::habilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::habilitarInterrupcion(%d)", this -> numPin);
    
    #ifdef __AVR__
        enablePinChangeInterrupt(this -> getNumPCINT());
    #endif
}

void PinEntradaDigital::deshabilitarInterrupcion(void) {
    LOG("EJECUTANDO PinEntrada::deshabilitarInterrupcion(%d)", this -> numPin);
    
    #ifdef __AVR__
        disablePinChangeInterrupt(this -> getNumPCINT());
    #endif
}

size_t PinEntradaDigital::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "PinEntradaDigital", indiceTira) + SUPERCLASES_A_JSON(impresora, Pin, EntradaDigital);
}
