/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef DETECTOR_STREAM
#define DETECTOR_STREAM

#include "../Instantaneos/CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "STRUCT_CanalBidireccional.h"
    template <void (*F_LOGGER)(CanalBidireccional<Stream, Print>&) = nullptr>
    class DetectorStream : public MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>, public CondicionResultado<CanalBidireccional<Stream, Print>> {
        private:
            Stream *entrada;
            
        public:
            DetectorStream(const __FlashStringHelper *nombre, CallbackResultado<CanalBidireccional<Stream, Print>> *callback, Scheduler *planif, Stream *entrada)
                : MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>(nombre, callback, planif, this)
                , entrada(entrada)
            {}
            
            CanalBidireccional<Stream, Print> getResultado(void) override {
                FLOGS("Ejecutando DetectorStream::getResultado()");
                return {*(this -> entrada), *(this -> entrada)};
            }
            
            bool esValido(const CanalBidireccional<Stream, Print> &resultado) const override {
                int numBytesDisponibles = resultado.entrada.available();
                LOG("resultado.entrada.available() = %d", numBytesDisponibles);

                return (numBytesDisponibles > 0);
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "DetectorStream") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<CanalBidireccional<Stream, Print>, F_LOGGER>));
            }
    };
#endif
