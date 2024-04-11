#include "FuncionesLoggers.h"
#include <log4arduino.h>

void imprimir(unsigned short &valor) {
    LOG("%d", valor);
} 
