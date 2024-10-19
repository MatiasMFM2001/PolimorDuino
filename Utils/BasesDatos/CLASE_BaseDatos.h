/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BASE_DATOS
#define BASE_DATOS

#define CLAVE_VERSION "VERSION"

#define TIPOS_NATIVOS_BD bool, float, double, signed char, unsigned char, signed int, unsigned int, signed short, unsigned short, signed long, unsigned long, signed long long, unsigned long long
#define TIPOS_CONVERTIBLES_BD JsonVariant, JsonArray, JsonObject

#define LIMITAR_STRING(valorOriginal, valorLimitado, MAX_LONGITUD, salida, nombreValor) \
    StringEstatica<MAX_LONGITUD> valorLimitado; \
 \
    if (!valorLimitado.agregarFinal(valorOriginal)) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se limitó la", nombreValor, 'a', MAX_LONGITUD, "caracteres, quedando '", valorLimitado.getContenido(), '\''); \
    }

#define LIMITAR_CLAVE(clave, copiaClave, MAX_LONGITUD_CLAVES, salida) \
    LIMITAR_STRING(clave, copiaClave, MAX_LONGITUD_CLAVES, salida, "clave")

#define GET_VALOR(clave, copiaClave, T, MAX_LONGITUD_CLAVES, salida) \
    LIMITAR_CLAVE(clave, copiaClave, MAX_LONGITUD_CLAVES, salida); \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::getValor(", copiaClave, ") con la BD corrupta. Se retornará el valor indeterminado"); \
 \
        if (this -> contieneClave(copiaClave)) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor previamente almacenado en esa clave."); \
        } \
        else { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado para ese tipo de datos."); \
        } \
    } \
 \
    if (!(this -> contieneClave(copiaClave))) { \
        return false; \
    }

#define GET_VALOR_SETTEANDO(clave, copiaClave, T, MAX_LONGITUD_CLAVES, valorPredeterminado, salida, ...) \
    LIMITAR_CLAVE(clave, copiaClave, MAX_LONGITUD_CLAVES, salida); \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::getValorSetteando(", copiaClave, ") con la BD corrupta. Se retornará el valor predeterminado"); \
        __VA_ARGS__; \
 \
        return false; \
    } \
 \
    if (!(this -> contieneClave(copiaClave))) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: La BD no contiene la clave", copiaClave, ". Se setteará el valor predeterminado"); \
        this -> setValor(clave, valorPredeterminado, salida); \
    } \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se corrompió la BD tras ejecutar BaseDatos::setValor(", copiaClave, ") desde BaseDatos::getValorSetteando()"); \
 \
        if (!(this -> contieneClave(copiaClave))) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado"); \
            __VA_ARGS__; \
 \
            return false; \
        } \
    }

#define SET_VALOR(clave, copiaValor, MAX_LONGITUD_CLAVES, salida) \
    LIMITAR_CLAVE(clave, copiaClave, MAX_LONGITUD_CLAVES, salida); \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::setValor(", copiaClave, ") con la BD corrupta"); \
        return false; \
    } \
 \
    if (!(this -> escribirBajoNivel(copiaClave.getContenido(), copiaValor, salida))) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Al intentar insertar la clave", copiaClave, ", falló porque la BaseDatos se llenó"); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    CLOG_PUNTERO_IMPRESORA(salida, "BaseDatos::setValor(", copiaClave, ") finalizó correctamente"); \
    return true;

#define DECLARAR_METODO_ABSTRACTO_BD(nombre, retorno, atributosAdicionales, ...) \
    virtual retorno nombre(__VA_ARGS__, Print *salida) atributosAdicionales = 0;

#define DECLARAR_LEER_BAJO_NIVEL_ABSTRACTO_BD(T_VALOR) \
    DECLARAR_METODO_ABSTRACTO_BD(leerBajoNivel, bool,, const char *clave, T_VALOR &variableASobreescribir);

#define DECLARAR_ESCRIBIR_BAJO_NIVEL_ABSTRACTO_BD(T_VALOR) \
    DECLARAR_METODO_ABSTRACTO_BD(escribirBajoNivel, bool,, char *copiaClave, T_VALOR copiaValor);

#define DEFINIR_METODO_BD(nombre, retorno, atributosAdicionales, ...) \
    retorno nombre(__VA_ARGS__, [[maybe_unused]] Print *salida) atributosAdicionales override

