#ifndef LECTOR_Entrada
#define LECTOR_Entrada


#include "CLASE_MedidorInstantaneo.h"
    template <typename TResultado, byte NumBits, void (*FLogger)(TResultado&)>
    class LectorEntrada : public MedidorInstantaneo<TResultado, FLogger> {
        private:
            Entrada<TResultado, NumBits> *entrada;
      
        public:
            LectorEntrada(const __FlashStringHelper *nombre, CallbackResultado<TResultado> *callback, Scheduler *planif, Entrada<TResultado, NumBits> *entrada)
                : MedidorInstantaneo<TResultado, FLogger>(nombre, callback, planif)
                , entrada(entrada)
            {}
            
            TResultado getResultado(void) override {
                return this -> entrada -> leer();
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "LectorEntrada", NumBits, entrada) + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<TResultado, FLogger>));
            }
    };
#endif
