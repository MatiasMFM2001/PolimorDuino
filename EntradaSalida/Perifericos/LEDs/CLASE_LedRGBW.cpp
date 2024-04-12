#include "CLASE_LedRGBW.h" 

#define POS_APAGADO 0
#define POS_ENCENDIDO 1

LedRGBW::LedRGBW(ColorRGBW colorApagado, ColorRGBW colorEncendido, bool estadoInicial)
    : Pulsable(estadoInicial, false)
{
    this -> colores.push_back(colorApagado);
    this -> colores.push_back(colorEncendido);
    this -> setEstado(estadoInicial);
}

ColorRGBW &LedRGBW::getColor(size_t indice) {
    return this -> colores[indice];
}

void LedRGBW::setColor(size_t indice, ColorRGBW ingr, bool ejecutarMostrar) {
    this -> getColor(indice) = ingr;
    
    if (ejecutarMostrar) {
        this -> mostrar();
    }
}

ColorRGBW LedRGBW::getColorActual(void) {
    return this -> getColor(this -> getEstado());
}

ColorRGBW LedRGBW::getColorApagado(void) {
    return this -> getColor(POS_APAGADO);
}

ColorRGBW LedRGBW::getColorEncendido(void) {
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

void LedRGBW::setEstado(bool valor) {
    this -> mostrar();
}

size_t LedRGBW::printTo(Print& p) const {
    return 0;
}
