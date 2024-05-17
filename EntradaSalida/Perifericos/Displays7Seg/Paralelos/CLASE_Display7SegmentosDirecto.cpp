/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "CLASE_Display7SegmentosDirecto.h"
#include "../DECLARACION_digitosHexa.h"

Display7SegmentosDirecto::Display7SegmentosDirecto(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, 7> salidasDatos, SalidaDigital *salidaEnable)
    : Display7SegmentosParalelo(numeroInicial, estadoInicial, salidasDatos, salidaEnable)
{}

byte Display7SegmentosDirecto::getBits(byte valor) {
    return getBitsDigito(valor % 16);
}
