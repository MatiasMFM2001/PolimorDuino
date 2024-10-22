/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TELEGRAM_UNIVERSAL
#define TELEGRAM_UNIVERSAL

#include "../../../Utils/CLASE_Contador.h"
#include <UniversalTelegramBot.h>
#include "CLASE_ClienteTelegram.h"
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER)(CanalBidireccional<Stream, Print>&) = nullptr>
    class TelegramUniversal : public ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER> {
        private:
            UniversalTelegramBot *bot;
            Contador<size_t> posArrayMensajes;
            size_t numMensajesRecibidos;
            
        public:
            TelegramUniversal(const __FlashStringHelper *nombre, CallbackResultado<CanalBidireccional<Stream, Print>> *callback, Scheduler *planif, UniversalTelegramBot *bot, size_t capacidadBuffer = LoopbackStream::DEFAULT_SIZE)
                : ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>(nombre, callback, planif, capacidadBuffer)
                , bot(bot), posArrayMensajes(Contador<size_t>(0)), numMensajesRecibidos(0)
            {}
            
            MensajeTelegram<CAPACIDAD_MENSAJE> recibirMensaje(void) override {
                FLOGS("INICIO TelegramUniversal::recibirMensaje()");
                
                if ((this -> posArrayMensajes.getValor()) >= (this -> numMensajesRecibidos)) {
                    LOG("TelegramUniversal::recibirMensaje() - Obteniendo nuevos mensajes desde la posición %d", this -> bot -> last_message_received + 1);
                    this -> numMensajesRecibidos = this -> bot -> getUpdates(this -> bot -> last_message_received + 1);
                    this -> posArrayMensajes.reiniciar();
                }
                
                if ((this -> numMensajesRecibidos) == 0) {
                    FLOGS("TelegramUniversal::recibirMensaje() - Saliendo porque no se recibieron mensajes nuevos");
                    return MensajeTelegram<CAPACIDAD_MENSAJE>();
                }
                
                LOG("TelegramUniversal::recibirMensaje() - Obteniendo al mensaje de la posición %d", this -> posArrayMensajes.getValor());
                telegramMessage &mensaje = this -> bot -> messages[this -> posArrayMensajes.getValor()];
                this -> posArrayMensajes.incrementar(1);
                
                char *posBufferFinal;
                int64_t idCanal = strtol(mensaje.chat_id.c_str(), &posBufferFinal, 0);
                
                if (*posBufferFinal != '\0') {
                    LOG("ERROR: La ID de mensaje '%s' no es un entero válido", mensaje.chat_id.c_str());
                    return MensajeTelegram<CAPACIDAD_MENSAJE>();
                }
                
                return MensajeTelegram<CAPACIDAD_MENSAJE>(mensaje.text.c_str(), idCanal, (mensaje.type == F("message")));
            }
            
            bool enviarMensaje(MensajeTelegram<CAPACIDAD_MENSAJE> &ingr) override {
                StringEstatica<32> idCanal;
                snprintf(idCanal.getContenido(), idCanal.getMaxLongitud(), "%lld", ingr.getIDCanal());
                
                return (this -> bot -> sendMessage(idCanal.getContenidoConstante(), ingr.getContenido().getContenidoConstante(), ""));
            }
            
            bool conectarseATelegram(void) override {
                return true;
            }
            
            StringEstatica<32> getNombreUsuario(void) override {
                return StringEstatica<32>(this -> bot -> userName.c_str());
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "TelegramUniversal") + SUPERCLASES_A_JSON(impresora, (ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER>));
            }
    };
#endif
