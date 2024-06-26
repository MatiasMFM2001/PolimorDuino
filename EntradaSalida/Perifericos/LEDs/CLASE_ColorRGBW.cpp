/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_ColorRGBW.h"
#include "../../../Logger/FuncionesJSON.h"

ColorRGBW::ColorRGBW(byte rojo, byte verde, byte azul, byte blanco)
    : rojo(rojo), verde(verde), azul(azul), blanco(blanco)
{}

byte ColorRGBW::getRojo(void) {
    return this -> rojo;
}

byte ColorRGBW::getVerde(void) {
    return this -> verde;
}

byte ColorRGBW::getAzul(void) {
    return this -> azul;
}

byte ColorRGBW::getBlanco(void) {
    return this -> blanco;
}

size_t ColorRGBW::printTo(Print& impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "ColorRGBW", rojo, verde, azul, blanco);
}
