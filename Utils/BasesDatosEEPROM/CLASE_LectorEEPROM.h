/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LECTOR_EEPROM
#define LECTOR_EEPROM

#include "CLASE_AdaptadorEEPROM.h"
    class LectorEEPROM : public AdaptadorEEPROM {
        private:
            template <typename T>
            T leerByteAvanzando(void) {
                return this -> eeprom -> read(this -> posActual++);
            }
            
        public:
            LectorEEPROM(size_t posInicial, EEPROMClass *eeprom)
                : AdaptadorEEPROM(posInicial, eeprom)
            {}
            
            int read(void) override {
                if (!(this -> posEnRango())) {
                    return -1;
                }
                
                return this -> leerByteAvanzando();
            }
            
            size_t readBytes(char* buffer, size_t longitud) override {
                if (!buffer || !(this -> posEnRango())) {
                    return 0;
                }
                
                size_t maxIteraciones = this -> getMaxIteraciones(longitud);
                
                for (size_t cont = 0; cont < maxIteraciones; ++cont) {
                    buffer[cont] = this -> leerByteAvanzando();
                }
                
                return maxIteraciones;
            }
    };
#endif
