#ifndef DISPLAY_7_SEGMENTOS_DIRECTO
#define DISPLAY_7_SEGMENTOS_DIRECTO

#include "CLASE_Display7Segmentos.h"
#include <Array.h>
#define CANT_NUMEROS_DISPLAY 16
    class Display7SegmentosDirecto : public Display7SegmentosParalelo<7> {
        private:
            Array<byte, CANT_NUMEROS_DISPLAY> bitsNumeros;
            
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7SegmentosDirecto(Array<byte, 7> pinesDatos, byte pinEnable, bool esAnodoComun);
    };
#endif
