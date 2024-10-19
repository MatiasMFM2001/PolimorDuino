/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ELEMENTO_MAPA
#define ELEMENTO_MAPA

#include "../../../Logger/FuncionesJSON.h"
    template <typename T_CLAVES, typename T_VALORES>
    class ElementoMapa : public Printable {
        private:
            T_CLAVES clave;
            T_VALORES valor;
        
        public:
            ElementoMapa(T_CLAVES clave = {}, T_VALORES valor = {})
                : clave(clave), valor(valor)
            {}
            
            const T_CLAVES &getClave(void) const {
                return (this -> clave);
            }
            
            const T_VALORES &getValor(void) const {
                return (this -> valor);
            }
            
            const T_CLAVES *getPunteroClave(void) const {
                return &(this -> clave);
            }
            
            const T_VALORES *getPunteroValor(void) const {
                return &(this -> valor);
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return (imprimirDatoJSON(impresora, this -> clave) + impresora.print(JSON_VARIABLE) + imprimirDatoJSON(impresora, this -> valor));
            }
    };
#endif
