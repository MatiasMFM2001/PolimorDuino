#ifndef DISPLAY_7_SEGMENTOS_PARALELO
#define DISPLAY_7_SEGMENTOS_PARALELO

#include <Array.h>
#include "CLASE_Display7Segmentos.h"
    template <byte NumPinesDatos>
    class Display7SegmentosParalelo : public Display7Segmentos {
        private:
            Array<SalidaDigital*, NumPinesDatos> salidasDatos;
            SalidaDigital *salidaEnable;
        
        protected:
            virtual byte getBits(byte valor) = 0;
        
        public:
            Display7SegmentosParalelo(Array<SalidaDigital*, NumPinesDatos> salidasDatos, SalidaDigital *salidaEnable);
        
            void setNumero(byte valor);
            void setEstado(bool valor) override;
        
            size_t printTo(Print& impresora) const override;
    };
#endif
