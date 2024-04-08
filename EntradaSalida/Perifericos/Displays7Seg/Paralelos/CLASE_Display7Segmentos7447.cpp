#include "CLASE_Display7Segmentos7447.h"

Display7Segmentos7447::Display7Segmentos7447(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, 4> salidasDatos, SalidaDigital *salidaEnable)
    : Display7SegmentosParalelo(numeroInicial, estadoInicial, salidasDatos, salidaEnable)
{}

byte Display7Segmentos7447::getBits(byte valor) {
    return valor;
}
