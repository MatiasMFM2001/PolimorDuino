/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CLIENTE_TELEGRAM
#define CLIENTE_TELEGRAM

#include "../../Instantaneos/CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "../../../Logger/CLASE_WrapperPuntero.h"
#include "../../../Utils/FuncionesGlobales.h"
#include "../../../Inclusiones/InclusionAsyncTelegram2.h"
#include "CLASE_MensajeTelegram.h"
#include <LoopbackStream.h>
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER)(WrapperPuntero<Stream>&) = nullptr>
    class ClienteTelegram : public MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>, public CondicionResultado<WrapperPuntero<Stream>> {
        private:
            Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> canalesPermitidos;
            LoopbackStream stream;
            
        public:
            ClienteTelegram(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<Stream>> *callback, Scheduler *planif, size_t capacidadBuffer)
                : MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>(nombre, callback, planif, this)
                , canalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS>()), stream(LoopbackStream(capacidadBuffer))
            {}
            
            virtual MensajeTelegram<CAPACIDAD_MENSAJE> recibirMensaje(void) = 0;
            virtual bool enviarMensaje(MensajeTelegram<CAPACIDAD_MENSAJE> &ingr) = 0;
            virtual bool conectarseATelegram(void) = 0;
            
            WrapperPuntero<Stream> getResultado(void) override {
                MensajeTelegram mensaje = this -> recibirMensaje();
                
                if (!mensaje.esValido()) {
                    FLOGS("ADVERTENCIA: Se descartó el mensaje recibido, porque no es válido (o está vacío)");
                    return WrapperPuntero<Stream>();
                }
                
                if (!mensaje.esMensajeTexto()) {
                    FLOGS("ADVERTENCIA: Se descartó el mensaje recibido, porque no es de texto");
                    return WrapperPuntero<Stream>();
                }
                
                int64_t idCanal = mensaje.getIDCanal();
                
                if (!contiene(this -> canalesPermitidos, idCanal)) {
                    LOG("ADVERTENCIA: Se descartó el mensaje recibido, porque el canal %d no está en el conjunto de canales permitidos", idCanal);
                    return WrapperPuntero<Stream>();
                }
                
                this -> stream.clear();
                StringEstatica<CAPACIDAD_MENSAJE> &texto = mensaje.getContenido();
                
                size_t tamanioTexto = texto.getLongitud();
                size_t tamanioBuffer = (this -> stream.availableForWrite());
                
                if (tamanioTexto > tamanioBuffer) {
                    LOG("ERROR: La cadena leida (de %d caracteres) no entra en el LoopbackStream de %d caracteres", tamanioTexto, tamanioBuffer);
                    return WrapperPuntero<Stream>();
                }
                
                this -> stream.print(texto.getContenidoConstante());
                return WrapperPuntero<Stream>(&(this -> stream));
            }
            
            bool esValido(WrapperPuntero<Stream> &resultado) override {
                return (!resultado.esNulo() && (resultado.getDato().available() > 0));
            }
            
            void setCanalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> &ingr) {
                this -> canalesPermitidos = ingr;
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "ClienteTelegram") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>));
            }
    };
#endif
