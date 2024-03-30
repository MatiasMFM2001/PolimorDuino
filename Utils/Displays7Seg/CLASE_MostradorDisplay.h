#ifndef MOSTRADOR_DISPLAY
#define MOSTRADOR_DISPLAY

#include "CLASE_Display7Segmentos.h"
#include "CLASE_Contador.h"
    template <size_t TNumNumeros>

    class MostradorDisplay : public Pulsable {
        private:
            Array<byte, TNumNumeros> numeros;
            Display7Segmentos* display;
            Contador<size_t> contPos;
        
        public:
            MostradorDisplay(Display7Segmentos* display)
                : numeros(Array<byte, TNumNumeros>()), display(display), contPos(Contador<size_t>(0))
            {}
            
            void setNumero(byte ingr) {
                LOG("EJECUTANDO MostradorDisplay::setNumero(%d)", ingr);
                this -> numeros.clear();
                this -> numeros.push_back(ingr);
                this -> contPos.reiniciar();
            }
            
            void setNumeros(Array<byte, TNumNumeros> ingr) {
                LOG("EJECUTANDO MostradorDisplay::setNumeros(%d)", ingr.size());
                this -> numeros = ingr;
                this -> contPos.reiniciar();
            }
            
            void encender() override {
                LOG("INICIO MostradorDisplay::encender(%d)", this -> numeros.at(this -> contPos.getValor()));
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
                FLOGS("FIN MostradorDisplay::encender()");
            }
            
            void apagar() override {
                LOG("EJECUTANDO MostradorDisplay::apagar(%d)", this -> numeros.at(this -> contPos.getValor()));
                this -> display -> apagar();
            }
            
            size_t printTo(Print& impresora) const override {
                return (imprimirCabeceraJSON(impresora, F("MostradorDisplay"))
                    + imprimirVariableJSON(impresora, F("numeros"), this -> numeros) + impresora.print(JSON_SEPARADOR)
                    + imprimirVariableJSON(impresora, F("display"), WrapperPuntero<Display7Segmentos>(this -> display)) + impresora.print(JSON_SEPARADOR)
                    + imprimirVariableJSON(impresora, F("contPos"), this -> contPos) + impresora.print(JSON_CLAUSURA_OBJETO)
                );
            }
    };
#endif