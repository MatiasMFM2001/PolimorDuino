/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ARRAY_CONJUNTO
#define ARRAY_CONJUNTO

#include <Array.h>
#include <Printable.h>
#include "../../FuncionesGlobales.h"
#include "../../../Logger/FuncionesJSON.h"
    template <typename T_DATOS, size_t MAX_CAPACIDAD>
    class ArrayConjunto : public Printable {
        private:
            Array<T_DATOS, MAX_CAPACIDAD> datos;
            bool (*comparador)(const T &, const T &);
        
        public:
            ArrayConjunto(Array<T_DATOS, MAX_CAPACIDAD> datos = Array<T_DATOS, MAX_CAPACIDAD>(), bool (*comparador)(const T &, const T &) = &iguales)
                : datos(Array<T_DATOS, MAX_CAPACIDAD>()), comparador(comparador)
            {
                this -> agregarTodos(datos);
            }
            
            size_t getLongitud(void) {
                return (this -> datos.size());
            }
            
            size_t getMaxLongitud(void) {
                return MAX_CAPACIDAD;
            }
            
            size_t getLongitudRestante(void) {
                return (MAX_CAPACIDAD - (this -> getLongitud()));
            }
            
            bool estaLlena(void) {
                return (this -> datos.full());
            }
            
            bool estaVacia(void) {
                return (this -> datos.empty());
            }
            
            T_DATOS *getContenido(void) {
                return (this -> contenido.data());
            }
            
            const T_DATOS *getContenidoConstante(void) const {
                return (this -> contenido.data());
            }

            void vaciarContenido(void) {
                this -> datos.clear();
            }
            
            bool contiene(const T_DATOS ingr) {
                return contiene(this -> datos, ingr, this -> comparador);
            }
            
            bool agregar(const T_DATOS ingr) {
                if ((this -> estaLlena()) || (this -> contiene(ingr))) {
                    return false;
                }
                
                this -> datos.push_back(ingr);
                return true;
            }
            
            template <size_t MAX_CAPACIDAD_INGR>
            size_t agregarTodos(const Array<T_DATOS, MAX_CAPACIDAD_INGR> &ingr) {
                size_t cantidadActual = (this -> getLongitud());
                
                for (const T_DATOS selec: ingr) {
                    this -> agregar(selec);
                }
                
                return ((this -> getLongitud()) - cantidadActual);
            }
            
            ArrayIterator<T> begin(void) {
                return (this -> datos.begin());
            }
            
            ArrayIterator<T> end(void) {
                return (this -> datos.end());
            }
            
            ArrayIterator<const T> begin(void) {
                return (this -> datos.begin());
            }
            
            ArrayIterator<const T> end(void) {
                return (this -> datos.end());
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return imprimirDatoJSON(impresora, this -> datos);
            }
    };
#endif
