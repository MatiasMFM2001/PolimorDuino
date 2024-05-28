/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MEDIDOR_MOCK
#define MEDIDOR_MOCK

#include "CLASE_MedidorInstantaneo.h"
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class MedidorMock : public MedidorInstantaneo<T_RESULTADO, F_LOGGER> {
        private:
            T_RESULTADO salida;
      
        public:
            MedidorMock(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, Scheduler *planif, T_RESULTADO salida, CondicionResultado<T_RESULTADO> *verificador = nullptr)
                : MedidorInstantaneo<T_RESULTADO, F_LOGGER>(nombre, callback, planif, verificador)
                , salida(salida)
            {}
            
            T_RESULTADO getResultado(void) override {
                return this -> salida;
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "MedidorMock", salida) + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<T_RESULTADO, F_LOGGER>));
            }
    };
#endif
