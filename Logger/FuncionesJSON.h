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
    
    template <typename TNombre>
    size_t imprimirCabeceraJSON(Print& impresora, const TNombre* nombreClase, bool objetoVacio = false) {
        return (impresora.print(JSON_APERTURA_OBJETO)
            + IMPRIMIR_VARIABLE_JSON(impresora, "Clase", nombreClase)
            + impresora.print(objetoVacio ? JSON_CLAUSURA_OBJETO : JSON_SEPARADOR)
        );
    }
    
    #define OBJETO_A_JSON_RECURSIVO(impresora, selec, ...) (IMPRIMIR_VARIABLE_JSON(impresora, #selec, selec) + OBJETO_A_JSON_RECURSIVO(impresora, ##__VA_ARGS__))
    #define OBJETO_A_JSON(impresora, nombreClase, ...) (imprimirCabeceraJSON(impresora, nombreClase) + OBJETO_A_JSON_RECURSIVO(impresora, ##__VA_ARGS__) + impresora.print(JSON_CLAUSURA_OBJETO))
#endif
