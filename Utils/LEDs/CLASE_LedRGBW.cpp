#include "CLASE_LedRGBW.h" 

#define POS_APAGADO
#define POS_ENCENDIDO

LedRGBW::LedRGBW(ColorRGBW colorApagado, ColorRGBW colorEncendido, bool estadoInicial)
{
    this -> colores.push_back(colorApagado);
    this -> colores.push_back(colorEncendido);
    
    Pulsable::Pulsable(estadoInicial);
}

ColorRGBW LedRGBW::getColorActual() {
    return this -> colores[this -> getEstado()];
}

ColorRGBW LedRGBW::getColorApagado() {
    return this -> colores[POS_APAGADO];
}

ColorRGBW LedRGBW::getColorEncendido() {
    return this -> colores[POS_ENCENDIDO];
}


void LedRGBW::setColorActual(ColorRGBW ingr, bool mostrar) {
    this -> colores[this -> getEstado()] = ingr;
    
    if (mostrar) {
        this -> mostrar();
    }
}

void LedRGBW::setColorApagado(ColorRGBW ingr, bool mostrarSiApagado) {
    this -> colores[POS_APAGADO] = ingr;
    
    if (mostrarSiApagado && !(this -> getEstado())) {
        this -> mostrar();
    }
}

void LedRGBW::setColorEncendido(ColorRGBW ingr, bool mostrarSiEncendido) {
    this -> colores[POS_ENCENDIDO] = ingr;
    
    if (mostrarSiEncendido && (this -> getEstado())) {
        this -> mostrar();
    }
}
