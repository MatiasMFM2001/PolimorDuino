/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALOR_EN_CONJUNTO
#define VALOR_EN_CONJUNTO

#include "INTERFAZ_CondicionResultado.h"
#include "../../Utils/EstructurasDatos/Conjuntos/CLASE_ArrayConjunto.h"
    template <typename T_DATOS, size_t MAX_CAPACIDAD_CONJUNTO>
    class ValorEnConjunto : public CondicionResultado<T_DATOS> {
        private:
            ArrayConjunto<T_DATOS, MAX_CAPACIDAD_CONJUNTO> *conjunto;
        
        public:
            ValorEnConjunto(ArrayConjunto<T_DATOS, MAX_CAPACIDAD_CONJUNTO> *conjunto)
                : conjunto(conjunto)
            {}
        
            bool esValido(const T_DATOS &resultado) override {
                return (this -> conjunto -> contiene(resultado));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ValorEnConjunto", conjunto);
            }
    };
#endif
