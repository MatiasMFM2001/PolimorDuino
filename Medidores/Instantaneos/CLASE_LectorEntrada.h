/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LECTOR_Entrada
#define LECTOR_Entrada


#include "CLASE_MedidorInstantaneo.h"
    template <typename T_RESULTADO, byte N_NUM_BITS, void (*F_LOGGER)(T_RESULTADO&)>
    class LectorEntrada : public MedidorInstantaneo<T_RESULTADO, F_LOGGER> {
        private:
            Entrada<T_RESULTADO, N_NUM_BITS> *entrada;
      
        public:
            LectorEntrada(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, Scheduler *planif, Entrada<T_RESULTADO, N_NUM_BITS> *entrada)
                : MedidorInstantaneo<T_RESULTADO, F_LOGGER>(nombre, callback, planif)
                , entrada(entrada)
            {}
            
            T_RESULTADO getResultado(void) override {
                return this -> entrada -> leer();
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "LectorEntrada", N_NUM_BITS, entrada) + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<T_RESULTADO, F_LOGGER>));
            }
    };
#endif
