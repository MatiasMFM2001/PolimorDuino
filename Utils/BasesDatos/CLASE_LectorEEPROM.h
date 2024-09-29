/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef LECTOR_EEPROM
#define LECTOR_EEPROM

#include "CLASE_AdaptadorEEPROM.h"
    template <typename T_EEPROM>
    class LectorEEPROM : public AdaptadorEEPROM<T_EEPROM> {
        private:
            size_t numBytesUsados;
        
            template <typename T>
            T leerByteAvanzando(void) {
                return this -> eeprom -> read(this -> posActual++);
            }
        
        protected:
            size_t getUltimaPosicion(void) override {
                return (this -> numBytesUsados - 1);
            }
        
        public:
            LectorEEPROM(size_t posInicial, T_EEPROM *eeprom, size_t numBytesUsados)
                : AdaptadorEEPROM<T_EEPROM>(posInicial, eeprom)
                , numBytesUsados(numBytesUsados)
            {}
            
            int read(void) {
                if (!(this -> posEnRango())) {
                    return -1;
                }
                
                return this -> leerByteAvanzando<int>();
            }
            
            size_t readBytes(char* buffer, size_t longitud) {
                if (!buffer || !(this -> posEnRango())) {
                    return 0;
                }
                
                size_t maxIteraciones = this -> getIteracionesRestantes(longitud);
                
                for (size_t cont = 0; cont < maxIteraciones; ++cont) {
                    buffer[cont] = this -> leerByteAvanzando<int>();
                }
                
                return maxIteraciones;
            }
    };
#endif
