/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MEDIDOR_TEMPORIZADO
#define MEDIDOR_TEMPORIZADO

#include "../CLASE_TareaMedidora.h"
    /**
     * @brief 
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class MedidorTemporizado : public TareaMedidora<T_RESULTADO, F_LOGGER> {
        public:
            MedidorTemporizado(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, unsigned long msMedicion, Scheduler *planif)
                : TareaMedidora<T_RESULTADO, F_LOGGER>(nombre, callback, msMedicion, planif)
            {}
    };
#endif
