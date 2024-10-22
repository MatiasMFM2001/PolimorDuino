/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALOR_EN_CONJUNTO
#define VALOR_EN_CONJUNTO

#include "../../Utils/ValidadoresJSON/CLASE_CondicionResultadoJSON.h"
#include "../../Utils/EstructurasDatos/Conjuntos/CLASE_ArrayConjunto.h"
#include "../../Logger/FuncionesLoggers.h"
    template <typename T_DATOS, size_t MAX_CAPACIDAD_CONJUNTO>
    class ValorEnConjunto : public CondicionResultadoJSON<T_DATOS> {
        private:
            ArrayConjunto<T_DATOS, MAX_CAPACIDAD_CONJUNTO> *conjunto;
        
        public:
            ValorEnConjunto(ArrayConjunto<T_DATOS, MAX_CAPACIDAD_CONJUNTO> *conjunto)
                : conjunto(conjunto)
            {}
        
            bool esValido(const T_DATOS &resultado) const override {
                return (this -> conjunto -> contiene(resultado));
            }
            
            void settearMensajeInvalido(const T_DATOS &ingr, Print &salida) const override {
                CLOG_REFERENCIA_IMPRESORA(salida, F("El valor"), ingr, F("no está en el conjunto"), *(this -> conjunto));
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
