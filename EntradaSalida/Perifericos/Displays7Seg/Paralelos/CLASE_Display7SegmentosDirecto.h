#ifndef DISPLAY_7_SEGMENTOS_DIRECTO
#define DISPLAY_7_SEGMENTOS_DIRECTO

#include "CLASE_Display7Segmentos.h"
#include <Array.h>
#define CANT_NUMEROS_DISPLAY 16
    class Display7SegmentosDirecto : public Display7SegmentosParalelo {
        private:
            Array<byte, CANT_NUMEROS_DISPLAY> bitsNumeros;
            
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7SegmentosDirecto(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool esAnodoComun);
    };
#endif
