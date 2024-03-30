#include "CLASE_Display7SegmentosDirecto.h"

Display7SegmentosDirecto::Display7SegmentosDirecto(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool esAnodoComun)
    : Display7Segmentos(pinesDatos, pinEnable, esAnodoComun, esAnodoComun)
    , bitsNumeros(Array<byte, CANT_NUMEROS_DISPLAY>({
        0b0111111,  // 0
        0b0000110,  // 1
        0b1011011,  // 2
        0b1001111,  // 3
        0b1100110,  // 4
        0b1101101,  // 5
        0b1111101,  // 6
        0b0000111,  // 7
        0b1111111,  // 8
        0b1101111,  // 9
        0b1110111,  // A
        0b1111100,  // b
        0b0111001,  // C
        0b1011110,  // d
        0b1111001,  // E
        0b1110001   // F
    }))
{}

byte Display7SegmentosDirecto::getBits(byte valor) {
    return (this -> bitsNumeros.at(valor % CANT_NUMEROS_DISPLAY));
}