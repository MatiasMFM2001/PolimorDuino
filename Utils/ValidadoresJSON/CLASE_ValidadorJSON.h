/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_JSON
#define VALIDADOR_JSON

#include "../../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
#include <ArduinoJson.h>
    class ValidadorJSON : public CondicionResultado<JsonVariant> {
        public:
            bool esValido(JsonDocument &documento);
    };
#endif
