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

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "Display7SegmentosAlmacenado", numeroActual) + SUPERCLASES_A_JSON(impresora, Display7Segmentos<T>);
            }
    };
#endif
