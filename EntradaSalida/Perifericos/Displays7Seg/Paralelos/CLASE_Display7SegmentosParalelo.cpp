#include "CLASE_Display7SegmentosParalelo.h"
#include "InclusionLog4Arduino.h"
#include "FuncionesJSON.h"

Display7SegmentosParalelo::Display7SegmentosParalelo(Array<SalidaDigital*, NumsalidasDatos> salidasDatos, SalidaDigital *salidaEnable)
    : salidasDatos(salidasDatos)
    , salidaEnable(salidaEnable)
{}

void Display7SegmentosParalelo::setNumero(byte valor) {
    LOG("INICIO Display7SegmentosParalelo::setNumero(%d)", valor);
        byte bits = this -> getBits(valor);
        
        for (SalidaDigital *selec: this -> salidasDatos) {
            selec -> setEstado(bits & 0b00000001);
            bits >>= 1;
        }
    LOG("FIN Display7SegmentosParalelo::setNumero(%#x)", valor);
}

void Display7SegmentosParalelo::setEstado(bool valor) {
    this -> salidaEnable -> setEstado(valor);
}

size_t Display7SegmentosParalelo::printTo(Print& impresora) const {
    return (imprimirCabeceraJSON(impresora, F("Display7SegmentosParalelo"))
        + imprimirVariableJSON(impresora, F("salidasDatos"), this -> salidasDatos) + impresora.print(JSON_SEPARADOR)
        + imprimirVariableJSON(impresora, F("salidaEnable"), this -> salidaEnable) + impresora.print(JSON_CLAUSURA_OBJETO)
    );
}
