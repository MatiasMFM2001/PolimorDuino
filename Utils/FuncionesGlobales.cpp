//#include "DeclaracionVariablesGlobales.h"
#include "FuncionesGlobales.h"

bool enRango(short valor, short min, short max) {
    return (valor >= min) && (valor <= max);
}

short limitarRango(short valor, short min, short max) {
    LOG("EJECUTANDO FuncionesGlobales::limitarRango(%d, %d, %d)", valor, min, max);
    return constrain(valor, min, max);
}

bool iguales(short num1, short num2, short difMax) {
    short dif = (num1 - num2);
    return (abs(dif) < difMax);
}

bool esPar(short num) {
    return (num % 2) == 0;
}

long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador) {
    if (numTerminos == TASK_FOREVER) {
        return TASK_FOREVER;
    }
    
    return (numTerminos * multiplicador);
}



void notificarAlarma() {
    FLOGS("EJECUTANDO FuncionesGlobales::notificarAlarma()");
    alarma.notificar();
}

void activarAlarma() {
    FLOGS("EJECUTANDO FuncionesGlobales::activarAlarma()");
    alarma.activar();
}

void desactivarAlarma() {
    FLOGS("EJECUTANDO FuncionesGlobales::desactivarAlarma()");
    alarma.desactivar();
}
