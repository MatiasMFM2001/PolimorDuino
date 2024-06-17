/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_TemperaturaHumedad.h"
#include "../../../Logger/FuncionesJSON.h"

TemperaturaHumedad::TemperaturaHumedad(float temperatura, float humedad)
    : temperatura(temperatura), humedad(humedad)
{}

bool TemperaturaHumedad::esValida(float ingr) {
    return ((ingr != NO_DEFINIDA) && !isinf(ingr) && !isnan(ingr));
}

void TemperaturaHumedad::setTemperatura(float ingr) {
    this -> temperatura = ingr;
}

float TemperaturaHumedad::getTemperatura(void) {
    return (this -> temperatura);
}

bool TemperaturaHumedad::tieneTemperatura(void) {
    return (this -> esValida(this -> temperatura));
}

void TemperaturaHumedad::setHumedad(float ingr) {
    this -> humedad = ingr;
}

float TemperaturaHumedad::getHumedad(void) {
    return (this -> humedad);
}

bool TemperaturaHumedad::tieneHumedad(void) {
    return (this -> esValida(this -> humedad));
}

size_t TemperaturaHumedad::printTo(Print &impresora) const {
    return OBJETO_SIN_SUPER_A_JSON(impresora, "TemperaturaHumedad", temperatura, humedad);
}
