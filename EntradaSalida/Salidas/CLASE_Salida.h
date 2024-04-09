#ifndef SALIDA
#define SALIDA

#include "../CLASE_EntradaSalida.h"
    template <typename T, byte NumBits>
    class Salida : public EntradaSalida<T, NumBits> {
        protected:
            virtual void escribirBajoNivel(T valor) = 0;
            
        public:
            Salida(bool invertir)
                : EntradaSalida<T, NumBits>(invertir)
            {}
            
            void escribir(T valor) {
                T maxValor = this -> getMaxValorRepresentable();
                
                if (valor > maxValor) {
                    LOG("Entrada::escribir() - Se escribio un valor %d mayor al maximo de %d", valor, maxValor);
                    this -> escribirBajoNivel(this -> invertirValor(maxValor));
                    return;
                }
                
                this -> escribirBajoNivel(this -> invertirValor(valor));
            }
    };
#endif
