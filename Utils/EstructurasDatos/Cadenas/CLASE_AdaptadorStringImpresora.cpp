/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_AdaptadorStringImpresora.h"

AdaptadorStringImpresora::AdaptadorStringImpresora(StringAbstracta *cadena)
    : Print()
    , cadena(cadena)
{}

size_t AdaptadorStringImpresora::write(byte ingr) {
    if ((ingr == 0) || (this -> cadena -> estaLlena())) {
        return 0;
    }
    
    this -> cadena -> agregarFinal(ingr);
    return 1;
}
