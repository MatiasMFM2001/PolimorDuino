/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONVERSORES
#define CONVERSORES

#define INSTANCIAR_TIPO_A_STRING(T) \
    template <> \
    inline const __FlashStringHelper* tipoAString<T>(void) { \
        return F(#T); \
    }

#include <ArduinoJson.h>
    namespace conversores {
        template <typename T>
        inline const __FlashStringHelper *tipoAString(void) {
            return F("TIPO DESCONOCIDO");
        }
        
        INSTANCIAR_TIPO_A_STRING(bool)
        
        INSTANCIAR_TIPO_A_STRING(float)
        INSTANCIAR_TIPO_A_STRING(double)
        
        INSTANCIAR_TIPO_A_STRING(signed char)
        INSTANCIAR_TIPO_A_STRING(unsigned char)
        INSTANCIAR_TIPO_A_STRING(signed int)
        INSTANCIAR_TIPO_A_STRING(unsigned int)
        INSTANCIAR_TIPO_A_STRING(signed short)
        INSTANCIAR_TIPO_A_STRING(unsigned short)
        INSTANCIAR_TIPO_A_STRING(signed long)
        INSTANCIAR_TIPO_A_STRING(unsigned long)
        INSTANCIAR_TIPO_A_STRING(signed long long)
        INSTANCIAR_TIPO_A_STRING(unsigned long long)
        
        INSTANCIAR_TIPO_A_STRING(char *)
        INSTANCIAR_TIPO_A_STRING(const char *)
        INSTANCIAR_TIPO_A_STRING(String)
        INSTANCIAR_TIPO_A_STRING(std::string)
        
        INSTANCIAR_TIPO_A_STRING(JsonVariant)
        INSTANCIAR_TIPO_A_STRING(JsonArray)
        INSTANCIAR_TIPO_A_STRING(JsonObject)
        
        INSTANCIAR_TIPO_A_STRING(JsonVariantConst)
        INSTANCIAR_TIPO_A_STRING(JsonArrayConst)
        INSTANCIAR_TIPO_A_STRING(JsonObjectConst)
    }
#endif
