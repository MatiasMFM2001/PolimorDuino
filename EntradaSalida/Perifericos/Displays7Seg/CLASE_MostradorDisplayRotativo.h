#ifndef MOSTRADOR_DISPLAY_ROTATIVO
#define MOSTRADOR_DISPLAY_ROTATIVO

#include "CLASE_Display7Segmentos.h"
#include "CLASE_Contador.h"
#include "../Logger/FuncionesJSON.h"
    /**
     * @brief Permite mostrar números secuencialmente (en bucle infinito) en un
     *  display de 7 segmentos de 1 dígito.
     * 
     * @tparam TNumNumeros La cantidad máxima de números a mostrar.
     */
    template <size_t TNumNumeros, typename TDisplay>
    class MostradorDisplayRotativo : public Pulsable {
        private:
            /** @brief Los números a mostrar. */
            Array<byte, TNumNumeros> numeros;
            
            /** @brief Instancia que mostrará cada número. */
            Display7Segmentos<TDisplay> *display;
            
            /** @brief Cursor de posiciones sobre el array. */
            Contador<size_t> contPos;
        
        public:
            /**
             * @brief Construye un MostradorDisplayRotativo, con el display especificado.
             * 
             * @param display El display de 7 segmentos y 1 dígito especificado.
             */
            MostradorDisplayRotativo(Display7Segmentos<TDisplay> *display)
                : numeros(Array<byte, TNumNumeros>()), display(display), contPos(Contador<size_t>(0))
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
            void setNumeros(Array<byte, TNumNumeros> ingr) {
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
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "MostradorDisplayRotativo", numeros, display, contPos) + SUPERCLASES_A_JSON(impresora, Pulsable);
            }
    };
#endif
