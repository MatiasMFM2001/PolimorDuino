/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_ValidadorJSON.h"

bool ValidadorJSON::esValido(JsonDocument &documento) {
    JsonVariant variante = documento.as<JsonVariant>();
    return (this -> esValido(variante));
}
