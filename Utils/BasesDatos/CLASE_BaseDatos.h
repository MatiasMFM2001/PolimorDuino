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

#define GET_VALOR(clave, T, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::getValor('", clave, "') con la BD corrupta. Se retornará el valor indeterminado"); \
 \
        if (this -> contieneClave(clave)) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor previamente almacenado en esa clave."); \
        } \
        else { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado para ese tipo de datos."); \
        } \
    } \
 \
    if (!(this -> contieneClave(clave))) { \
        return false; \
    }

#define GET_VALOR_SETTEANDO(clave, T, valorPredeterminado, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::getValorSetteando('", clave, "') con la BD corrupta. Se retornará el valor predeterminado"); \
        return false; \
    } \
 \
    if (!(this -> contieneClave(clave))) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: La BD no contiene la clave '", clave, "'. Se setteará el valor predeterminado"); \
        this -> setValor(clave, valorPredeterminado, salida); \
    } \
 \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se corrompió la BD tras ejecutar BaseDatos::getValorSetteando('", clave, "')"); \
 \
        if (!(this -> contieneClave(clave))) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se retornará el valor predeterminado"); \
            return valorPredeterminado; \
        } \
    }

#define SET_VALOR(clave, copiaValor, MAX_LONGITUD_CLAVES, salida) \
    if (this -> estaCorrupta) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se ejecutó BaseDatos::setValor('", clave, "') con la BD corrupta"); \
        return false; \
    } \
 \
    StringEstatica<MAX_LONGITUD_CLAVES> copiaClave; \
 \
    if (!copiaClave.agregarFinal(clave)) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: Se limitó la clave a", MAX_LONGITUD_CLAVES, "caracteres, quedando '", copiaClave.getContenido(), '\''); \
    } \
 \
    CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatos::setValor('", clave, "') =", copiaClave.getContenido()); \
 \
    if (!(this -> escribirBajoNivel(copiaClave.getContenido(), copiaValor, salida))) { \
        CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Al intentar insertar la clave '", clave, "', falló porque la BaseDatos se llenó"); \
        this -> estaCorrupta = true; \
        return false; \
    } \
 \
    CLOG_PUNTERO_IMPRESORA(salida, "BaseDatos::setValor('", clave, "') finalizó correctamente"); \
    return true;

#define DECLARAR_METODO_ABSTRACTO_BD(nombre, retorno, atributosAdicionales, ...) \
    virtual retorno nombre(__VA_ARGS__, Print *salida) atributosAdicionales = 0;

#define DECLARAR_LEER_BAJO_NIVEL_ABSTRACTO_BD(T_VALOR) \
    DECLARAR_METODO_ABSTRACTO_BD(leerBajoNivel, bool,, const char *clave, T_VALOR &variableASobreescribir);

#define DECLARAR_ESCRIBIR_BAJO_NIVEL_ABSTRACTO_BD(T_VALOR) \
    DECLARAR_METODO_ABSTRACTO_BD(escribirBajoNivel, bool,, char *copiaClave, T_VALOR copiaValor);

#define DEFINIR_METODO_BD(nombre, retorno, atributosAdicionales, ...) \
    retorno nombre(__VA_ARGS__, Print *salida) atributosAdicionales override

#include <ArduinoJson.h>
#include "../FuncionesGlobales.h"
#include "../../Medidores/Callbacks/INTERFAZ_CallbackResultadoMutable.h"
#include "../CLASE_StringEstatica.h"
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
                GET_VALOR(clave, T_VALOR, salida);
                return (this -> leerBajoNivel(clave, variableASobreescribir, salida));
            }
            
            template <typename T_VALOR>
            bool setValor(const char *clave, const T_VALOR valor, Print *salida = nullptr) {
                T_VALOR copiaValor = valor;
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatos::setValor('", clave, "', ", valor, ')');
                SET_VALOR(clave, copiaValor, MAX_LONGITUD_CLAVES, salida);
            }
            
            bool setValor(const char *clave, const char *valor, Print *salida = nullptr) {
                StringEstatica<MAX_LONGITUD_STRINGS> copiaValor(valor);
                CLOG_PUNTERO_IMPRESORA(salida, "Escribiendo BaseDatos::setValor('", clave, "', '", valor, "')");
                SET_VALOR(clave, copiaValor.getContenido(), MAX_LONGITUD_CLAVES, salida);
            }
            
            template <typename T_VALOR>
            bool getValorSetteando(const char *clave, T_VALOR valorPredeterminado, T_VALOR &variableASobreescribir, Print *salida = nullptr) {
                GET_VALOR_SETTEANDO(clave, T_VALOR, valorPredeterminado, salida);
                return (this -> leerBajoNivel(clave, variableASobreescribir, salida));
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
            
            bool contieneClave(const char *ingr) {
                return (this -> contieneClaveBajoNivel(ingr));
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
