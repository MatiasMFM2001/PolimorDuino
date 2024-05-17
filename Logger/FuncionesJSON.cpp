#include "FuncionesJSON.h"

size_t imprimirCaracterJSON(Print& impresora, const char ingr) {
    switch (ingr) {
        case '\b': return impresora.print(F("\\b"));
        case '\f': return impresora.print(F("\\f"));
        case '\n': return impresora.print(F("\\n"));
        case '\r': return impresora.print(F("\\r"));
        case '\t': return impresora.print(F("\\t"));
        case '"': return impresora.print(F("\\\""));
        case '\\': return impresora.print(F("\\\\"));
            
        default: return impresora.print(ingr);
    }
}

size_t imprimirDatoJSON(Print& impresora, const char* valor) {
    if (valor == nullptr) {
        return impresora.print(JSON_NULL);
    }
    
    size_t salida = impresora.print(JSON_STRING);
    char selec = *valor;
    
    while (selec != '\0') {
        salida += imprimirCaracterJSON(impresora, selec);
        selec = *(++valor);
    }
    
    return (salida + impresora.print(JSON_STRING));
}

size_t imprimirDatoJSON(Print& impresora, const __FlashStringHelper* valor) {
    if (valor == nullptr) {
        return impresora.print(JSON_NULL);
    }
    
    PGM_P p = reinterpret_cast<PGM_P>(valor);
    size_t salida = impresora.print(JSON_STRING);
    char selec = pgm_read_byte(p);
    
    while (selec != '\0') {
        salida += imprimirCaracterJSON(impresora, selec);
        selec = pgm_read_byte(++p);
    }
    
    return (salida + impresora.print(JSON_STRING));
}

size_t imprimirDatoJSON(Print& impresora, const bool valor) {
    return impresora.print(valor ? F("true") : F("false"));
}

size_t imprimirDatoJSON(Print& impresora, Printable& valor) {
    return impresora.print(valor);
}
