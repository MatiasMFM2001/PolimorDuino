/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_CondicionRangoIndices.h"
#include "../../../EstructurasDatos/Cadenas/CLASE_StringEstatica.h"

CondicionRangoIndices::CondicionRangoIndices(ValidadorJSON *hijo, size_t indiceMin, size_t indiceMax)
    : CondicionValidador<size_t, JsonArrayConst>(hijo)
    , indiceMin(indiceMin), indiceMax(indiceMax)
{}

CondicionRangoIndices::CondicionRangoIndices(ValidadorJSON *hijo, size_t indice)
    : CondicionRangoIndices(hijo, indice, indice)
{}

bool CondicionRangoIndices::puedeValidar(const size_t ingr) {
    return enRango(ingr, this -> indiceMin, this -> indiceMax);
}

bool CondicionRangoIndices::varianteContieneTodas(const JsonArrayConst &ingr, NodoPilaJSON &pilaClaves) {
    FLOGS("Ejecutando CondicionRangoIndices::varianteContieneTodas()");

    size_t limiteSuperior = (ingr.size() - 1);
    bool salida = enRango<size_t>(this -> indiceMin, 0, limiteSuperior);

    if ((this -> indiceMax) != EXTREMO_INFINITO) {
        salida &= enRango<size_t>(this -> indiceMax, 0, limiteSuperior);
    }

    if (!salida) {
        StringEstatica<16> bufferNumeros;
        bufferNumeros.agregarFinalPrintf("%lu", this -> indiceMin);
        
        pilaClaves.agregarFinalMensaje("El array no contiene las posiciones en el rango [");
        pilaClaves.agregarFinalMensaje(bufferNumeros.getContenidoConstante());
        pilaClaves.agregarFinalMensaje(", ");
        
        bufferNumeros.vaciarContenido();
        bufferNumeros.agregarFinalPrintf("%lu", this -> indiceMax);
        
        pilaClaves.agregarFinalMensaje(bufferNumeros.getContenidoConstante());
        pilaClaves.agregarFinalMensaje("]");

        pilaClaves.setDatoErroneo(ingr);
        pilaClaves.guardarNodosPila();
    }

    return salida;
}

size_t CondicionRangoIndices::printTo(Print &impresora) const {
    return OBJETO_A_JSON(impresora, "CondicionRangoIndices", indiceMin, indiceMax) + SUPERCLASES_A_JSON(impresora, (CondicionValidador<size_t, JsonArrayConst>));
}
