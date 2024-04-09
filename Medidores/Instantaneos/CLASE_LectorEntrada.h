#ifndef LECTOR_Entrada
#define LECTOR_Entrada


#include "CLASE_MedidorInstantaneo.h"
    template <typename TResultado, byte NumBits, void (*FLogger)(TResultado&)>
    class LectorEntrada : MedidorInstantaneo<TResultado, FLogger> {
        private:
            Entrada<TResultado, NumBits> *entrada;
      
        public:
            LectorEntrada(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, Scheduler* planif, Entrada<TResultado, NumBits> *entrada)
                : MedidorInstantaneo<TResultado, FLogger>(nombre, callback, planif)
                , entrada(entrada)
            {}
            
            TResultado getResultado(void) override {
                return this -> entrada -> leer();
            }
    };
#endif
