#ifndef COLORES_COMUNES
#define COLORES_COMUNES

#include "STRUCT_ColorRGBW.h"
	/**
	 * @brief Estructura de datos que almacena una paleta de colores.
	 * 
	 * Parece una enumeración, pero en realidad todos los "valores" son campos
	 *  de tipo ColorRGBW, y se puede usar la misma sintaxis de enumeración (por
	 *  ejemplo, @code ColoresComunes::NEGRO).
	 * 
	 * Está almacenado en RAM?
	 */
    struct ColoresComunes {ColorRGBW
        NEGRO = {0, 0, 0},
        
        ROJO = {255, 0, 0},
        NARANJA = {255, 127, 0},
        AMARILLO = {255, 255, 0},
        LIMA = {127, 255, 0},
        VERDE = {0, 255, 0},
        TURQUESA = {0, 255, 127},
        CIAN = {0, 255, 255},
        AZUR = {0, 127, 255},
        AZUL = {0, 0, 255},
        VIOLETA = {127, 0, 255},
        MAGENTA = {255, 0, 255},
        ROSA = {255, 0, 127},
        
        BLANCO_RGB = {255, 255, 255},
        BLANCO_RGBW = {0, 0, 0, 255},
    };
#endif
