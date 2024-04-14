#include "CLASE_IniciadorInfinito.h"
#include "../../Logger/FuncionesJSON.h"

IniciadorInfinito::IniciadorInfinito(unsigned long msEntreIniciaciones, Scheduler* planif, Task *tarea)
    : IniciadorTareas(msEntreIniciaciones, planif, tarea)
{}

bool IniciadorInfinito::deboFinalizar(void) {
    return false;
}

size_t IniciadorInfinito::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "IniciadorInfinito");
}
