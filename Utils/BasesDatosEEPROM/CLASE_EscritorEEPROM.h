/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ESCRITOR_EEPROM
#define ESCRITOR_EEPROM

#include "CLASE_AdaptadorEEPROM.h"
    class EscritorEEPROM : public AdaptadorEEPROM {
        private:
            template <typename T>
            void escribirByteAvanzando(T valor) {
                this -> eeprom -> write(this -> posActual++, valor);
            }
            
        public:
            EscritorEEPROM(size_t posInicial, EEPROMClass *eeprom)
                : AdaptadorEEPROM(posInicial, eeprom)
            {}
            
            size_t write(uint8_t caracter) override {
                if (!(this -> posEnRango())) {
                    return 0;
                }
                
                return this -> leerByteAvanzando();
            }
            
            size_t readBytes(char* buffer, size_t longitud) override {
                if (!buffer || !(this -> posEnRango())) {
                    return 0;
                }
                
                size_t maxIteraciones = this -> getMaxIteraciones(longitud);
                
                for (size_t cont = 0; cont < maxIteraciones; ++cont) {
                    this -> escribirByteAvanzando(buffer[cont]);
                }
                
                return maxIteraciones;
            }
    };
#endif
