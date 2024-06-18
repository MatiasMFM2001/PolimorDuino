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
            CLOG_REFERENCIA_IMPRESORA(salida, "ERROR:", descripcion, "ingresad@ no es del tipo de datos '", #tipoDato, '\''); \
            return valorRetorno; \
        } \

    #define NOMBRE_CALLBACK(nombreComando) callbackComando_ ## nombreComando
    #define DECLARAR_CALLBACK(capacidadError, nombreComando, args, numArgs, salida) StringEstatica<capacidadError> NOMBRE_CALLBACK(nombreComando) (JsonArray &args, size_t numArgs, Print &salida)
    #define DEFINIR_CALLBACK(capacidadError, nombreComando) DECLARAR_CALLBACK(capacidadError, nombreComando, args, numArgs, salida)
    #define CREAR_COMANDO(capacidadNombre, capacidadError, nombreComando, minArgs, maxArgs) Comando<capacidadNombre, capacidadError>(#nombreComando, &NOMBRE_CALLBACK(nombreComando), minArgs, maxArgs)
#endif
