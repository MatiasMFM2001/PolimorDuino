#ifndef ENTRADA_SALIDA
#define ENTRADA_SALIDA
    template <typename T, byte NumBits>
    class EntradaSalida {
        private:
            /** @brief Si invertir el funcionamiento del pin o no. */
            bool invertir;
        
        protected:
            T getMaxValorRepresentable(void) {
                return (1 << NumBits) - 1;
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
    };
#endif
