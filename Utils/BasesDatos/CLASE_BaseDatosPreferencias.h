/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef BASE_DATOS_PREFERENCIAS
#define BASE_DATOS_PREFERENCIAS

#define DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(T_VALOR, metodo) \
    DEFINIR_METODO_BD(leerBajoNivel, bool,, const char *clave, T_VALOR &variableASobreescribir) { \
        variableASobreescribir = (this -> preferencias.metodo(clave)); \
        return true; \
    }

#define RETORNAR_ERROR(bufferDocumento, bufferMsgPack) \
    bufferDocumento.clear(); \
    delete[] bufferMsgPack; \
    return false;

#define DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS_JSON(T_VALOR) \
    DEFINIR_METODO_BD(leerBajoNivel, bool,, const char *clave, T_VALOR &variableASobreescribir) { \
        size_t numBytesRequeridos = (this -> preferencias.getBytesLength(clave)); \
 \
        char *bufferMsgPack = new char[numBytesRequeridos + 1]; \
        StaticJsonDocument<CAPACIDAD_BUFFER_JSON> bufferDocumento; \
 \
        size_t retornoLectura = (this -> preferencias.getBytes(clave, bufferMsgPack, numBytesRequeridos)); \
 \
        if (retornoLectura != numBytesRequeridos) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ADVERTENCIA: numBytesRequeridos =", numBytesRequeridos, ", pero retornoLectura =", retornoLectura); \
            RETORNAR_ERROR(bufferDocumento, bufferMsgPack); \
        } \
 \
        DeserializationError retornoDeserial = deserializeMsgPack(bufferDocumento, bufferMsgPack, numBytesRequeridos); \
 \
        if (retornoDeserial != DeserializationError::Ok) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ERROR: Deserializar el MessagePack del buffer falló con el error", retornoDeserial.c_str()); \
            RETORNAR_ERROR(bufferDocumento, bufferMsgPack); \
        } \
 \
        if (!(bufferDocumento.template is<T_VALOR>())) { \
            CLOG_PUNTERO_IMPRESORA(salida, "ERROR: La variante leída no es del tipo " #T_VALOR); \
            RETORNAR_ERROR(bufferDocumento, bufferMsgPack); \
        } \
 \
        variableASobreescribir = (bufferDocumento.template as<T_VALOR>()); \
        bufferDocumento.clear(); \
        delete[] bufferMsgPack; \
 \
        return true; \
    }

#define DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(T_VALOR, metodo) \
    DEFINIR_METODO_BD(escribirBajoNivel, bool,, char *copiaClave, T_VALOR copiaValor) { \
        return ((this -> preferencias.metodo(copiaClave, copiaValor)) > 0); \
    }

#define DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS_JSON(T_VALOR) \
    DEFINIR_METODO_BD(escribirBajoNivel, bool,, char *copiaClave, T_VALOR copiaValor) { \
        size_t numBytesRequeridos = measureMsgPack(copiaValor); \
        char *bufferMsgPack = new char[numBytesRequeridos + 1]; \
 \
        serializeMsgPack(copiaValor, bufferMsgPack, numBytesRequeridos); \
        bool retorno = ((this -> preferencias.putBytes(copiaClave, bufferMsgPack, copiaValor)) == numBytesRequeridos); \
 \
        delete[] bufferMsgPack; \
        return retorno; \
    }

#ifdef ESP32
    #include <nvs.h>
#else
    #define NVS_KEY_NAME_MAX_SIZE 32
#endif

#include <Preferences.h>
#include "CLASE_BaseDatos.h"
    template <size_t CAPACIDAD_BUFFER_JSON, size_t MAX_LONGITUD_STRINGS, size_t MAX_LONGITUD_CLAVES = (NVS_KEY_NAME_MAX_SIZE - 1)>
    class BaseDatosPreferencias : public BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS> {
        private:
            Preferences preferencias;
            const char *nombreEspacio;
            bool soloLectura;
        
        protected:
            bool inicializarBajoNivel(void) override {
                return (this -> preferencias.begin(this -> nombreEspacio, this -> soloLectura));
            }
            
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(bool, getBool);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(float, getFloat);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(double, getDouble);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(signed char, getChar);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(unsigned char, getUChar);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(signed int, getInt);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(unsigned int, getUInt);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(signed short, getShort);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(unsigned short, getUShort);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(signed long, getLong);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(unsigned long, getULong);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(signed long long, getLong64);
            DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS(unsigned long long, getULong64);
            
            FOR_EACH(DEFINIR_LEER_BAJO_NIVEL_BD_PREFERENCIAS_JSON, TIPOS_CONVERTIBLES_BD);
            
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(bool, putBool);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(float, putFloat);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(double, putDouble);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(signed char, putChar);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(unsigned char, putUChar);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(signed int, putInt);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(unsigned int, putUInt);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(signed short, putShort);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(unsigned short, putUShort);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(signed long, putLong);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(unsigned long, putULong);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(signed long long, putLong64);
            DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS(unsigned long long, putULong64);
            
            FOR_EACH(DEFINIR_ESCRIBIR_BAJO_NIVEL_BD_PREFERENCIAS_JSON, TIPOS_CONVERTIBLES_BD);
            
            bool guardarBajoNivel(Print *salida) override {
                return true;
            }
            
            bool contieneClaveBajoNivel(const char *ingr) override {
                return (this -> preferencias.isKey(ingr));
            }
        
        public:
            BaseDatosPreferencias(size_t version, CallbackResultadoMutable<BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>> *migrador, const char *nombreEspacio, bool soloLectura)
                : BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>(version, migrador, true)
                , preferencias(Preferences()), nombreEspacio(nombreEspacio), soloLectura(soloLectura)
            {}
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_A_JSON(impresora, "BaseDatosPreferencias") + SUPERCLASES_A_JSON(impresora, (BaseDatos<MAX_LONGITUD_CLAVES, MAX_LONGITUD_STRINGS>))
                    + impresora.println()
                    //+ serializeJsonPretty(this -> documento, impresora)
                    ;
            }
    };
#endif
