/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "DECLARACION_digitosHexa.h"
#include "../../../Utils/FuncionesGlobales.h"

#if __AVR__
    #include <avr/pgmspace.h>
#else
    #include <pgmspace.h>
#endif

byte getBitsDigito(byte hexa) {
    if (!enRango<byte>(hexa, 0, (sizeof(DIGITOS_HEXA) - 1))) {
        return 0;
    }
    
    byte salida;
    memcpy_P(&salida, DIGITOS_HEXA + hexa, 1);
    return salida;
}
