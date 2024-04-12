#ifndef COLOR_RGBW
#define COLOR_RGBW

#include <Arduino.h>
	/**
	 * @brief Almacena los brillos de los subpíxeles de un color RGBW.
	 */
    struct ColorRGBW {
		/** @brief Brillo del subpíxel rojo. */
        byte rojo;
        
        /** @brief Brillo del subpíxel verde. */
        byte verde;
        
        /** @brief Brillo del subpíxel azul. */
        byte azul;
        
        /** @brief Brillo del subpíxel blanco. */
        byte blanco;
        
        ColorRGBW(byte rojo = 0, byte verde = 0, byte azul = 0, byte blanco = 0)
            : rojo(rojo), verde(verde), azul(azul), blanco(blanco)
        {}
    };
#endif
