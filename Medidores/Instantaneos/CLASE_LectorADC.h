#ifndef LECTOR_ADC
#define LECTOR_ADC


#include "CLASE_MedidorInstantaneo.h"
    class LectorADC : MedidorInstantaneo {
        private:
            byte pin;
      
        public:
            LectorADC(byte pin);
            
            
    };
#endif
