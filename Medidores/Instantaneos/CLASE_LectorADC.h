#ifndef LECTOR_ADC
#define LECTOR_ADC


#include "CLASE_Ventilador.h"
    class LectorADC : public Task {
        private:
            byte pin;
            Ventilador* vent;
      
        public:
            LectorADC(byte pin, long msEntreLecturas, Ventilador* vent, Scheduler* planif);
    
            bool Callback() override;
    };
#endif
