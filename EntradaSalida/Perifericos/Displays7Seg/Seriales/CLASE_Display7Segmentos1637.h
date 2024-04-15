#ifndef DISPLAY_7_SEGMENTOS_1637
#define DISPLAY_7_SEGMENTOS_1637

#include "../CLASE_Display7SegmentosAlmacenado.h"
#include <Arduino.h>
#include <TM1637Display.h>
    class Display7Segmentos1637 : public Display7SegmentosAlmacenado<byte> {
        private:
            size_t indiceDigito;
            TM1637Display *display;
        
        protected:
            void setNumeroBajoNivel(byte valor) override;
        
        public:
            Display7Segmentos1637(byte numeroInicial, bool estadoInicial, size_t indiceDigito, TM1637Display *display, byte brillo);
            
            void encender(void) override;
            void apagar(void) override;

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override;
    };
#endif
