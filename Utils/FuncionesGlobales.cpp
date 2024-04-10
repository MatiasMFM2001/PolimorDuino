//#include "DeclaracionVariablesGlobales.h"
#include "FuncionesGlobales.h"
#include <TaskScheduler.h>

long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador) {
    if (numTerminos == TASK_FOREVER) {
        return TASK_FOREVER;
    }
    
    return (numTerminos * multiplicador);
}
