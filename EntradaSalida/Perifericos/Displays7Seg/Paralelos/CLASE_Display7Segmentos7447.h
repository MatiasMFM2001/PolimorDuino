#ifndef DISPLAY_7_SEGMENTOS_7447
#define DISPLAY_7_SEGMENTOS_7447

#include "CLASE_Display7Segmentos.h"
    class Display7Segmentos7447 : public Display7SegmentosParalelo<4> {
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7Segmentos7447(T numeroInicial, bool estadoInicial, Array<SalidaDigital*, 4> salidasDatos, SalidaDigital *salidaEnable);
    };
#endif
