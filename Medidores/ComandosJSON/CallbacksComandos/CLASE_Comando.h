/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COMANDO
#define COMANDO

#include "../../../Utils/CLASE_StringEstatica.h"
#include "../../../Utils/FuncionesGlobales.h"
    template<size_t CAPACIDAD_NOMBRE, size_t CAPACIDAD_MENSAJE_ERROR>
    class Comando : public Printable {
        private:
            StringEstatica<CAPACIDAD_NOMBRE> nombre;
            StringEstatica<CAPACIDAD_MENSAJE_ERROR> (*manejador)(JsonArray &, size_t, Print &);
            size_t minNumArgumentos;
            size_t maxNumArgumentos;

        public:
            Comando(StringEstatica<CAPACIDAD_NOMBRE> nombre, StringEstatica<CAPACIDAD_MENSAJE_ERROR> (*manejador)(JsonArray&, size_t, Print &), size_t minNumArgumentos, size_t maxNumArgumentos)
                : nombre(nombre), manejador(manejador), minNumArgumentos(minNumArgumentos), maxNumArgumentos(maxNumArgumentos)
            {}

            size_t getMinArgumentos(void) {
                return (this -> minNumArgumentos);
            }
            
            size_t getMaxArgumentos(void) {
                return (this -> maxNumArgumentos);
            }

            bool tieneNombre(const char *ingr) {
                return (ingr && (strncmp(this -> nombre.getContenidoConstante(), ingr, this -> nombre.getLongitud()) == 0));
            }
            
            bool recibeNumArgumentos(size_t ingr) {
                return enRango(this -> minNumArgumentos, this -> maxNumArgumentos, ingr);
            }
            
            StringEstatica<CAPACIDAD_MENSAJE_ERROR> invocar(JsonArray &args, size_t numArgs, Print &salida) {
                if (!(this -> manejador)) {
                    return StringEstatica<CAPACIDAD_MENSAJE_ERROR>();
                }
                
                return this -> manejador(args, numArgs, salida);
            }

            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Comando", nombre, minNumArgumentos, maxNumArgumentos);
            }
    };
#endif
