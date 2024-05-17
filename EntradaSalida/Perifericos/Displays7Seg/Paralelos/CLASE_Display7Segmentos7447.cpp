/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_Display7Segmentos7447.h"

Display7Segmentos7447::Display7Segmentos7447(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, 4> salidasDatos, SalidaDigital *salidaEnable)
    : Display7SegmentosParalelo(numeroInicial, estadoInicial, salidasDatos, salidaEnable)
{}

byte Display7Segmentos7447::getBits(byte valor) {
    return valor;
}
