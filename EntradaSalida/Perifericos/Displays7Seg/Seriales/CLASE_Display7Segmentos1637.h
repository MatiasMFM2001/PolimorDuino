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
    };
#endif
