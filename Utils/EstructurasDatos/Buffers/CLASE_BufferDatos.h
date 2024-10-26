/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BUFFER_DATOS
#define BUFFER_DATOS

#include "CLASE_BufferImpresora.h"
    /**
     * @brief Permite almacenar temporalmente los bytes que serán impresos por
     *  una instancia de @c Print, cuando ésta requiere tener las
     *  interrupciones activadas para funcionar, pero fueron desactivadas
     *  temporalmente.
     *
     * @tparam N_NUM_BYTES La capacidad del buffer, en bytes.
     */
    template <size_t N_NUM_BYTES>
    class BufferDatos: public BufferImpresora<N_NUM_BYTES> {
        private:
            /** @brief Instancia que imprimirá los bytes del buffer. */
            Print *salida;
        
        public:
            /**
             * @brief Construye un BufferDatos, con el array vacío y la
             *  impresora especificada.
             * 
             * @param salida La impresora especificada (que puede ser nula).
             */
            BufferDatos(Print *salida = nullptr)
                : BufferImpresora<N_NUM_BYTES>()
                , salida(salida)
            {}
            
            /**
             * @brief Si la impresora no es nula, le envía todos los datos
             *  almacenados y vacía el buffer.
             */
            void flush(void) override {
                if (this -> salida == nullptr) {
                    return;
                }
                
                this -> salida -> write(this -> getContenidoConstante(), this -> getLongitud());
                this -> vaciarContenido();
            }
    };
#endif
