/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FUNCIONES_JSON
#define FUNCIONES_JSON

#define JSON_APERTURA_OBJETO '{'
#define JSON_CLAUSURA_OBJETO '}'
#define JSON_APERTURA_ARRAY '['
#define JSON_CLAUSURA_ARRAY ']'
#define JSON_VARIABLE ':'
#define JSON_SEPARADOR ','
#define JSON_STRING '"'
#define JSON_NULL F("null")

#include <Arduino.h>
#include <Print.h>
#include "MACRO_ForEachAcumulando.h"
#include <Array.h>
    size_t imprimirCaracterJSON(Print &impresora, const char ingr);
    
    size_t imprimirDatoJSON(Print &impresora, const char *valor);
    size_t imprimirDatoJSON(Print &impresora, const __FlashStringHelper *valor);
    size_t imprimirDatoJSON(Print &impresora, const bool valor);
    size_t imprimirDatoJSON(Print &impresora, Printable &valor);
    
    template <typename T_VALOR>
    size_t imprimirDatoJSON(Print &impresora, T_VALOR &valor) {
        return impresora.print(valor);
    }

#include "CLASE_WrapperPunteroPrintable.h"
    template <typename T_VALOR>
    size_t imprimirDatoJSON(Print &impresora, T_VALOR *valor) {
        return imprimirDatoJSON(impresora, WrapperPunteroPrintable<T_VALOR>(valor));
    }
    
    template <typename T_VALOR, size_t S>
    size_t imprimirDatoJSON(Print &impresora, const Array<T_VALOR, S> &array) {
        size_t salida = impresora.print(JSON_APERTURA_ARRAY);
        
        if ((S > 0) && !array.empty()) {
            size_t ultPos = array.size() - 1;
            
            for (size_t cont = 0; cont < ultPos; ++cont) {
                salida += imprimirDatoJSON(impresora, array[cont]);
                salida += impresora.print(JSON_SEPARADOR);
            }
            
            imprimirDatoJSON(impresora, array[ultPos]);
        }
        
        return salida + impresora.print(JSON_CLAUSURA_ARRAY);
    }

    // Robado de https://stackoverflow.com/a/62984543
    #define DEPAREN(X) ESC(ISH X)
    #define ISH(...) ISH __VA_ARGS__
    #define ESC(...) ESC_(__VA_ARGS__)
    #define ESC_(...) VAN ## __VA_ARGS__
    #define VANISH

    #define LLAMAR_METODO(impresora, nombreSuperclase) DEPAREN(nombreSuperclase)::printTo(impresora)

    #define IMPRIMIR_NOMBRE_VARIABLE_JSON(impresora, nombreVariable) (imprimirDatoJSON(impresora, F(nombreVariable)) + impresora.print(JSON_VARIABLE))
    #define IMPRIMIR_VARIABLE_JSON(impresora, nombreVariable, valor) (IMPRIMIR_NOMBRE_VARIABLE_JSON(impresora, nombreVariable) + imprimirDatoJSON(impresora, valor))
    #define IMPRIMIR_VARIABLE_INSTANCIA_JSON(impresora, variable) IMPRIMIR_VARIABLE_JSON(impresora, #variable, variable) + impresora.print(',')
    #define IMPRIMIR_SUPERCLASE_JSON(impresora, nombreSuperclase) IMPRIMIR_VARIABLE_JSON(impresora, #nombreSuperclase, LLAMAR_METODO(impresora, nombreSuperclase))
    #define IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora) impresora.print(JSON_CLAUSURA_OBJETO)
    
    template <typename T_NOMBRE>
    size_t imprimirCabeceraJSON(Print &impresora, const T_NOMBRE *nombreClase, bool objetoVacio = false) {
        return (impresora.print(JSON_APERTURA_OBJETO)
            + IMPRIMIR_VARIABLE_JSON(impresora, "Clase", nombreClase)
            + impresora.print(objetoVacio ? JSON_CLAUSURA_OBJETO : JSON_SEPARADOR)
        );
    }
    
    #define OBJETO_A_JSON(impresora, nombreClase, ...) (imprimirCabeceraJSON(impresora, F(nombreClase)) + FOR_EACH_ACUMULANDO(IMPRIMIR_VARIABLE_INSTANCIA_JSON, impresora, __VA_ARGS__))
    #define SUPERCLASES_A_JSON(impresora, ...) (FOR_EACH_ACUMULANDO(IMPRIMIR_SUPERCLASE_JSON, impresora, __VA_ARGS__) + IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora))
    #define OBJETO_SIN_SUPER_A_JSON(impresora, nombreClase, ...) (OBJETO_A_JSON(impresora, nombreClase, __VA_ARGS__) + IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora))
#endif
