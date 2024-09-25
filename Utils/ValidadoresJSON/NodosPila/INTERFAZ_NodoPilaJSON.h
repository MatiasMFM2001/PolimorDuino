/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef NODO_PILA_JSON
#define NODO_PILA_JSON

#define CLAVE_MENSAJE_JSON "msj"
#define CLAVE_DATO_JSON "dato"
#define CLAVE_PILA_JSON "pila"

#include <Printable.h>
#include <ArduinoJson.h>
#include "../../CLASE_StringEstatica.h"
    class NodoPilaJSON : public Printable {
        public:
            virtual JsonArray copiarLista(void) = 0;
            virtual bool agregarFinalMensaje(const char *ingr) = 0;
            virtual void setDatoErroneo(JsonVariant ingr) = 0;
    };
#endif