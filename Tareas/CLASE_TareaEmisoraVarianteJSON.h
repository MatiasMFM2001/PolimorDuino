/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TAREA_EMISORA_VARIANTE_JSON
#define TAREA_EMISORA_VARIANTE_JSON

#include "../Inclusiones/InclusionTaskSchedulerDeclarations.h"
#include <Print.h>
#include <ArduinoJson.h>
    template <typename T_VARIANTE, size_t (*serializador)(const T_VARIANTE&, Print&)>
    class TareaEmisoraVarianteJSON : public Task {
        private:
            Print &salida;
            T_VARIANTE *variante;

        public:
            TareaEmisoraVarianteJSON(Print &salida, T_VARIANTE *variante = nullptr)
                : salida(salida), variante(variante)
            {}

            bool OnEnable(void) override {
                serializador(*(this -> variante), this -> salida);
                return true;
            }
    };
#endif
