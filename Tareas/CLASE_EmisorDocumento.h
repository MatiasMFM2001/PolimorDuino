/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef EMISOR_DOCUMENTO
#define EMISOR_DOCUMENTO

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include <Print.h>
    template <size_t (*serializador)(const JsonDocument&, Print&)>
    class EmisorDocumento : public Task {
        private:
            Print &salida;
            JsonDocument *documento;

        public:
            EmisorDocumento(Print &salida, JsonDocument *documento = nullptr)
                : salida(salida), documento(documento)
            {}

            bool OnEnable(void) override {
                serializador(*(this -> documento), this -> salida);
                return true;
            }
    };
#endif
