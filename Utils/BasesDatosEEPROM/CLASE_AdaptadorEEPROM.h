/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ADAPTADOR_EEPROM
#define ADAPTADOR_EEPROM

#include "../FuncionesGlobales.h"
    class AdaptadorEEPROM {
        private:
            size_t posActual;
            EEPROMClass *eeprom;
        
        protected:
            bool posEnRango(void) {
                return enRango(this -> posActual, 0, (this -> eeprom -> longitud()) - 1);
            }
            
            size_t getMaxIteraciones(size_t longitud) {
                return min(longitud, (this -> eeprom -> longitud()) - (this -> posActual));
            }
            
        public:
            AdaptadorEEPROM(size_t posInicial, EEPROMClass *eeprom)
                : posActual(posInicial), eeprom(eeprom)
            {}
    };
#endif
