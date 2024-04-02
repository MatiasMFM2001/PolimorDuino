#ifndef LECTOR_ADC
#define LECTOR_ADC


#include "CLASE_MedidorInstantaneo.h"
    template <typename TResultado, void (*FLogger)(TResultado&)>
    class LectorADC : MedidorInstantaneo<TResultado, FLogger> {
        private:
            byte pin;
      
        public:
            LectorADC(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, Scheduler* planif)
                : MedidorInstantaneo(nombre, callback, planif)
                , pin(pin)
            {}
            
            virtual TResultado getResultado() override {
                return analogRead(this -> pin);
            }
    };
#endif
