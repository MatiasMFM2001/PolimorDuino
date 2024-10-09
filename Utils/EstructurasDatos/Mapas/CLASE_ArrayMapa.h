/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef ARRAY_MAPA
#define ARRAY_MAPA

#include "../Conjuntos/CLASE_ArrayConjunto.h"
#include "CLASE_ElementoMapa.h"
#include "CLASE_ComparadorIgualdadElementos.h"
    template <typename T_CLAVES, typename T_VALORES, size_t MAX_CAPACIDAD>
    class ArrayMapa : public Printable {
        private:
            ComparadorIgualdadElementos<T_CLAVES, T_VALORES> comparadorElementos;
            ArrayConjunto<ElementoMapa<T_CLAVES, T_VALORES>, MAX_CAPACIDAD> datos;
        
        public:
            ArrayMapa(ComparadorIgualdad<T_CLAVES> *comparadorClaves, ArrayConjunto<ElementoMapa<T_CLAVES, T_VALORES>, MAX_CAPACIDAD> datos = ArrayConjunto<ElementoMapa<T_CLAVES, T_VALORES>, MAX_CAPACIDAD>(nullptr))
                : comparadorElementos(ComparadorIgualdadElementos<T_CLAVES, T_VALORES>(comparadorClaves)), datos(ArrayConjunto<ElementoMapa<T_CLAVES, T_VALORES>, MAX_CAPACIDAD>(&(this -> comparadorElementos)))
            {
                this -> agregarTodos(datos);
            }
            
            size_t getLongitud(void) {
                return (this -> datos.getLongitud());
            }
            
            size_t getMaxLongitud(void) {
                return MAX_CAPACIDAD;
            }
            
            size_t getLongitudRestante(void) {
                return (this -> datos.getLongitudRestante());
            }
            
            bool estaLlena(void) {
                return (this -> datos.estaLlena());
            }
            
            bool estaVacia(void) {
                return (this -> datos.estaVacia());
            }

            void vaciarContenido(void) {
                this -> datos.vaciarContenido();
            }
            
            bool contiene(const ElementoMapa<T_CLAVES, T_VALORES> ingr) {
                return (this -> datos.contiene(ingr));
            }
            
            bool contieneClave(const T_CLAVES clave, const T_VALORES valorEjemplo = {}) {
                return (this -> contiene(ElementoMapa<T_CLAVES, T_VALORES>(clave, valorEjemplo)));
            }
            
            bool agregar(const ElementoMapa<T_CLAVES, T_VALORES> ingr) {
                return (this -> datos.agregar(ingr));
            }
            
            bool agregar(const T_CLAVES clave, const T_VALORES valor) {
                return (this -> agregar(ElementoMapa<T_CLAVES, T_VALORES>(clave, valor)));
            }
            
            template <size_t MAX_CAPACIDAD_INGR>
            size_t agregarTodos(const ArrayConjunto<ElementoMapa<T_CLAVES, T_VALORES>, MAX_CAPACIDAD_INGR> &ingr) {
                return (this -> datos.agregarTodos(ingr));
            }
            
            ArrayIterator<ElementoMapa<T_CLAVES, T_VALORES>> begin(void) {
                return (this -> datos.begin());
            }
            
            ArrayIterator<ElementoMapa<T_CLAVES, T_VALORES>> end(void) {
                return (this -> datos.end());
            }
            
            ArrayIterator<const ElementoMapa<T_CLAVES, T_VALORES>> begin(void) const {
                return (this -> datos.begin());
            }
            
            ArrayIterator<const ElementoMapa<T_CLAVES, T_VALORES>> end(void) const {
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
