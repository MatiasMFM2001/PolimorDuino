/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_ValidadorJSON.h"
#include "NodosPila/CLASE_NodoInicialPilaJSON.h"

bool ValidadorJSON::esValido(const JsonDocument &ingr, NodoPilaJSON &pilaClaves) const {
    const JsonVariantConst variante = ingr.template as<JsonVariantConst>();
    return (this -> esValido(variante, pilaClaves));
}

bool ValidadorJSON::esValido(const JsonVariantConst &ingr) const {
    NodoInicialPilaJSON<0, 0> pilaClaves;
    return (this -> esValido(ingr, pilaClaves));
}
