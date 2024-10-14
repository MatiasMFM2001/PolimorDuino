/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_STRING_IMPRESORA
#define ADAPTADOR_STRING_IMPRESORA

#include <Print.h>
#include "INTERFAZ_StringAbstracta.h"
    /**
     * @brief Permite almacenar los bytes que serían impresos por una instancia
     *  de @c Print, en un objeto que implemente @c StringAbstracta.
     */
    class AdaptadorStringImpresora: public Print {
        private:
            /** @brief Estructura que almacena los caracteres. */
            StringAbstracta *cadena;

        public:
            /**
             * @brief Construye un AdaptadorStringImpresora, con la cadena especificada.
             *
             * @param salida La cadena especificada (que no debería ser nula).
             */
            AdaptadorStringImpresora(StringAbstracta *cadena);

            /**
             * @brief Escribe un byte en la cadena, si hay capacidad suficiente.
             *
             * @param ingr El byte a escribir.
             * @returns @c 1 si hay capacidad, @c 0 en caso contrario.
             */
            size_t write(byte ingr) override;
    };
#endif
