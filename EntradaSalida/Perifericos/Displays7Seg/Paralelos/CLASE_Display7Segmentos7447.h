/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DISPLAY_7_SEGMENTOS_7447
#define DISPLAY_7_SEGMENTOS_7447

#include "CLASE_Display7SegmentosParalelo.h"
    class Display7Segmentos7447 : public Display7SegmentosParalelo<4> {
        protected:
            virtual byte getBits(byte valor) override;
        
        public:
            Display7Segmentos7447(byte numeroInicial, bool estadoInicial, Array<SalidaDigital*, 4> salidasDatos, SalidaDigital *salidaEnable);
    };
#endif
