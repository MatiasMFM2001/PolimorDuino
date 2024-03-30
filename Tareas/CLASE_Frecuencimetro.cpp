#include "CLASE_Frecuencimetro.h"


Frecuencimetro::Frecuencimetro(Scheduler* planif)
    : Task(TASK_SECOND, TASK_FOREVER, planif, true)
    , contFrec(Contador<unsigned short>(0)), ultFrec(0)
{}

bool Frecuencimetro::Callback() {
    this -> ultFrec = this -> contFrec.getValor();
    this -> reiniciar();
    
    return true;
}

void Frecuencimetro::incrementar() {
    this -> contFrec.incrementar(1);
}

void Frecuencimetro::reiniciar() {
    this -> contFrec.reiniciar();
}

unsigned short Frecuencimetro::getHz() {
    return (this -> contFrec.getValor());
}

bool Frecuencimetro::estaEnCero() {
    return (this -> getHz()) == 0;
}
