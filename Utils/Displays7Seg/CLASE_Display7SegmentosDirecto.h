#ifndef DISPLAY_7_SEGMENTOS_DIRECTO
#define DISPLAY_7_SEGMENTOS_DIRECTO

#include "CLASE_Display7Segmentos.h"
#include <Array.h>
#define CANT_NUMEROS_DISPLAY 16
    class Display7SegmentosDirecto : public Display7Segmentos {
        private:
            Array<byte, CANT_NUMEROS_DISPLAY> bitsNumeros;
        
        public:
            Display7SegmentosDirecto(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool esAnodoComun);
        
            byte getBits(byte valor) override;
    };
#endif
