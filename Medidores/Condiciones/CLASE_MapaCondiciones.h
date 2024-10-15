/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MAPA_CONDICIONES
#define MAPA_CONDICIONES

#include "INTERFAZ_CondicionResultado.h"
#include "../../Logger/FuncionesLoggers.h"
#include "../../Utils/EstructurasDatos/Mapas/CLASE_ArrayMapa.h"
    template <typename T_CLAVES, typename T_VALORES, size_t MAX_CAPACIDAD_MAPA>
    class MapaCondiciones : public CondicionResultado<T_CLAVES, T_VALORES> {
        private:
            ArrayMapa<T_CLAVES, CondicionResultado<T_VALORES> *, MAX_CAPACIDAD_MAPA> mapa;
            bool valorPredeterminado;
        
        public:
            MapaCondiciones(ArrayMapa<T_CLAVES, CondicionResultado<T_VALORES> *, MAX_CAPACIDAD_MAPA> mapa, bool valorPredeterminado)
                : mapa(mapa), valorPredeterminado(valorPredeterminado)
            {}
        
            bool esValido(const T_CLAVES &clave, const T_VALORES &valor) const override {
                CondicionResultado<T_VALORES> *condicionAsociada;
                
                if (!(this -> mapa -> getValorDe(clave, condicionAsociada, nullptr))) {
                    CLOG("ADVERTENCIA: La clave", clave, "no tiene una condición asociada. Retornando", this -> valorPredeterminado);
                    return (this -> valorPredeterminado);
                }
                
                if (!condicionAsociada) {
                    CLOG("ADVERTENCIA: La clave", clave, "tiene una condición asociada nula. Retornando", this -> valorPredeterminado);
                    return (this -> valorPredeterminado);
                }
                
                return (condicionAsociada -> esValido(valor));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "MapaCondiciones", mapa);
            }
    };
#endif
