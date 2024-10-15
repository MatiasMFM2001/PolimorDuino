/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALOR_EN_RANGO
#define VALOR_EN_RANGO

#include "../../Utils/ValidadoresJSON/CLASE_CondicionResultadoJSON.h"
#include "../../Logger/FuncionesJSON.h"
#include "../../Utils/FuncionesGlobales.h"
#include "../../Logger/FuncionesLoggers.h"
    template <typename T>
    class ValorEnRango : public CondicionResultadoJSON<T> {
        private:
            T minimoInclusivo;
            T maximoInclusivo;
        
        public:
            ValorEnRango(T minimoInclusivo, T maximoInclusivo)
                : minimoInclusivo(minimoInclusivo), maximoInclusivo(maximoInclusivo)
            {}
        
            void setMinimo(const T ingr) {
                this -> minimoInclusivo = ingr;
            }
            
            void setMaximo(const T ingr) {
                this -> maximoInclusivo = ingr;
            }
        
            bool esValido(const T &resultado) const override {
                return enRango(resultado, this -> minimoInclusivo, this -> maximoInclusivo);
            }
            
            void settearMensajeInvalido(const T &ingr, Print &salida) const override {
                CLOG_REFERENCIA_IMPRESORA(salida, "El valor", ingr, "no está en el rango [", this -> minimoInclusivo, ", ", this -> maximoInclusivo, ']');
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ValorEnRango", minimoInclusivo, maximoInclusivo);
            }
    };
#endif
