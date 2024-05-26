/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_RESULTADO
#define CONDICION_RESULTADO

#include <Printable.h>
    template <typename... T>
    class CondicionResultado : virtual public Printable {
        public:
            virtual bool esValido(T&... resultado) = 0;
    };
#endif
