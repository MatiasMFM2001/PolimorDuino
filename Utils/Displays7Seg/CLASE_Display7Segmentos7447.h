#ifndef DISPLAY_7_SEGMENTOS_7447
#define DISPLAY_7_SEGMENTOS_7447

#include "CLASE_Display7Segmentos.h"
    class Display7Segmentos7447 : public Display7SegmentosParalelo {
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7Segmentos7447(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable);
    };
#endif
