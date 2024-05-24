/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MEDIDOR_INSTANTANEO
#define MEDIDOR_INSTANTANEO

#include "../CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class MedidorInstantaneo : public TareaMedidora<T_RESULTADO, F_LOGGER> {
        public:
            MedidorInstantaneo(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, Scheduler *planif, CondicionResultado<T_RESULTADO> *verificador)
                : TareaMedidora<T_RESULTADO, F_LOGGER>(nombre, callback, TASK_MILLISECOND, planif, verificador)
            {}
        
            virtual void iniciarMedicion(void) override {
            }
    };
#endif
