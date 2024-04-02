#include "CLASE_LedRGBW.h" 

#define POS_APAGADO
#define POS_ENCENDIDO

LedRGBW::LedRGBW(ColorRGBW colorApagado, ColorRGBW colorEncendido, bool estadoInicial)
{
    this -> colores.push_back(colorApagado);
    this -> colores.push_back(colorEncendido);
    
    Pulsable::Pulsable(estadoInicial);
}

ColorRGBW &LedRGBW::getColor(byte indice) {
    return this -> colores[indice];
}

void LedRGBW::setColor(byte indice, ColorRGBW ingr, bool ejecutarMostrar) {
    this -> getColor(indice) = ingr;
    
    if (ejecutarMostrar) {
        this -> mostrar();
    }
}

ColorRGBW LedRGBW::getColorActual() {
    return this -> getColor(this -> getEstado());
}

ColorRGBW LedRGBW::getColorApagado() {
    return this -> getColor(POS_APAGADO);
}

ColorRGBW LedRGBW::getColorEncendido() {
    return this -> getColor(POS_ENCENDIDO);
}


void LedRGBW::setColorActual(ColorRGBW ingr, bool mostrar) {
    this -> setColor(this -> getEstado(), ingr, mostrar);
}

void LedRGBW::setColorApagado(ColorRGBW ingr, bool mostrarSiApagado) {
    this -> setColor(POS_APAGADO, ingr, mostrarSiApagado && !(this -> getEstado()));
}

void LedRGBW::setColorEncendido(ColorRGBW ingr, bool mostrarSiEncendido) {
    this -> setColor(POS_ENCENDIDO, ingr, mostrarSiEncendido && (this -> getEstado()));
}
