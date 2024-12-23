/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_JSON
#define VALIDADOR_JSON

//#include "../../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
#include <ArduinoJson.h>
#include "INTERFAZ_CondicionJSON.h"
#include "../../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
    class ValidadorJSON : public CondicionJSON<>, public CondicionResultado<JsonVariantConst> {
        public:
            bool esValido(const JsonDocument &ingr, NodoPilaJSON &pilaClaves) const;
            bool esValido(const JsonVariantConst &ingr) const override;
            
            using CondicionJSON<>::esValido;
    };
#endif
