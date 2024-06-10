/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TELEGRAM_ASINCRONICO
#define TELEGRAM_ASINCRONICO

#include "../Instantaneos/CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "../../Logger/CLASE_WrapperPuntero.h"
#include <LoopbackStream.h>
#include "../../Utils/FuncionesGlobales.h"
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, void (*F_LOGGER)(WrapperPuntero<Stream>&) = nullptr>
    class TelegramAsincronico : public MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>, public CondicionResultado<WrapperPuntero<Stream>> {
        private:
            AsyncTelegram2 *bot;
            LoopbackStream stream;
            Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> canalesPermitidos;
            
        public:
            TelegramAsincronico(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<Stream>> *callback, Scheduler *planif, AsyncTelegram2 *bot, size_t capacidadBuffer = LoopbackStream::DEFAULT_SIZE)
                : MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>(nombre, callback, planif, this)
                , bot(bot), stream(LoopbackStream(capacidadBuffer)), canalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS>())
            {}
            
            WrapperPuntero<Stream> getResultado(void) override {
                TBMessage mensaje;
                MessageType tipoMensaje = this -> bot -> getNewMessage(mensaje);
                
                if (tipoMensaje != MessageType::MessageText) {
                    LOG("ADVERTENCIA: Se descartó el mensaje recibido, de tipo %d", tipoMensaje);
                    return WrapperPuntero<Stream>();
                }
                
                if (!contiene(this -> canalesPermitidos, mensaje.chatId)) {
                    return WrapperPuntero<Stream>();
                }
                
                this -> stream.clear();
                String &texto = mensaje.text;
                
                size_t tamanioTexto = texto.length();
                size_t tamanioBuffer = (this -> stream.availableForWrite());
                
                if (tamanioTexto > tamanioBuffer) {
                    LOG("ERROR: La cadena leida (de %d caracteres) no entra en el LoopbackStream de %d caracteres", tamanioTexto, tamanioBuffer);
                    return WrapperPuntero<Stream>();
                }
                
                this -> stream.print(texto);
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
                return OBJETO_A_JSON(impresora, "TelegramAsincronico") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>));
            }
    };
#endif