#include <ArduinoJson.h>
#include "../FuncionesGlobales.h"
#include "../../Medidores/Callbacks/INTERFAZ_CallbackResultadoMutable.h"
#include "../EstructurasDatos/Cadenas/CLASE_StringEstatica.h"
#include "../../Logger/FuncionesLoggers.h"
#include "../MACRO_ForEach.h"
#include "../INTERFAZ_Inicializable.h"
    template <size_t MAX_LONGITUD_CLAVES, size_t MAX_LONGITUD_STRINGS>
    class BaseDatos : public Inicializable, public Printable {
        private:
            bool leerAlInicializar;
            bool estaCorrupta;
            size_t version;
            CallbackResultadoMutable<BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>> *migrador;
        
        protected:
            virtual bool inicializarBajoNivel(void) = 0;
            
            FOR_EACH(DECLARAR_LEER_BAJO_NIVEL_ABSTRACTO_BD, TIPOS_NATIVOS_BD);
            FOR_EACH(DECLARAR_LEER_BAJO_NIVEL_ABSTRACTO_BD, TIPOS_CONVERTIBLES_BD);
            DECLARAR_LEER_BAJO_NIVEL_ABSTRACTO_BD(StringAbstracta);
            
            FOR_EACH(DECLARAR_ESCRIBIR_BAJO_NIVEL_ABSTRACTO_BD, TIPOS_NATIVOS_BD);
            FOR_EACH(DECLARAR_ESCRIBIR_BAJO_NIVEL_ABSTRACTO_BD, TIPOS_CONVERTIBLES_BD);
            DECLARAR_ESCRIBIR_BAJO_NIVEL_ABSTRACTO_BD(char *);
            
            virtual bool contieneClaveBajoNivel(const char *ingr) = 0;
            virtual bool guardarBajoNivel(Print *salida) = 0;
        
        public:
            BaseDatos(size_t version, CallbackResultadoMutable<BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>> *migrador, bool leerAlInicializar)
                : leerAlInicializar(leerAlInicializar), estaCorrupta(false), version(version), migrador(migrador)
            {}
            
            void inicializar(void) override {
                if (!(this -> leerAlInicializar)) {
                    return;
                }
                
                if (!(this -> inicializarBajoNivel())) {
                    FLOGS("BaseDatos::inicializar() - No se pudo inicializar correctamente");
                    return;
                }
                
                size_t versionDocumento;
                this -> getValorSetteando(CLAVE_VERSION, 1U, versionDocumento);
                
                LOG("BaseDatos::inicializar() - MessagePack deserializado correctamente, de versión = %d", versionDocumento);
                //imprimir(this -> documento);
                
                if ((versionDocumento >= (this -> version)) || !(this -> migrador)) {
                    return;
                }
                
                this -> migrador -> notificar(*this);
                this -> setValor(CLAVE_VERSION, this -> version);
                this -> guardar();
            }
            
            template <typename T_VALOR>
            bool getValor(const char *clave, T_VALOR &variableASobreescribir, Print *salida = nullptr) {
                GET_VALOR(clave, copiaClave, T_VALOR, MAX_LONGITUD_CLAVES, salida);
                return (this -> leerBajoNivel(copiaClave.getContenidoConstante(), variableASobreescribir, salida));
            }
            
            template <typename T_VALOR>
            bool setValor(const char *clave, const T_VALOR valor, Print *salida = nullptr) {
                T_VALOR copiaValor = valor;
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatos::setValor('", clave, "', ", valor, ')');
                SET_VALOR(clave, copiaValor, MAX_LONGITUD_CLAVES, salida);
            }
            
            bool setValor(const char *clave, StringEstatica<MAX_LONGITUD_STRINGS> &valor, Print *salida = nullptr) {
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatos::setValor('", clave, "', '", valor, "')");
                SET_VALOR(clave, valor.getContenido(), MAX_LONGITUD_CLAVES, salida);
            }
            
            bool setValor(const char *clave, const char *valor, Print *salida = nullptr) {
                LIMITAR_STRING(valor, copiaValor, MAX_LONGITUD_STRINGS, salida, "String a settear")
                return (this -> setValor(clave, copiaValor, salida));
            }
            
            bool setValor(const char *clave, const StringAbstracta &valor, Print *salida = nullptr) {
                return (this -> setValor(clave, valor.getContenidoConstante(), salida));
            }
            
            template <typename T_VALOR>
            bool getValorSetteando(const char *clave, T_VALOR valorPredeterminado, T_VALOR &variableASobreescribir, Print *salida = nullptr) {
                GET_VALOR_SETTEANDO(clave, copiaClave, T_VALOR, MAX_LONGITUD_CLAVES, valorPredeterminado, salida, variableASobreescribir = valorPredeterminado);
                return (this -> leerBajoNivel(copiaClave.getContenidoConstante(), variableASobreescribir, salida));
            }
            
            bool getValorSetteando(const char *clave, const char *valorPredeterminado, StringAbstracta &variableASobreescribir, Print *salida = nullptr) {
                GET_VALOR_SETTEANDO(clave, copiaClave, T_VALOR, MAX_LONGITUD_CLAVES, valorPredeterminado, salida, variableASobreescribir.agregarFinal(valorPredeterminado));
                return (this -> leerBajoNivel(copiaClave.getContenidoConstante(), variableASobreescribir, salida));
            }
            
            bool guardar(Print *salida = nullptr) {
                if (this -> estaCorrupta) {
                    CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se accedió a BaseDatos::guardar() con la BD corrupta");
                    return false;
                }
                
                if (!(this -> guardarBajoNivel(salida))) {
                    FLOGS("BaseDatos::guardar() - No se pudo guardar correctamente");
                    return false;
                }
                
                CLOG_PUNTERO_IMPRESORA(salida, "BaseDatos::guardar() - Entradas guardadas correctamente");
                return true;
            }
            
            bool contieneClave(const StringEstatica<MAX_LONGITUD_CLAVES> &ingr) {
                return (this -> contieneClaveBajoNivel(ingr.getContenidoConstante()));
            }
            
            bool contieneClave(const char *ingr) {
                #ifndef ENABLE_LOG4ARDUINO
                    Print *_log4arduino_target = nullptr;
                #endif
                
                LIMITAR_CLAVE(ingr, copiaClave, MAX_LONGITUD_CLAVES, _log4arduino_target);
                return (this -> contieneClave(copiaClave));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "BaseDatos", leerAlInicializar, estaCorrupta, version, migrador);
            }
    };
#endif
