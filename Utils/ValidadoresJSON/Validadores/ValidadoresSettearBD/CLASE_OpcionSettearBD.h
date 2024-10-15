/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef OPCION_SETTEAR_BD
#define OPCION_SETTEAR_BD

#include "../CLASE_ValidadorArray.h"
#include "../../../EstructurasDatos/Conjuntos/CLASE_ArrayConjunto.h"
#include "../../../../Medidores/Condiciones/CLASE_ValorEnConjunto.h"
#include "../../Condiciones/Indices/CLASE_CondicionRangoIndices.h"
#include "../../../FuncionesGlobales.h"
#include "../../../EstructurasDatos/Conjuntos/CLASE_AdaptadorFuncionComparadorIgualdad.h"
#include "../CLASE_ValidadorPrimitivo.h"
    template <size_t CAPACIDAD_TIPOS_DATOS>
    class OpcionSettearBD : public ValidadorJSON {
        private:
            AdaptadorFuncionComparadorIgualdad<const char *> adaptadorIgualdad;
            ArrayConjunto<const char *, CAPACIDAD_TIPOS_DATOS> tiposDatosPermitidos;
            ValorEnConjunto<const char *, CAPACIDAD_TIPOS_DATOS> condicionValidezTipoDato;
            ValidadorPrimitivo<const char *> validadorTipoDato;
            CondicionRangoIndices condicionTipoDato;
            
            ValidadorJSON *validadorValor;
            CondicionRangoIndices condicionValor;
            
            ValidadorArray<3> validadorElementos;
        
        public:
            OpcionSettearBD(ValidadorJSON *validadorValor, Array<const char *, CAPACIDAD_TIPOS_DATOS> tiposDatosPermitidos)
                : adaptadorIgualdad(AdaptadorFuncionComparadorIgualdad<const char *>(&cadenasIguales))
                , tiposDatosPermitidos(ArrayConjunto<const char *, CAPACIDAD_TIPOS_DATOS>(&(this -> adaptadorIgualdad), tiposDatosPermitidos))
                , condicionValidezTipoDato(ValorEnConjunto<const char *, CAPACIDAD_TIPOS_DATOS>(&(this -> tiposDatosPermitidos)))
                , validadorTipoDato(ValidadorPrimitivo<const char *>(&(this -> condicionValidezTipoDato)))
                , condicionTipoDato(CondicionRangoIndices(&(this -> validadorTipoDato), 1))
                
                , validadorValor(validadorValor)
                , condicionValor(CondicionRangoIndices(this -> validadorValor, 2))
                
                , validadorElementos(ValidadorArray<3>(Array<CondicionValidador<size_t, JsonArrayConst> *, 3>({&(this -> condicionTipoDato), &(this -> condicionValor)}), true))
            {}
            
            OpcionSettearBD(ValidadorJSON *validadorValor = nullptr, const char *tipoDato = "")
                : OpcionSettearBD(validadorValor, Array<const char *, CAPACIDAD_TIPOS_DATOS>({tipoDato}))
            {}
            
            bool esValido(const JsonVariantConst &variante, NodoPilaJSON &pilaClaves) const override {
                return (this -> validadorElementos.esValido(variante, pilaClaves));
            }

            /**
             * @brief Imprime los valores de las variables de instancia a la
             *  impresora especificada.
             *
             * @param impresora Referencia a la impresora especificada.
             * @returns La cantidad de bytes escritos a la impresora.
             */
            virtual size_t printTo(Print &impresora) const override {
                return OBJETO_SIN_SUPER_A_JSON(impresora, "OpcionSettearBD");
            }

            using ValidadorJSON::esValido;
    };
#endif
