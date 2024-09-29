/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_EEPROM
#define ADAPTADOR_EEPROM

#include "../FuncionesGlobales.h"
    template <typename T_EEPROM>
    class AdaptadorEEPROM {
        private:
            size_t posInicial;
        
        protected:
            size_t posActual;
            T_EEPROM *eeprom;
        
            virtual size_t getUltimaPosicion(void) {
                return (this -> eeprom -> length() - 1);
            }
        
            bool posEnRango(void) {
                return enRango(this -> posActual, this -> posInicial, this -> getUltimaPosicion());
            }

            size_t getIteracionesRestantes(size_t longitud) {
                return min(longitud, (this -> getUltimaPosicion() + 1) - (this -> posActual));
            }
            
        public:
            AdaptadorEEPROM(size_t posInicial, T_EEPROM *eeprom)
                : posInicial(posInicial), posActual(posInicial), eeprom(eeprom)
            {}
    };
#endif
