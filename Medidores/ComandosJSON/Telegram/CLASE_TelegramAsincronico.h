/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TELEGRAM_ASINCRONICO
#define TELEGRAM_ASINCRONICO

#include "../../../Inclusiones/InclusionAsyncTelegram2.h"
#include "CLASE_ClienteTelegram.h"
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER)(CanalBidireccional<Stream, Print>&) = nullptr>
    class TelegramAsincronico : public ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER> {
        private:
            AsyncTelegram2 *bot;
            
        public:
            TelegramAsincronico(const __FlashStringHelper *nombre, CallbackResultado<CanalBidireccional<Stream, Print>> *callback, Scheduler *planif, AsyncTelegram2 *bot, size_t capacidadBuffer = LoopbackStream::DEFAULT_SIZE)
                : ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>(nombre, callback, planif, capacidadBuffer)
                , bot(bot)
            {}
            
            MensajeTelegram<CAPACIDAD_MENSAJE> recibirMensaje(void) override {
                FLOGS("INICIO TelegramAsincronico::recibirMensaje()");
                
                TBMessage mensaje;
                MessageType tipoMensaje = this -> bot -> getNewMessage(mensaje);
                
                if (tipoMensaje == MessageType::MessageNoData) {
                    FLOGS("TelegramAsincronico::recibirMensaje() - Saliendo porque no se recibieron mensajes nuevos");
                    return MensajeTelegram<CAPACIDAD_MENSAJE>();
                }
                
                return MensajeTelegram<CAPACIDAD_MENSAJE>(mensaje.text.c_str(), mensaje.chatId, (tipoMensaje == MessageType::MessageText));
            }
            
            bool enviarMensaje(MensajeTelegram<CAPACIDAD_MENSAJE> &ingr) override {
                TBMessage mensaje;
                mensaje.chatId = ingr.getIDCanal();
                
                return (this -> bot -> sendMessage(mensaje, ingr.getContenido().getContenidoConstante()));
            }
            
            bool conectarseATelegram(void) override {
                return (this -> bot -> begin());
            }
            
            StringEstatica<32> getNombreUsuario(void) override {
                return StringEstatica<32>(this -> bot -> getBotName());
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "TelegramAsincronico") + SUPERCLASES_A_JSON(impresora, (ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>));
            }
    };
#endif
