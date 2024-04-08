#include "CLASE_Display7Segmentos1637.h" 

Display7Segmentos1637::Display7Segmentos1637(byte numeroInicial, bool estadoInicial, byte indiceDigito, TM1637Display *display)
    : Display7SegmentosAlmacenado(numeroInicial, estadoInicial)
    , indiceDigito(indiceDigito), display(display)
{}

void Display7Segmentos1637::setNumeroBajoNivel(byte valor) override {
    this -> display -> showNumberHexEx(valor % 16, 0, false, 1, this -> indiceDisplay);
}
