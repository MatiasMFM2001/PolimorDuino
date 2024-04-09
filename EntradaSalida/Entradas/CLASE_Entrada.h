#ifndef ENTRADA
#define ENTRADA

#include "../CLASE_EntradaSalida.h"
    template <typename T, byte NumBits>
    class Entrada : public EntradaSalida<T, NumBits> {
        protected:
            virtual T leerBajoNivel(void) = 0;
            
        public:
            Entrada(bool invertir)
                : EntradaSalida<T, NumBits>(invertir)
            {}
            
            T leer() {
                T valor = this -> leerBajoNivel();
                T maxValor = this -> getMaxValorRepresentable();
                
                if (valor > maxValor) {
                    LOG("Entrada::leer() - Se leyo un valor %d mayor al maximo de %d", valor, maxValor);
                    return this -> invertirValor(maxValor);
                }
                
                return this -> invertirValor(valor);
            }
    };
#endif
