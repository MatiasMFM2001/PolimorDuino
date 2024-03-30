#ifndef COLOR_RGB
#define COLOR_RGB

#include "TIPO_Byte.h"
    struct ColorRGB {
        byte rojo, verde, azul;
    };

    struct ColorRGBW : ColorRGB {
        byte blanco;
    };
#endif
