/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DETECTOR_STREAM
#define DETECTOR_STREAM

#include "CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "../../../Logger/CLASE_WrapperPuntero.h"
    template <void (*F_LOGGER)(WrapperPuntero<Stream>&) = nullptr>
    class DetectorStream : public MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>, public CondicionResultado<WrapperPuntero<Stream>> {
        private:
            Stream *entrada;
            
        public:
            DetectorStream(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<Stream>> *callback, Scheduler *planif, Stream *entrada)
                : MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>(nombre, callback, planif, this)
                , entrada(entrada)
            {}
            
            WrapperPuntero<Stream> getResultado(void) override {
                return WrapperPuntero(this -> entrada);
            }
            
            bool esValido(WrapperPuntero<Stream> &resultado) override {
                return (resultado.getDato().available() > 0);
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "DetectorStream") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>));
            }
    };
#endif
