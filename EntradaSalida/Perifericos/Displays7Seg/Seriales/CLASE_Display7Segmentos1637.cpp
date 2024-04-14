#include "CLASE_Display7Segmentos1637.h" 

Display7Segmentos1637::Display7Segmentos1637(byte numeroInicial, bool estadoInicial, size_t indiceDigito, TM1637Display *display, byte brillo)
    : Display7SegmentosAlmacenado(numeroInicial, estadoInicial)
    , indiceDigito(indiceDigito), display(display)
{
    this -> display -> setBrightness(brillo);
}

void Display7Segmentos1637::setNumeroBajoNivel(byte valor) {
    if (this -> getEstado()) {
        this -> display -> showNumberHexEx(valor % 16, 0, false, 1, this -> indiceDigito);
    }
}

void Display7Segmentos1637::encender(void) {
    this -> setNumeroBajoNivel(this -> getNumero());
}

void Display7Segmentos1637::apagar(void) {
    byte digito[] = {0};
    this -> display -> setSegments(digito, 1, this -> indiceDigito);
}

size_t Display7Segmentos1637::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "Display7Segmentos1637", indiceDigito) + SUPERCLASES_A_JSON(impresora, Display7SegmentosAlmacenado<byte>);
}
