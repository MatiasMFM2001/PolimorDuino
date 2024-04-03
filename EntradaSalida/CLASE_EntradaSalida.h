#ifndef ENTRADA_SALIDA
#define ENTRADA_SALIDA
    template <typename T, byte NumBits>
    class EntradaSalida {
        private:
            /** @brief Si invertir el funcionamiento del pin o no. */
            bool invertir;
        
        protected:
            T invertirValor(T ingr) {
                if (!(this -> invertir)) {
                    return ingr;
                }
                
                T maxValor = (1 << NumBits) - 1;
                return maxValor - ingr;
            }
            
        public:
            EntradaSalida(bool invertir)
                : invertir(invertir)
            {}
    };
#endif
