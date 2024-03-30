#ifndef DISPLAY_7_SEGMENTOS
#define DISPLAY_7_SEGMENTOS

#include <Array.h>
#include "CLASE_PinSalida.h"
#include "Constantes.h"
    class Display7Segmentos : public Pulsable {
        private:
            Array<PinSalida, NUM_PINES_DISPLAY> pinesDatos;
            PinSalida pinEnable;
            //byte numero;
        
        public:
            Display7Segmentos(Array<byte, NUM_PINES_DISPLAY> pinesDatos, byte pinEnable, bool invertirDatos, bool invertirEnable);
        
            virtual byte getBits(byte valor) = 0;
            void setNumero(byte valor);
            
            void encender();
            void apagar();
        
            size_t printTo(Print& impresora) const override;
    };
#endif