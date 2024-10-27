/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef NOTIFICADOR_BOT_CONECTADO
#define NOTIFICADOR_BOT_CONECTADO

#include "../../Callbacks/INTERFAZ_CallbackResultado.h"
#include "../../../Logger/CLASE_WrapperPuntero.h"
#include "CLASE_ClienteTelegram.h"
#include <Stream.h>
#include "../../../Logger/FuncionesLoggers.h"
#include "../../../Logger/FuncionesJSON.h"
    template <size_t CAPACIDAD_CANALES_PERMITIDOS, size_t CAPACIDAD_MENSAJE, void (*F_LOGGER_CLIENTE)(CanalBidireccional<Stream, Print>&) = nullptr>
    class NotificadorBotConectado : public CallbackResultado<WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>>> {
        public:
            void notificar(const WrapperPuntero<ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE>> &resultado) override {
                ClienteTelegram<CAPACIDAD_CANALES_PERMITIDOS, CAPACIDAD_MENSAJE, F_LOGGER_CLIENTE> &bot = resultado.getDato();
                CLOG_REFERENCIA_IMPRESORA(Serial, F("Dispositivo conectado al bot de Telegram de username"), bot.getNombreUsuario());
            }

            /**
            * @brief Imprime el dato apuntado a la impresora especificada.
            *
            * @param impresora Referencia a la impresora especificada.
            * @returns La cantidad de bytes escritos a la impresora.
            */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "NotificadorBotConectado");
            }
    };
#endif
