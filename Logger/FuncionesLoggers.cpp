#include "FuncionesLoggers.h"
#include "../Inclusiones/InclusionLog4Arduino.h"

void imprimir(unsigned short &valor) {
    LOG("%d", valor);
} 
