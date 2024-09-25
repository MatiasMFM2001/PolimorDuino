/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef COMANDO
#define COMANDO

#include "../../../Utils/CLASE_StringEstatica.h"
#include "../../../Utils/FuncionesGlobales.h"
#include "../../../Utils/ValidadoresJSON/CLASE_ValidadorJSON.h"
#include "../../../Utils/ValidadoresJSON/NodosPila/INTERFAZ_NodoPilaJSON.h"
    template <size_t CAPACIDAD_NOMBRE>
    class Comando : public Printable {
        private:
            StringEstatica<CAPACIDAD_NOMBRE> nombre;
            void (*manejador)(const JsonArray &, size_t, Print &);
            size_t minNumArgumentos;
            size_t maxNumArgumentos;
            ValidadorJSON *validador;

        public:
            Comando(StringEstatica<CAPACIDAD_NOMBRE> nombre = StringEstatica<CAPACIDAD_NOMBRE>(), void (*manejador)(const JsonArray&, size_t, Print &) = nullptr, size_t minNumArgumentos = 0, size_t maxNumArgumentos = -1, ValidadorJSON *validador = nullptr)
                : nombre(nombre), manejador(manejador), minNumArgumentos(minNumArgumentos), maxNumArgumentos(maxNumArgumentos), validador(validador)
            {}

            StringEstatica<CAPACIDAD_NOMBRE> &getNombre(void) {
                return (this -> nombre);
            }

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
                return enRango(ingr, this -> minNumArgumentos, this -> maxNumArgumentos);
            }
            
            bool validarArgumentos(const JsonArray &ingr, NodoPilaJSON &pilaClaves) {
                return (!(this -> validador) || (this -> validador -> esValido(ingr, pilaClaves)));
            }
            
            void invocar(const JsonArray &args, size_t numArgs, Print &salida) {
                if (!(this -> manejador)) {
                    return;
                }
                
                this -> manejador(args, numArgs, salida);
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
