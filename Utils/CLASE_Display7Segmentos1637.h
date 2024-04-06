#ifndef DISPLAY_7_SEGMENTOS_1637
#define DISPLAY_7_SEGMENTOS_1637
    class Display7Segmentos1637 : public Display7SegmentosAlmacenado<byte> {
        private:
            byte indiceDigito;
            TM1637Display *display;
            
        public:
            Display7Segmentos1637(byte numeroInicial, bool estadoInicial, byte indiceDigito, TM1637Display *display, byte brillo);

            void setNumeroBajoNivel(byte valor);
    };
#endif
