#ifndef CONTADOR_T
#define CONTADOR_T

#include "FuncionesJSON.h"
    template <typename T>
    
    class Contador : public Printable {
        private:
            T valorInicial, valorActual;
    
        public:
            Contador(T valorInicial)
                : valorInicial(valorInicial), valorActual(valorInicial)
            {}
    
            void incrementar(T cantidad) {
                (this -> valorActual) += cantidad;
            }
            
            void decrementar(T cantidad) {
                (this -> valorActual) -= cantidad;
            }
    
            T getValor() {
                return (this -> valorActual);
            }
            
            void reiniciar() {
                this -> valorActual = this -> valorInicial;
            }
            
            bool estaReiniciado() {
                return (this -> valorActual == this -> valorInicial);
            }
            
            size_t printTo(Print& impresora) const override {
                return (imprimirCabeceraJSON(impresora, F("Contador"))
                    + imprimirVariableJSON(impresora, F("valorInicial"), this -> valorInicial) + impresora.print(JSON_SEPARADOR)
                    + imprimirVariableJSON(impresora, F("valorActual"), this -> valorActual) + impresora.print(JSON_CLAUSURA_OBJETO)
                );
            }
    };
#endif
