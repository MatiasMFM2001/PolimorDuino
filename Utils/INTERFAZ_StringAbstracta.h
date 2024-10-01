/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef STRING_ABSTRACTA
#define STRING_ABSTRACTA

#include <Printable.h>
#include "../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
    class StringAbstracta : public Printable {
        public:
            virtual size_t actualizarLongitudMidiendo(void) = 0;
            
            virtual size_t getLongitud(void) = 0;
            virtual size_t getMaxLongitud(void) = 0;
            virtual size_t getLongitudRestante(void) = 0;
            
            virtual bool estaLlena(void) = 0;
            virtual bool estaVacia(void) = 0;
            
            virtual char *getContenido(void) = 0;
            virtual const char *getContenidoConstante(void) const = 0;
            virtual void vaciarContenido(void) = 0;
            
            virtual bool agregarFinal(const char *ingr) = 0;            
            virtual bool agregarFinal(const char ingr) = 0;
            virtual bool agregarFinalPrintf(const char *formato, ...) = 0;
            
            virtual size_t agregarCaracteresMientras(Stream& stream, CondicionResultado<int> &condicion, bool terminarSiCaracterInvalido = true) = 0;
            virtual size_t agregarCaracteresHasta(Stream& stream, CondicionResultado<int> &condicion, bool terminarSiCaracterInvalido = true) = 0;
    };
#endif
