#ifndef LED_RGBW
#define LED_RGBW
    class LedRGBW: public Pulsable {
        private:
            Array<ColorRGBW, 2> colores;

            ColorRGBW &getColor(size_t indice);
            void setColor(size_t indice, ColorRGBW ingr, bool ejecutarMostrar);
            
        public:
            LedRGBW(ColorRGBW colorApagado, ColorRGBW colorEncendido, bool estadoInicial = false);
            
            ColorRGBW getColorActual();
            ColorRGBW getColorApagado();
            ColorRGBW getColorEncendido();
            
            void setColorActual(ColorRGBW ingr, bool mostrar = true);
            void setColorApagado(ColorRGBW ingr, bool mostrarSiApagado = true);
            void setColorEncendido(ColorRGBW ingr, bool mostrarSiEncendido = true);
            
            virtual void setEstado(bool valor, bool mostrar = true) override;
            
            virtual void mostrar() = 0;
    };
#endif