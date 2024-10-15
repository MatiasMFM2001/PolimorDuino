/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CONDICION_RESULTADO_JSON
#define CONDICION_RESULTADO_JSON

#include "INTERFAZ_CondicionJSON.h"
#include "../../Medidores/Condiciones/INTERFAZ_CondicionResultado.h"
    template <typename T_DATO>
    class CondicionResultadoJSON : public CondicionResultado<T_DATO>, public CondicionJSON<T_DATO> {
        public:
            virtual void settearMensajeInvalido(const T_DATO &ingr, Print &salida) const = 0;
        
            bool esValido(const T_DATO &ingr, NodoPilaJSON &pilaClaves) const override {
                if (this -> esValido(ingr)) {
                    return true;
                }

                AdaptadorStringImpresora salida = pilaClaves.getAdaptadorMensaje();
                this -> settearMensajeInvalido(ingr, salida);
                
                return false;
            }
            
            using CondicionResultado<T_DATO>::esValido;
    };
#endif
