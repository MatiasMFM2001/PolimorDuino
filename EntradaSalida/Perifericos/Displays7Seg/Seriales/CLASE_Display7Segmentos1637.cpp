#include "CLASE_Display7Segmentos1637.h" 

Display7Segmentos1637::Display7Segmentos1637(byte numeroInicial, bool estadoInicial, byte indiceDigito, TM1637Display *display)
    : Display7SegmentosAlmacenado(numeroInicial, estadoInicial)
    , indiceDigito(indiceDigito), display(display)
{}

void Display7Segmentos1637::setNumeroBajoNivel(byte valor) override {
    if (this -> getEstado()) {
        this -> display -> showNumberHexEx(valor % 16, 0, false, 1, this -> indiceDisplay);
    }
}

void Display7Segmentos1637::encender(void) {
    this -> setNumeroBajoNivel(this -> getNumero());
}

void Display7Segmentos1637::apagar(void) {
    byte digito[] = {0};
    this -> display -> setSegments(digito, 1, this -> indiceDisplay);
}
