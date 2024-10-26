/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BUFFER_IMPRESORA
#define BUFFER_IMPRESORA

#include <Print.h>
#include <Array.h>
    /**
     * @brief Permite "imprimir" caracteres almacenándolos en un buffer.
     *
     * @tparam N_NUM_BYTES La capacidad del buffer.
     * @tparam T_DATOS El tipo de datos de los elementos a guardar en el buffer.
     */
    template <size_t N_NUM_BYTES, typename T_DATOS = byte>
    class BufferImpresora: public Print {
        protected:
            /** @brief Estructura que almacena los bytes del buffer. */
            Array<T_DATOS, N_NUM_BYTES> datos;
        
        public:
            /**
             * @brief Construye un BufferImpresora.
             */
            BufferImpresora(void)
                : Print()
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
            
            T_DATOS *getContenido(void) {
                return (this -> datos.data());
            }
            
            const T_DATOS *getContenidoConstante(void) const {
                return (this -> datos.data());
            }
            
            size_t getLongitud(void) {
                return (this -> datos.size());
            }
            
            size_t getLongitudBytes(void) {
                return (this -> getLongitud() * sizeof(T_DATOS));
            }
            
            void vaciarContenido(void) {
                this -> datos.clear();
            }
    };
#endif
