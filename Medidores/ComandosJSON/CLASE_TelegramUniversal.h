/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef TELEGRAM_UNIVERSAL
#define TELEGRAM_UNIVERSAL

#include "../Instantaneos/CLASE_MedidorInstantaneo.h"
#include <Stream.h>
#include "../../Logger/CLASE_WrapperPuntero.h"
#include <LoopbackStream.h>
#include "../../Utils/FuncionesGlobales.h"
#include "../../Utils/CLASE_Contador.h"
#include <UniversalTelegramBot.h>
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, void (*F_LOGGER)(WrapperPuntero<Stream>&) = nullptr>
    class TelegramUniversal : public MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>, public CondicionResultado<WrapperPuntero<Stream>> {
        private:
            UniversalTelegramBot *bot;
            LoopbackStream stream;
            Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS> canalesPermitidos;
            Contador<size_t> posArrayMensajes;
            size_t numMensajesRecibidos;
            
        public:
            TelegramUniversal(const __FlashStringHelper *nombre, CallbackResultado<WrapperPuntero<Stream>> *callback, Scheduler *planif, UniversalTelegramBot *bot, size_t capacidadBuffer = LoopbackStream::DEFAULT_SIZE)
                : MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>(nombre, callback, planif, this)
                , bot(bot), stream(LoopbackStream(capacidadBuffer)), canalesPermitidos(Array<int64_t, CAPACIDAD_CANALES_PERMITIDOS>()), posArrayMensajes(Contador<size_t>(0)), numMensajesRecibidos(0)
            {}
            
            WrapperPuntero<Stream> getResultado(void) override {
                FLOGS("INICIO TelegramUniversal::getResultado()");
                
                if ((this -> posArrayMensajes.getValor()) >= (this -> numMensajesRecibidos)) {
                    LOG("TelegramUniversal::getResultado() - Obteniendo nuevos mensajes desde la posición %d", this -> bot -> last_message_received + 1);
                    this -> numMensajesRecibidos = this -> bot -> getUpdates(this -> bot -> last_message_received + 1);
                    this -> posArrayMensajes.reiniciar();
                }
                
                if ((this -> numMensajesRecibidos) == 0) {
                    FLOGS("TelegramUniversal::getResultado() - Saliendo porque no se recibieron mensajes nuevos");
                    return WrapperPuntero<Stream>();
                }
                
                LOG("TelegramUniversal::getResultado() - Obteniendo al mensaje de la posición %d", this -> posArrayMensajes.getValor());
                telegramMessage &mensaje = this -> bot -> messages[this -> posArrayMensajes.getValor()];
                this -> posArrayMensajes.incrementar(1);
                
                this -> bot -> sendMessage(mensaje.chat_id, mensaje.text, "");
                
                if (mensaje.type != "message") {
                    LOG("ADVERTENCIA: Se descartó el mensaje recibido, de tipo %s", mensaje.type.c_str());
                    return WrapperPuntero<Stream>();
                }
                
                char *posBufferFinal;
                int64_t idCanal = strtol(mensaje.chat_id.c_str(), &posBufferFinal, 0);
                
                if (*posBufferFinal != '\0') {
                    LOG("ERROR: La ID de mensaje '%s' no es un entero válido", mensaje.chat_id.c_str());
                    return WrapperPuntero<Stream>();
                }
                
                if (!contiene(this -> canalesPermitidos, idCanal)) {
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
                return OBJETO_A_JSON(impresora, "TelegramUniversal") + SUPERCLASES_A_JSON(impresora, (MedidorInstantaneo<WrapperPuntero<Stream>, F_LOGGER>));
            }
    };
#endif
