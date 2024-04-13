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
#include "CLASE_WrapperPuntero.h"
#include <avr/pgmspace.h>
#include "MACRO_ForEachAcumulando.h"
    size_t imprimirCaracterJSON(Print& impresora, const char ingr);
    
    size_t imprimirDatoJSON(Print& impresora, const char* valor);
    size_t imprimirDatoJSON(Print& impresora, const __FlashStringHelper* valor);
    size_t imprimirDatoJSON(Print& impresora, const bool valor);
    size_t imprimirDatoJSON(Print& impresora, const Printable& valor);
    
    template <typename TValor>
    size_t imprimirDatoJSON(Print& impresora, const TValor &valor) {
        return impresora.print(valor);
    }
    
    template <typename TValor>
    size_t imprimirDatoJSON(Print& impresora, const TValor* valor) {
        return imprimirDatoJSON(impresora, WrapperPuntero<TValor>(valor));
    }

    #define IMPRIMIR_NOMBRE_VARIABLE_JSON(impresora, nombreVariable) (imprimirDatoJSON(impresora, F(nombreVariable)) + impresora.print(JSON_VARIABLE))
    #define IMPRIMIR_VARIABLE_JSON(impresora, nombreVariable, valor) (IMPRIMIR_NOMBRE_VARIABLE_JSON(impresora, nombreVariable) + imprimirDatoJSON(impresora, valor))
    #define IMPRIMIR_VARIABLE_INSTANCIA_JSON(impresora, variable) IMPRIMIR_VARIABLE_JSON(impresora, #variable, variable)
    #define IMPRIMIR_SUPERCLASE_JSON(impresora, nombreSuperclase) IMPRIMIR_VARIABLE_JSON(impresora, #nombreSuperclase, nombreSuperclase::printTo(impresora))
    #define IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora) impresora.print(JSON_CLAUSURA_OBJETO)
    
    template <typename TNombre>
    size_t imprimirCabeceraJSON(Print& impresora, const TNombre* nombreClase, bool objetoVacio = false) {
        return (impresora.print(JSON_APERTURA_OBJETO)
            + IMPRIMIR_VARIABLE_JSON(impresora, "Clase", nombreClase)
            + impresora.print(objetoVacio ? JSON_CLAUSURA_OBJETO : JSON_SEPARADOR)
        );
    }
    
    #define OBJETO_A_JSON(impresora, nombreClase, ...) (imprimirCabeceraJSON(impresora, nombreClase) + FOR_EACH_ACUMULANDO(IMPRIMIR_VARIABLE_INSTANCIA_JSON, impresora, __VA_ARGS__))
    #define SUPERCLASES_A_JSON(impresora, ...) (FOR_EACH_ACUMULANDO(IMPRIMIR_SUPERCLASE_JSON, impresora, __VA_ARGS__) + IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora))
    #define OBJETO_SIN_SUPER_A_JSON(impresora, nombreClase, ...) (OBJETO_A_JSON(impresora, nombreClase, __VA_ARGS__) + IMPRIMIR_CLAUSURA_OBJETO_JSON(impresora))
#endif