#include "CLASE_Display7SegmentosParalelo.h"
#include "InclusionLog4Arduino.h"
#include "FuncionesJSON.h"

Display7SegmentosParalelo::Display7SegmentosParalelo(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool invertirDatos, bool invertirEnable)
    : pinEnable(PinSalida(pinEnable, invertirEnable))
{
    for (byte selec: pinesDatos) {
        this -> pinesDatos.push_back(PinSalida(selec, invertirDatos));
    }
}

void Display7SegmentosParalelo::setNumero(byte valor) {
    LOG("INICIO Display7SegmentosParalelo::setNumero(%d)", valor);
        byte bits = this -> getBits(valor);
        
        for (PinSalida selec: this -> pinesDatos) {
            selec.setEstado(bits & 0b00000001);
            bits >>= 1;
        }
    LOG("FIN Display7SegmentosParalelo::setNumero(%#x)", valor);
}

void Display7SegmentosParalelo::encender(void) {
    this -> pinEnable.encender();
}

void Display7SegmentosParalelo::apagar(void) {
    this -> pinEnable.apagar();
}

size_t Display7SegmentosParalelo::printTo(Print& impresora) const {
    return (imprimirCabeceraJSON(impresora, F("Display7SegmentosParalelo"))
        + imprimirVariableJSON(impresora, F("pinesDatos"), this -> pinesDatos) + impresora.print(JSON_SEPARADOR)
        + imprimirVariableJSON(impresora, F("pinEnable"), this -> pinEnable) + impresora.print(JSON_CLAUSURA_OBJETO)
    );
}
