/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BUFFER_DATOS
#define BUFFER_DATOS

#include <Print.h>
#include <Array.h>
    /**
     * @brief Permite almacenar temporalmente los bytes que serán impresos por
     *  una instancia de @c Print, cuando ésta requiere tener las
     *  interrupciones activadas para funcionar, pero fueron desactivadas
     *  temporalmente.
     *
     * @tparam N_NUM_BYTES La capacidad del buffer, en bytes.
     */
    template <size_t N_NUM_BYTES>
    class BufferDatos: public Print {
        private:
            /** @brief Estructura que almacena los bytes del buffer. */
            Array<byte, N_NUM_BYTES> datos;
            
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
                : Print()
                , salida(salida)
            {}
        
            /**
             * @brief Escribe un byte en el buffer, si hay capacidad suficiente.
             * 
             * @param ingr El byte a escribir.
             * @returns @c 1 si hay capacidad, @c 0 en caso contrario.
             */
            size_t write(byte ingr) override {
                if (this -> datos.full()) {
                    return 0;
                }
                
                this -> datos.push_back(ingr);
                return 1;
            }
            
            /**
             * @brief Si la impresora no es nula, le envía todos los datos
             *  almacenados y vacía el buffer.
             */
            void flush(void) override {
                if (this -> salida == nullptr) {
                    return;
                }
                
                this -> salida -> write(this -> datos.data(), this -> datos.size());
                this -> datos.clear();
            }
    };
#endif
