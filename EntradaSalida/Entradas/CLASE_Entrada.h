#ifndef ENTRADA
#define ENTRADA

#include "CLASE_EntradaSalida.h"
    template <typename T, byte NumBits>
    class Entrada : public EntradaSalida<T, NumBits> {
        protected:
            virtual T leerBajoNivel(void) = 0;
            
        public:
            Entrada(bool invertir)
                : EntradaSalida(invertir)
            {}
            
            T leer() {
                return this -> invertirValor(this -> leerBajoNivel());
            }
    };
#endif
