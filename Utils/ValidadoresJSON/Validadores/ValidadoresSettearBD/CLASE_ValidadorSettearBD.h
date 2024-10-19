/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef VALIDADOR_SETTEAR_BD
#define VALIDADOR_SETTEAR_BD

#include "CLASE_OpcionSettearBD.h"
#include "../../../EstructurasDatos/Mapas/CLASE_ArrayMapa.h"
#include "../../../../Medidores/Condiciones/CLASE_ClaveEnMapa.h"
    template <size_t CAPACIDAD_MAPA_OPCIONES, size_t CAPACIDAD_TIPOS_DATOS_OPCIONES>
    class ValidadorSettearBD : public ValidadorJSON {
        private:
            AdaptadorFuncionComparadorIgualdad<const char *> adaptadorIgualdad;
            ArrayMapa<const char *, OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES>, CAPACIDAD_MAPA_OPCIONES> mapaOpciones;
            ClaveEnMapa<const char *, OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES>, CAPACIDAD_MAPA_OPCIONES> condicionValidezClave;
            ValidadorPrimitivo<const char *> validadorClave;
            ValidadorPrimitivo<JsonArrayConst> validadorArray;
        
        public:
            ValidadorSettearBD(const Array<ElementoMapa<const char *, OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES>>, CAPACIDAD_MAPA_OPCIONES> opciones)
                : adaptadorIgualdad(AdaptadorFuncionComparadorIgualdad<const char *>(&cadenasIguales))
                , mapaOpciones(ArrayMapa<const char *, OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES>, CAPACIDAD_MAPA_OPCIONES>(&(this -> adaptadorIgualdad), opciones))
                , condicionValidezClave(ClaveEnMapa<const char *, OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES>, CAPACIDAD_MAPA_OPCIONES>(&(this -> mapaOpciones)))
                , validadorClave(ValidadorPrimitivo<const char *>(&(this -> condicionValidezClave)))
                , validadorArray(ValidadorPrimitivo<JsonArrayConst>())
            {}
        
            bool esValido(const JsonVariantConst &variante, NodoPilaJSON &pilaClaves) const override {
                if (!(this -> validadorArray.esValido(variante, pilaClaves))) {
                    return false;
                }
                
                const JsonArrayConst array = (variante.template as<JsonArrayConst>());
                const JsonVariantConst claveVariante = array[0];
                
                if (!(this -> validadorClave.esValido(claveVariante, pilaClaves))) {
                    return false;
                }
                
                const char *clave = (claveVariante.template as<const char *>());
                const OpcionSettearBD<CAPACIDAD_TIPOS_DATOS_OPCIONES> *opcion = (this -> mapaOpciones.getValorDe(clave));
                
                if (!opcion) {
                    pilaClaves.agregarFinalMensaje("ERROR: Se obtuvo un puntero a opción nulo, cuando no debería haber pasado. Retornando false");
                    pilaClaves.setDatoErroneo(variante);
                    pilaClaves.guardarNodosPila();
                    
                    return false;
                }
                
                return (opcion -> esValido(variante, pilaClaves));
            }
            
            /**
             * @brief Imprime el dato apuntado a la impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "ValidadorSettearBD", mapaOpciones, condicionValidezClave, validadorClave, validadorArray);
            }
    };
#endif
