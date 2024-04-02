#include "CLASE_Frecuencimetro.h"


Frecuencimetro::Frecuencimetro(Scheduler* planif, const __FlashStringHelper *nombre)
    : Task(TASK_SECOND, TASK_ONCE, planif, false)
    , MedidorTemporizado(nombre)
    , contFrec(Contador<unsigned short>(0))
{}

bool Frecuencimetro::Callback() {
    this -> finalizarMedicion(this -> getHz());
    return true;
}

void Frecuencimetro::incrementar() {
    if (!(this -> isEnabled())) {
        return;
    }
    
    this -> contFrec.incrementar(1);
}

void Frecuencimetro::iniciarMedicion() {
    this -> contFrec.reiniciar();
}

unsigned short Frecuencimetro::getHz() {
    return (this -> contFrec.getValor());
}

bool Frecuencimetro::estaEnCero() {
    return (this -> getHz()) == 0;
}
