#include "CLASE_Display7Segmentos.h"
#include "InclusionLog4Arduino.h"
#include "FuncionesJSON.h"

Display7Segmentos::Display7Segmentos(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool invertirDatos, bool invertirEnable)
    : pinEnable(PinSalida(pinEnable, invertirEnable))
{
    for (byte selec: pinesDatos) {
        this -> pinesDatos.push_back(PinSalida(selec, invertirDatos));
    }
}

void Display7Segmentos::setNumero(byte valor) {
    LOG("INICIO Display7Segmentos::setNumero(%d)", valor);
        byte bits = this -> getBits(valor);
        
        for (PinSalida selec: this -> pinesDatos) {
            selec.setEstado(bits & 0b00000001);
            bits >>= 1;
        }
    LOG("FIN Display7Segmentos::setNumero(%#x)", valor);
}

void Display7Segmentos::encender() {
    this -> pinEnable.encender();
}

void Display7Segmentos::apagar() {
    this -> pinEnable.apagar();
}

size_t Display7Segmentos::printTo(Print& impresora) const {
    return (imprimirCabeceraJSON(impresora, F("Display7Segmentos"))
        + imprimirVariableJSON(impresora, F("pinesDatos"), this -> pinesDatos) + impresora.print(JSON_SEPARADOR)
        + imprimirVariableJSON(impresora, F("pinEnable"), this -> pinEnable) + impresora.print(JSON_CLAUSURA_OBJETO)
    );
}