#ifndef LISTA_COLORES
#define LISTA_COLORES

#include "STRUCT_ColorRGB.h"
    struct Colores {ColorRGB   // Parece un enum, pero en realidad todos los "valores" son campos de tipo ColorRGB
        LED_APAGADO = {0, 0, 0},    // Está almacenado en RAM
        
        BOOT_SETUP = {255, 0, 0},
        CALIB_PARTE1 = {255, 127, 0},
        CALIB_PARTE2 = {255, 255, 0},
        CALIB_PARTE3 = {127, 255, 0},
        CALIB_PARTE4 = {0, 255, 0},
        //BOOT_ = {0, 255, 127},
        //BOOT_ = {0, 255, 255},
        //BOOT_ = {0, 127, 255},
        //BOOT_ = {0, 0, 255},
        //BOOT_ = {127, 0, 255},
        //BOOT_ = {255, 0, 255},
        //BOOT_ = {255, 0, 127},
        
        VENT_FALLO = {255, 0, 0},
        VENT_3PIN = {0, 255, 0},
        VENT_4PIN = {0, 255, 255};
    };
#endif
