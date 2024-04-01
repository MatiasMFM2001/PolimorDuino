#ifndef COLOR_RGB
#define COLOR_RGB

#include "TIPO_Byte.h"
	/**
	 * @brief Almacena los brillos de los subpíxeles de un color RGB.
	 */
    struct ColorRGB {
        byte rojo, verde, azul;
    };

	/**
	 * @brief Almacena los brillos de los subpíxeles de un color RGBW.
	 */
    struct ColorRGBW : ColorRGB {
        byte blanco;
    };
#endif
