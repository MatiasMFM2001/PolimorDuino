/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef MENSAJE_TELEGRAM
#define MENSAJE_TELEGRAM

#include "../../../Utils/CLASE_StringEstatica.h"
#include <Printable.h>
    template <size_t CAPACIDAD_CONTENIDO>
    class MensajeTelegram : public Printable {
        private:
            StringEstatica<CAPACIDAD_CONTENIDO> contenido;
            int64_t idCanal;
            bool esMsjTexto;
            
        public:
            MensajeTelegram(const char *contenido = nullptr, int64_t idCanal = 0, bool esMensajeTexto = false)
                : contenido(StringEstatica<CAPACIDAD_CONTENIDO>(contenido)), idCanal(idCanal), esMsjTexto(esMensajeTexto)
            {}
            
            bool esValido(void) {
                return (!(this -> contenido.estaVacia()) && (this -> idCanal > 0));
            }
            
            StringEstatica<CAPACIDAD_CONTENIDO> &getContenido(void) {
                return (this -> contenido);
            }
            
            int64_t getIDCanal(void) {
                return (this -> idCanal);
            }
            
            bool esMensajeTexto(void) {
                return (this -> esMsjTexto);
            }
            
            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "MensajeTelegram", contenido, idCanal, esMsjTexto);
            }
    };
#endif
