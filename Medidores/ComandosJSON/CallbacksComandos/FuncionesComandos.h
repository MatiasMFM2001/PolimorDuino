/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FUNCIONES_COMANDOS
#define FUNCIONES_COMANDOS

#include "CLASE_Comando.h"
    #define VALIDAR_DATO_JSON(tipoDato, descripcion, valor, salida, valorRetorno) \
        if (!valor.is<tipoDato>()) { \
            CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR:"), F(descripcion), F("ingresad@ no es del tipo de datos '"), F(#tipoDato), '\''); \
            return valorRetorno; \
        } \

    #define NOMBRE_CALLBACK(nombreComando) callbackComando_ ## nombreComando
    #define DECLARAR_CALLBACK(nombreComando, args, numArgs, salida) void NOMBRE_CALLBACK(nombreComando) ([[maybe_unused]] const JsonArray &args, [[maybe_unused]] size_t numArgs, Print &salida)
    #define DEFINIR_CALLBACK(nombreComando) DECLARAR_CALLBACK(nombreComando, args, numArgs, salida)
    #define CREAR_COMANDO(capacidadNombre, nombreComando, ...) Comando<capacidadNombre>(#nombreComando, &NOMBRE_CALLBACK(nombreComando), __VA_ARGS__)
#endif
