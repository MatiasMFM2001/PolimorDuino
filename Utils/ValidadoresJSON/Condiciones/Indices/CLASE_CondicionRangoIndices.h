/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_RANGO_INDICES
#define CONDICION_RANGO_INDICES

#define EXTREMO_INFINITO ((size_t) -1)

#include "../CLASE_CondicionValidador.h"
#include "../../../FuncionesGlobales.h"
    class CondicionRangoIndices : public CondicionValidador<size_t, JsonArrayConst> {
        size_t indiceMin;
        size_t indiceMax;
        
        public:
            CondicionRangoIndices(ValidadorJSON *hijo, size_t indiceMin, size_t indiceMax);
            CondicionRangoIndices(ValidadorJSON *hijo, size_t indice);
        
            bool puedeValidar(const size_t ingr);
            bool varianteContieneTodas(const JsonArrayConst &ingr, NodoPilaJSON &pilaClaves);

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override;
    };
#endif
