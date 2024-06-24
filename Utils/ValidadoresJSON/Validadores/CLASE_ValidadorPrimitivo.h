/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_PRIMITIVO
#define VALIDADOR_PRIMITIVO

#include "../CLASE_ValidadorJSON.h"
    template <typename T>
    class ValidadorPrimitivo : public ValidadorJSON {
        public:
            bool esValido(JsonVariant &variante) override {
                return variante.is<T>();
            }
    };
#endif
