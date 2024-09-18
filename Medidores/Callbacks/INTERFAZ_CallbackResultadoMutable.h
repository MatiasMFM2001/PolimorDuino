/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CALLBACK_RESULTADO_MUTABLE
#define CALLBACK_RESULTADO_MUTABLE

#include <Printable.h>
    template <typename... T>
    class CallbackResultadoMutable : virtual public Printable {
        public:
            virtual void notificar(T&... resultado) = 0;
    };
#endif
