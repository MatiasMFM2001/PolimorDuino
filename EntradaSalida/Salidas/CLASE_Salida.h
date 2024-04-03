#ifndef SALIDA
#define SALIDA

#include "CLASE_EntradaSalida.h"
    template <typename T, byte NumBits>
    class Salida : EntradaSalida<T, NumBits> {
        protected:
            virtual void escribirBajoNivel(T valor) = 0;
            
        public:
            Salida(bool invertir)
                : EntradaSalida(invertir)
            {}
            
            void escribir(T valor) {
                return this -> escribirBajoNivel(this -> invertirValor(valor));
            }
    };
#endif
