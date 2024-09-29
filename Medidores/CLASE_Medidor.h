/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MEDIDOR
#define MEDIDOR

#include "../Logger/FuncionesLoggers.h"
#include "Callbacks/INTERFAZ_CallbackResultado.h"
#include "Condiciones/INTERFAZ_CondicionResultado.h"
#include "../Logger/FuncionesJSON.h"
    /**
     * @brief Define una interfaz para los objetos que puedan medir parámetros,
     *  realizando acciones con los valores medidos.
     * 
     * @tparam T_RESULTADO El tipo de dato que almacena el resultado de una
     *  medición.
     * @tparam F_LOGGER La función encargada de imprimir en logs el valor medido.
     */
    template <typename T_RESULTADO, void (*F_LOGGER)(T_RESULTADO&) = imprimir>
    class Medidor : virtual public Printable {
        private:
            CallbackResultado<T_RESULTADO> *callback;
            CondicionResultado<T_RESULTADO> *verificador;
            
        protected:
            const __FlashStringHelper *nombre;
        
            /**
             * @brief Usa el valor medido para imprimirlo en el log, y ejecutar
             *  el @c callback.
             * 
             * @param ingr El valor medido.
             */
            void finalizarMedicion(T_RESULTADO &ingr) {
                LOG("MEDIDOR \"%S\" - Ejecutando callback.notificar() con valor:", this -> nombre);
                
                #pragma GCC diagnostic ignored "-Waddress"
                if (F_LOGGER) {
                    F_LOGGER(ingr);
                }
                else {
                    LOG("MEDIDOR \"%S\" - Valor no mostrado por F_LOGGER nulo.", this -> nombre);
                }
                
                if ((this -> verificador) && !(this -> verificador -> esValido(ingr))) {
                    LOG("MEDIDOR \"%S\" - Callback no ejecutado por resultado inválido.", this -> nombre);
                    return;
                }
                
                LOG("MEDIDOR \"%S\" - Callback ejecutado por resultado válido.", this -> nombre);
                
                if (this -> callback) {
                    this -> callback -> notificar(ingr);
                }
            }
        
        public:
            Medidor(const __FlashStringHelper *nombre, CallbackResultado<T_RESULTADO> *callback, CondicionResultado<T_RESULTADO> *verificador)
                : callback(callback), verificador(verificador), nombre(nombre)
            {}
        
            void setCallback(CallbackResultado<T_RESULTADO> *ingr) {
                this -> callback = ingr;
            }
            
            void setNombre(const __FlashStringHelper *ingr) {
                this -> nombre = ingr;
            }
        
            virtual void iniciarMedicion(void) = 0;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "Medidor", callback, verificador, nombre);
            }
    };
#endif
