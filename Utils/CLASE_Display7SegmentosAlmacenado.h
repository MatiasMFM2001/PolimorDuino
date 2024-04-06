#ifndef DISPLAY_7_SEGMENTOS_ALMACENADO
#define DISPLAY_7_SEGMENTOS_ALMACENADO
    template <typename T>
    class Display7SegmentosAlmacenado : Display7Segmentos<T> {
        private:
            T numeroActual;

        protected:
            void setNumeroBajoNivel(T valor) = 0;

        public:
            Display7SegmentosAlmacenado(T numeroInicial, bool estadoInicial)
                : Display7Segmentos(numeroInicial, estadoInicial)
            {}

            void setNumero(T valor) override {
                this -> numeroActual = valor;
                this -> setNumeroBajoNivel(valor);
            }

            T getNumero(void) {
                return this -> numeroActual;
            }
    };
#endif
