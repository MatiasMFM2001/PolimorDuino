#include "CLASE_Display7Segmentos7447.h"

Display7Segmentos7447::Display7Segmentos7447(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable)
    : Display7Segmentos(pinesDatos, pinEnable, false, false)
{}

byte Display7Segmentos7447::getBits(byte valor) {
    return valor;
}