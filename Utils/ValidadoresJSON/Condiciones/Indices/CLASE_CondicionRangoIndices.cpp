/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_CondicionRangoIndices.h"

CondicionRangoIndices::CondicionRangoIndices(ValidadorJSON *hijo, size_t indiceMin, size_t indiceMax)
    : CondicionValidador<size_t, JsonArray>(hijo)
    , indiceMin(indiceMin), indiceMax(indiceMax)
{}

CondicionRangoIndices::CondicionRangoIndices(ValidadorJSON *hijo, size_t indice)
    : CondicionRangoIndices(hijo, indice, indice)
{}

bool CondicionRangoIndices::puedeValidar(const size_t ingr) {
    return enRango(ingr, this -> indiceMin, this -> indiceMax);
}

bool CondicionRangoIndices::varianteContieneTodas(const JsonArray &ingr) {
    size_t limiteSuperior = (ingr.size() - 1);
    bool salida = enRango<size_t>(this -> indiceMin, 0, limiteSuperior);

    if ((this -> indiceMax) != EXTREMO_INFINITO) {
        salida &= enRango<size_t>(this -> indiceMax, 0, limiteSuperior);
    }

    return salida;
}

size_t CondicionRangoIndices::printTo(Print &impresora) const {
    return OBJETO_A_JSON(impresora, "CondicionRangoIndices", indiceMin, indiceMax) + SUPERCLASES_A_JSON(impresora, (CondicionValidador<size_t, JsonArray>));
}
