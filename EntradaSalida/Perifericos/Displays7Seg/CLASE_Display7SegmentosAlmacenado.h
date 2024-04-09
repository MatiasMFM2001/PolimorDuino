#ifndef DISPLAY_7_SEGMENTOS_ALMACENADO
#define DISPLAY_7_SEGMENTOS_ALMACENADO

#include "CLASE_Display7Segmentos.h"
    template <typename T>
    class Display7SegmentosAlmacenado : public Display7Segmentos<T> {
        private:
            T numeroActual;

        protected:
            virtual void setNumeroBajoNivel(T valor) = 0;

        public:
            Display7SegmentosAlmacenado(T numeroInicial, bool estadoInicial)
                : Display7Segmentos<T>(numeroInicial, estadoInicial)
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
