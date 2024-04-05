#include "CLASE_Display7Segmentos7447.h"

Display7Segmentos7447::Display7Segmentos7447(T numeroInicial, bool estadoInicial, Array<SalidaDigital*, NumSalidasDatos> salidasDatos, SalidaDigital *salidaEnable)
    : Display7SegmentosParalelo(numeroInicial, estadoInicial, salidasDatos, salidaEnable)
{}

byte Display7Segmentos7447::getBits(byte valor) {
    return valor;
}
