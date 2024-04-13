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
    size_t imprimirCaracterJSON(Print& impresora, const char ingr);
    
    size_t imprimirDatoJSON(Print& impresora, const char* valor);
    size_t imprimirDatoJSON(Print& impresora, const __FlashStringHelper* valor);
    size_t imprimirDatoJSON(Print& impresora, const bool valor);
    size_t imprimirDatoJSON(Print& impresora, const Printable& valor);
    
    template <typename TValor>
    size_t imprimirDatoJSON(Print& impresora, const TValor* valor) {
        return imprimirDatoJSON(impresora, WrapperPuntero<TValor>(valor));
    }
    
    //#define imprimirDatoJSON(impresora, valor, ...) imprimirDatoJSON(impresora, valor, ##__VA_ARGS__)
    #define imprimirNombreVariableJSON(impresora, nombreVariable) (imprimirDatoJSON(impresora, nombreVariable) + impresora.print(JSON_VARIABLE))
    //#define imprimirDatoJSON(impresora, valor, ...) impresora.print(valor, ##__VA_ARGS__)
    #define imprimirVariableJSON(impresora, nombreVariable, valor, ...) (imprimirNombreVariableJSON(impresora, nombreVariable) + imprimirDatoJSON(impresora, valor, ##__VA_ARGS__))
    
    
    template <typename TNombre>
    size_t imprimirCabeceraJSON(Print& impresora, const TNombre* nombreClase, bool objetoVacio = false) {
        return (impresora.print(JSON_APERTURA_OBJETO)
            + imprimirVariableJSON(impresora, F("Clase"), nombreClase)
            + impresora.print(objetoVacio ? JSON_CLAUSURA_OBJETO : JSON_SEPARADOR)
        );
    }
#endif
