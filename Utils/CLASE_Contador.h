#ifndef CONTADOR_T
#define CONTADOR_T

#include <Printable.h>
    /**
     * @brief Encapsula una variable a usar como contador, permitiendo
     *  imprimirla.
     * 
     * @tparam T El tipo de dato a usar para almacenar los valores del contador.
     */
    template <typename T>
    class Contador : public Printable {
        private:
            /** @brief Valor inicial del contador. */
            T valorInicial;
            
            /** @brief Valor final del contador. */
            T valorActual;
    
        public:
            /**
             * @brief Construye un Contador, con el valor inicial especificado.
             * 
             * @param valorInicial El valor inicial especificado.
             */
            Contador(T valorInicial)
                : valorInicial(valorInicial), valorActual(valorInicial)
            {}
    
            /**
             * @brief Incrementa el valor actual del contador, según la cantidad
             *  especificada.
             * 
             * @param cantidad La cantidad especificada.
             */
            void incrementar(T cantidad) {
                (this -> valorActual) += cantidad;
            }
            
            /**
             * @brief Decrementa el valor actual del contador, según la cantidad
             *  especificada.
             * 
             * @param cantidad La cantidad especificada.
             */
            void decrementar(T cantidad) {
                (this -> valorActual) -= cantidad;
            }
    
            /**
             * @returns El valor actual.
             */
            T getValor(void) {
                return (this -> valorActual);
            }
            
            /**
             * @brief Regresa el contador a su valor inicial.
             */
            void reiniciar(void) {
                this -> valorActual = this -> valorInicial;
            }
            
            /**
             * @returns @code true si el valor actual del contador es igual al
             *  inicial, @code false en caso contrario.
             */
            bool estaReiniciado(void) {
                return (this -> valorActual == this -> valorInicial);
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             * 
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print& impresora) const override {
                return 0;
            }
    };
#endif
