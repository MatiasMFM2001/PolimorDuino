/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef STRING_ESTATICA
#define STRING_ESTATICA

#include "INTERFAZ_StringAbstracta.h"
#include "../Logger/FuncionesLoggers.h"
#include "../Medidores/Condiciones/CLASE_CompuertaNO.h"
#include "../Logger/FuncionesJSON.h"
#include <stdarg.h>
#include "CLASE_Contador.h"
    template <size_t MAX_CAPACIDAD>
    class StringEstatica : public StringAbstracta {
        private:
            char contenido[MAX_CAPACIDAD + 1];
            Contador<size_t> longitud;
        
            void escribirCaracterNulo(void) {
                this -> contenido[this -> getLongitud()] = '\0';
            }
        
        public:
            StringEstatica(const char *contenidoInicial = nullptr)
                : contenido(), longitud(Contador<size_t>(0))
            {
                this -> agregarFinal(contenidoInicial);
            }
            
            StringEstatica(char *contenidoInicial)
                : StringEstatica<MAX_CAPACIDAD>(contenidoInicial)
            {}
            
            StringEstatica(char caracterInicial)
                : StringEstatica<MAX_CAPACIDAD>()
            {
                this -> agregarFinal(caracterInicial);
            }
            
            size_t actualizarLongitudMidiendo(void) override {
                this -> longitud.reiniciar();
                
                for (char selec: this -> contenido) {
                    if (selec == '\0') {
                        return (this -> getLongitud());
                    }
                    
                    this -> longitud.incrementar(1);
                }
                
                return (this -> getLongitud());
            }
            
            size_t getLongitud(void) override {
                return (this -> longitud.getValor());
            }
            
            size_t getMaxLongitud(void) override {
                return MAX_CAPACIDAD;
            }
            
            size_t getLongitudRestante(void) override {
                return (MAX_CAPACIDAD - (this -> getLongitud()));
            }
            
            bool estaLlena(void) override {
                return (this -> getLongitud() >= MAX_CAPACIDAD);
            }
            
            bool estaVacia(void) override {
                return (this -> getLongitud() == 0);
            }
            
            char *getContenido(void) override {
                return (this -> contenido);
            }
            
            const char *getContenidoConstante(void) const override {
                return (this -> contenido);
            }

            void vaciarContenido(void) override {
                this -> longitud.reiniciar();
                this -> escribirCaracterNulo();
            }
            
            bool agregarFinal(const char *ingr) override {
                if (!ingr || (*ingr == '\0')) {
                    return true;
                }
                
                while ((*ingr != '\0') && !(this -> estaLlena())) {
                    this -> contenido[this -> getLongitud()] = *ingr;
                    
                    this -> longitud.incrementar(1);
                    ++ingr;
                }
                
                this -> escribirCaracterNulo();
                return (*ingr == '\0');
            }
            
            bool agregarFinal(const char ingr) override {
                char buffer[2] = {ingr, '\0'};
                return this -> agregarFinal(buffer);
            }
            
            bool agregarFinalPrintf(const char *formato, ...) override {
                va_list argumentos;
                
                va_start(argumentos, formato);                
                    size_t longitudRestante = (this -> getLongitudRestante() + 1);
                    int retorno = vsnprintf(this -> getContenido() + this -> getLongitud(), longitudRestante, formato, argumentos);
                va_end(argumentos);
                
                if ((retorno < 0) || (retorno >= longitudRestante)) {
                    this -> escribirCaracterNulo();
                    return false;
                }
                
                this -> longitud.incrementar(retorno);
                return true;
            }
            
            size_t agregarCaracteresMientras(Stream& stream, CondicionResultado<int> &condicion, bool terminarSiCaracterInvalido = true) override {
                size_t longitudInicial = (this -> getLongitud());
                
                int datoLeido = stream.read();
                    
                while (!(this -> estaLlena()) && (datoLeido != -1)) {
                    if (condicion.esValido(datoLeido)) {
                        this -> agregarFinal((char) datoLeido);
                    }
                    else if (terminarSiCaracterInvalido) {
                        break;
                    }
                    
                    datoLeido = stream.read();
                }
                
                return (this -> getLongitud()) - longitudInicial;
            }
            
            size_t agregarCaracteresHasta(Stream& stream, CondicionResultado<int> &condicion, bool terminarSiCaracterInvalido = true) override {
                CompuertaNO<int> negador(&condicion);
                return this -> agregarCaracteresMientras(stream, negador, terminarSiCaracterInvalido);
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
