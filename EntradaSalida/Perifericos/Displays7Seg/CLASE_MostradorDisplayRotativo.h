/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MOSTRADOR_DISPLAY_ROTATIVO
#define MOSTRADOR_DISPLAY_ROTATIVO

#include "CLASE_Display7Segmentos.h"
#include "CLASE_Contador.h"
#include "../Logger/FuncionesJSON.h"
    /**
     * @brief Permite mostrar números secuencialmente (en bucle infinito) en un
     *  display de 7 segmentos de 1 dígito.
     * 
     * @tparam N_NUM_NUMEROS La cantidad máxima de números a mostrar.
     */
    template <size_t N_NUM_NUMEROS, typename T_DISPLAY>
    class MostradorDisplayRotativo : public Pulsable {
        private:
            /** @brief Los números a mostrar. */
            Array<byte, N_NUM_NUMEROS> numeros;
            
            /** @brief Instancia que mostrará cada número. */
            Display7Segmentos<T_DISPLAY> *display;
            
            /** @brief Cursor de posiciones sobre el array. */
            Contador<size_t> contPos;
        
        public:
            /**
             * @brief Construye un MostradorDisplayRotativo, con el display especificado.
             * 
             * @param display El display de 7 segmentos y 1 dígito especificado.
             */
            MostradorDisplayRotativo(Display7Segmentos<T_DISPLAY> *display)
                : numeros(Array<byte, N_NUM_NUMEROS>()), display(display), contPos(Contador<size_t>(0))
            {}
            
            /**
             * @brief Establece un único número para mostrar.
             * 
             * @param ingr El número a mostrar.
             */
            void setNumero(byte ingr) {
                LOG("EJECUTANDO MostradorDisplayRotativo::setNumero(%d)", ingr);
                this -> numeros.clear();
                this -> numeros.push_back(ingr);
                this -> contPos.reiniciar();
            }
            
            /**
             * @brief Establece múltiples números para mostrar.
             * 
             * @param ingr Los números a mostrar.
             */
            void setNumeros(Array<byte, N_NUM_NUMEROS> ingr) {
                LOG("EJECUTANDO MostradorDisplayRotativo::setNumeros(%d)", ingr.size());
                this -> numeros = ingr;
                this -> contPos.reiniciar();
            }
            
            /**
             * @brief Reinicia el contador (de ser necesario), muestra el número
             *  actual e incrementa el contador.
             */
            void encender(void) override {
                LOG("INICIO MostradorDisplayRotativo::encender(%d)", this -> numeros.at(this -> contPos.getValor()));
                    if (this -> contPos.getValor() >= this -> numeros.size()) {
                        this -> contPos.reiniciar();
                    }
                    
                    this -> display -> setNumero(
                        this -> numeros.at(
                            this -> contPos.getValor()
                        )
                    );
                    
                    this -> contPos.incrementar(1);
                    this -> display -> encender();
                FLOGS("FIN MostradorDisplayRotativo::encender()");
            }
            
            /**
             * @brief Apaga el display.
             */
            void apagar(void) override {
                LOG("EJECUTANDO MostradorDisplayRotativo::apagar(%d)", this -> numeros.at(this -> contPos.getValor()));
                this -> display -> apagar();
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "MostradorDisplayRotativo", numeros, display, contPos) + SUPERCLASES_A_JSON(impresora, Pulsable);
            }
    };
#endif
