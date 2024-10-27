/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef PULSABLE_COMPUESTO
#define PULSABLE_COMPUESTO   

#include <Array.h>
    template <size_t CAPACIDAD_HIJOS>
    class PulsableCompuesto : public Pulsable {
        private:
            Array<Pulsable *, CAPACIDAD_HIJOS> hijos;
        
        public:
            PulsableCompuesto(bool estadoInicial, Array<Pulsable *, CAPACIDAD_HIJOS> hijos)
                : Pulsable(estadoInicial, false)
                , hijos(hijos)
            {}
            
            void setEstado(bool ingr) override {
                this -> setEstadoActual(ingr);

                for (Pulsable *selec: this -> hijos) {
                    if (!selec) {
                        continue;
                    }
                    
                    selec -> setEstado(ingr);
                }
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "PulsableCompuesto", hijos);
            }
    };
#endif
