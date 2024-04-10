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
        byte blanco = 0;
    };
#endif
