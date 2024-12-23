/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "../../Medidores/ComandosJSON/CallbacksComandos/FuncionesComandos.h"
#include "../FuncionesGlobales.h"
#include "../MACRO_ForEach.h"

#define CREAR_CALLBACKS_BD(validadorSettearBD, nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreSettearBD, 3, 3, validadorSettearBD), \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreVerBD, 0, 0), \
    CREAR_COMANDO(CAPACIDAD_NOMBRES_INVC, nombreGuardarBD, 0, 0)

#define DEFINIR_CALLBACKS_BD(nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    DEFINIR_CALLBACK(nombreSettearBD); \
    DEFINIR_CALLBACK(nombreVerBD); \
    DEFINIR_CALLBACK(nombreGuardarBD);

#define GUARDAR_DATO(baseDatos, punteroTipoDato, clave, tipoDato, valor, salida) \
    if (cadenasIguales(punteroTipoDato, F(#tipoDato))) { \
        VALIDAR_DATO_JSON(tipoDato, "El valor", valor, salida,); \
        baseDatos.setValor(clave, valor.as<tipoDato>(), &Serial); \
        CLOG_REFERENCIA_IMPRESORA(salida, F("Valor de tipo"), F(#tipoDato), F("guardado correctamente")); \
    }

#define GUARDAR_DATO_TIPO(T) \
    GUARDAR_DATO(baseDatos, tipoDato, clave, T, valor, salida);

#define DECLARAR_CALLBACKS_BD(baseDatos, nombreSettearBD, nombreVerBD, nombreGuardarBD, ...) \
    DECLARAR_CALLBACK(nombreSettearBD, args, numArgs, salida) { \
        const char *clave = args[0]; \
 \
        if (clave[0] == '\0') { \
            CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR: La clave ingresada es vacía")); \
            return; \
        } \
 \
        const char *tipoDato = args[1]; \
        const JsonVariant &valor = args[2]; \
 \
        FOR_EACH(GUARDAR_DATO_TIPO, __VA_ARGS__); \
    } \
 \
    DECLARAR_CALLBACK(nombreVerBD, args, numArgs, salida) { \
        CLOG_REFERENCIA_IMPRESORA(salida, baseDatos); \
    } \
 \
    DECLARAR_CALLBACK(nombreGuardarBD, args, numArgs, salida) { \
        if (baseDatos.guardar(&salida)) { \
            CLOG_REFERENCIA_IMPRESORA(salida, F("BD guardada correctamente")); \
        } \
        else { \
            CLOG_REFERENCIA_IMPRESORA(salida, F("ERROR: No se pudo guardar el contenido de la BD")); \
        } \
    }

#define DECLARAR_CALLBACKS_BD_TODOS_TIPOS(baseDatos, nombreSettearBD, nombreVerBD, nombreGuardarBD) \
    DECLARAR_CALLBACKS_BD(baseDatos, nombreSettearBD, nombreVerBD, nombreGuardarBD, \
        bool, float, double, const char *, char, signed char, unsigned char, \
        int, signed int, unsigned int, short, signed short, unsigned short, \
        long, signed long, unsigned long, long long, signed long long, \
        unsigned long long, JsonVariant, JsonArray, JsonObject \
    )
