#include "CLASE_Display7SegmentosDirecto.h"
#include "DECLARACION_digitosHexa.h"

Display7SegmentosDirecto::Display7SegmentosDirecto(T numeroInicial, bool estadoInicial, Array<SalidaDigital*, 7> salidasDatos, SalidaDigital *salidaEnable)
    : Display7SegmentosParalelo(numeroInicial, estadoInicial, salidasDatos, salidaEnable)
{}

byte Display7SegmentosDirecto::getBits(byte valor) {
    return getBitsDigito(valor % CANT_NUMEROS_DISPLAY);
}
