/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_JSON
#define CONDICION_JSON

#include <ArduinoJson.h>
#include <Printable.h>
#include "NodosPila/INTERFAZ_NodoPilaJSON.h"
    template <typename T_DATO = JsonVariantConst>
    class CondicionJSON : virtual public Printable {
        public:
            virtual bool esValido(const T_DATO &ingr, NodoPilaJSON &pilaClaves) = 0;
    };
#endif
