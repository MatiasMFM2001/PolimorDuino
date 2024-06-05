/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef STRING_ESTATICA
#define STRING_ESTATICA

#include <Printable.h>
#include <Array.h>
    template <size_t MAX_CAPACIDAD>
    class StringEstatica : public Printable {
        private:
            Array<char, MAX_CAPACIDAD + 1> contenido;
        
        public:
            StringEstatica(const char *contenidoInicial = nullptr)
                : contenido(Array<char, MAX_CAPACIDAD + 1>({'\0'}))
            {
                this -> agregarFinal(contenidoInicial);
            }
            
            StringEstatica(char *contenidoInicial)
                : contenido(Array<char, MAX_CAPACIDAD + 1>({'\0'}))
            {
                this -> agregarFinal(contenidoInicial);
            }
            
            size_t getLongitud(void) {
                return (this -> contenido.size() - 1);
            }
            
            bool estaLlena(void) {
                return (this -> getLongitud() == MAX_CAPACIDAD);
            }
            
            bool estaVacia(void) {
                return (this -> getLongitud() == 0);
            }
            
            char *getContenido(void) {
                return this -> contenido.data();
            }
            
            const char *getContenidoConstante(void) const {
                return this -> contenido.data();
            }
            
            bool agregarFinal(const char *ingr) {
                if (!ingr || (*ingr == '\0')) {
                    return true;
                }
                
                this -> contenido.pop_back();
                
                while ((*ingr != '\0') && !(this -> estaLlena())) {
                    this -> contenido.push_back(*ingr);
                    ++ingr;
                }
                
                this -> contenido.push_back('\0');
                return (*ingr == '\0');
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return imprimirDatoJSON(impresora, this -> getContenidoConstante());
            }
    };
#endif
