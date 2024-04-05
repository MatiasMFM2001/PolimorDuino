#ifndef LED_WS2812
#define LED_WS2812
    class LedWS2812: public LedRGBW {
        private:
            Adafruit_NeoPixel *tiraRGBW;
            unsigned short indiceTira;

        public:
            LedWS2812(ColorRGBW colorApagado, ColorRGBW colorEncendido, Adafruit_NeoPixel *tiraRGBW, unsigned short indiceTira, bool estadoInicial = false);
            
            virtual void mostrar() override;
    };
#endif
