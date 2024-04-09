#ifndef DISPLAY_7_SEGMENTOS_DIRECTO
#define DISPLAY_7_SEGMENTOS_DIRECTO

#include "CLASE_Display7SegmentosParalelo.h"
#include <Array.h>
    class Display7SegmentosDirecto : public Display7SegmentosParalelo<7> { 
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7SegmentosDirecto(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, 7> salidasDatos, SalidaDigital *salidaEnable);
    };
#endif
