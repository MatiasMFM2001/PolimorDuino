#ifndef ENTRADA_SALIDA
#define ENTRADA_SALIDA

#include <Arduino.h>
#include <Printable.h>
#include "../Logger/FuncionesJSON.h"
    template <typename T, byte N_NUM_BITS>
    class EntradaSalida : virtual public Printable {
        private:
            /** @brief Si invertir el funcionamiento del pin o no. */
            bool invertir;
        
        protected:
            T getMaxValorRepresentable(void) {
                return (1 << N_NUM_BITS) - 1;
            }
        
            T invertirValor(T ingr) {
                if (!(this -> invertir)) {
                    return ingr;
                }
                
                return (this -> getMaxValorRepresentable()) - ingr;
            }
            
        public:
            EntradaSalida(bool invertir)
                : invertir(invertir)
            {}
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "EntradaSalida", N_NUM_BITS, invertir);
            }
    };
#endif
