/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef WRAPPER_PUNTERO_PRINTABLE
#define WRAPPER_PUNTERO_PRINTABLE

#include <Printable.h>
#include "FuncionesJSON.h"
#include "CLASE_WrapperPuntero.h"
    /**
     * @brief Encapsula un puntero crudo, permitiendo imprimirlo.
     *
     * @tparam T El tipo de dato a apuntar.
     */
    template <typename T>
    class WrapperPunteroPrintable : public WrapperPuntero<T>, public Printable {
        public:
            /**
             * @brief Construye un WrapperPunteroPrintable, con el puntero especificado.
             *
             * @param puntero El puntero especificado.
             */
            WrapperPunteroPrintable(T *puntero = nullptr)
                : WrapperPuntero<T>(puntero)
            {}
        
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                if (this -> esNulo()) {
                    return impresora.print(JSON_NULL);
                }
                
                return imprimirDatoJSON(impresora, this -> getDato());
            }
    };
#endif
