/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CLAVE_EN_MAPA
#define CLAVE_EN_MAPA

#include "INTERFAZ_CondicionResultado.h"
#include "../../Logger/FuncionesJSON.h"
#include "../../Utils/EstructurasDatos/Mapas/CLASE_ArrayMapa.h"
    template <typename T_CLAVES, typename T_VALORES, size_t MAX_CAPACIDAD_MAPA>
    class ClaveEnMapa : public CondicionResultado<T_CLAVES> {
        private:
            ArrayMapa<T_CLAVES, T_VALORES, MAX_CAPACIDAD_MAPA> *mapa;
            T_VALORES valorEjemplo;
        
        public:
            ClaveEnMapa(ArrayMapa<T_CLAVES, T_VALORES, MAX_CAPACIDAD_MAPA> *mapa, T_VALORES valorEjemplo = {})
                : mapa(mapa), valorEjemplo(valorEjemplo)
            {}
        
            bool esValido(const T_CLAVES &resultado) const override {
                return (this -> mapa -> contieneClave(resultado, this -> valorEjemplo));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ClaveEnMapa", mapa, valorEjemplo);
            }
    };
#endif
