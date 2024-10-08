/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "../../Medidores/ComandosJSON/CallbacksComandos/FuncionesComandos.h"
#include "../FuncionesGlobales.h"

#define CREAR_CALLBACKS_BD(nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreSettearBD, 3, 3), \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreVerBD, 0, 0), \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreGuardarBD, 0, 0)

#define DEFINIR_CALLBACKS_BD(nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    DEFINIR_CALLBACK(nombreSettearBD); \
    DEFINIR_CALLBACK(nombreVerBD); \
    DEFINIR_CALLBACK(nombreGuardarBD);

#define GUARDAR_DATO(baseDatos, punteroTipoDato, clave, tipoDato, valor, salida) \
    if (cadenasIguales(punteroTipoDato, #tipoDato)) { \
        VALIDAR_DATO_JSON(tipoDato, "El valor", valor, salida,); \
        baseDatos.setValor(clave, valor.as<tipoDato>(), &Serial); \
        CLOG_REFERENCIA_IMPRESORA(salida, "Valor de tipo", #tipoDato, "guardado correctamente"); \
    }

#define DECLARAR_CALLBACKS_BD(baseDatos, nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    DECLARAR_CALLBACK(nombreSettearBD, args, numArgs, salida) { \
        const char *clave = args[0]; \
 \
        if (clave[0] == '\0') { \
            CLOG_REFERENCIA_IMPRESORA(salida, "ERROR: La clave ingresada es vacía"); \
            return; \
        } \
 \
        const char *tipoDato = args[1]; \
        const JsonVariant &valor = args[2]; \
 \
        GUARDAR_DATO(baseDatos, tipoDato, clave, int, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, size_t, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, float, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, const char *, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, bool, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, JsonArray, valor, salida); \
        GUARDAR_DATO(baseDatos, tipoDato, clave, JsonObject, valor, salida); \
    } \
 \
    DECLARAR_CALLBACK(nombreVerBD, args, numArgs, salida) { \
        CLOG_REFERENCIA_IMPRESORA(salida, baseDatos); \
    } \
 \
    DECLARAR_CALLBACK(nombreGuardarBD, args, numArgs, salida) { \
        if (baseDatos.guardar(&salida)) { \
            CLOG_REFERENCIA_IMPRESORA(salida, "BD guardada correctamente"); \
        } \
        else { \
            CLOG_REFERENCIA_IMPRESORA(salida, "ERROR: No se pudo guardar el contenido de la BD"); \
        } \
    }
