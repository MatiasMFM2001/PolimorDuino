/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef FUNCIONES_GLOBALES
#define FUNCIONES_GLOBALES

#include <Array.h>
#include "../Medidores/Condiciones/CLASE_AdaptadorFuncionCondicion.h"
#include "CLASE_StringEstatica.h"
    /**
     * @brief Determina si el valor ingresado está dentro de los límites
     *  (inclusivos) especificados.
     * 
     * @tparam T El tipo de dato de los valores a procesar.
     * @param valor El valor ingresado.
     * @param min El valor mínimo del rango especificado.
     * @param max El valor máximo del rango especificado.
     * @returns @c true si el valor está dentro de los límites, @c false
     *  en caso contrario.
     */
    template <typename T>
    bool enRango(T valor, T min, T max) {
        return (valor >= min) && (valor <= max);
    }
    
    /**
     * @brief Se asegura que el valor ingresado esté dentro de los límites
     *  (inclusivos) especificados.
     * 
     * @tparam T El tipo de dato de los valores a procesar y retornar.
     * @param valor El valor ingresado.
     * @param min El valor mínimo del rango especificado.
     * @param max El valor máximo del rango especificado.
     * @returns El valor ingresado si está dentro de los límites, el valor
     *  mínimo si éste es mayor al ingreado, o el valor máximo si éste es menor
     *  al ingresado.
     */
    template <typename T>
    T limitarRango(T valor, T min, T max) {
        return constrain(valor, min, max);
    }
    
    /**
     * @brief Determina si dos números son cercanos entre sí, teniendo en cuenta
     *  el valor de tolerancia máximo.
     * 
     * @tparam T El tipo de dato de los valores a procesar.
     * @param num1 El primer número a comparar.
     * @param num2 El segundo número a comparar.
     * @param max La tolerancia/distancia máxima a contemplar.
     * @returns @c true si la diferencia entre los números es menor o igual a
     *  la tolerancia máxima, @c false en caso contrario.
     */
    template <typename T>
    bool iguales(T num1, T num2, T difMax) {
        T dif = (num1 - num2);
        return (abs(dif) < difMax);
    }
    
    /**
     * @brief Determina si dos valores son iguales entre sí.
     * 
     * @tparam T El tipo de dato de los valores a procesar.
     * @param valor1 El primer valor a comparar.
     * @param valor2 El segundo valor a comparar.
     * @returns @c true si los valores son iguales, @c false en caso contrario.
     */
    template <typename T>
    bool iguales(const T &valor1, const T &valor2) {
        return (valor1 == valor2);
    }
    
    bool cadenasIguales(const char* const &valor1, const char* const &valor2);

    /**
     * @brief Determina si el número ingresado es par.
     * 
     * @tparam T El tipo de dato del valor a procesar.
     * @param num El número a verificar.
     * @returns @c true si el número es par, @c false en caso contrario.
     */
    template <typename T>
    bool esPar(T num) {
        return (num % 2) == 0;
    }
    
    /**
     * @brief Intercambia los elementos del array de las posiciones
     *  especificadas.
     *
     * @tparam T El tipo de dato de los valores almacenados en el array.
     * @tparam S La cantidad máxima de elementos del array a procesar.
     * @param array El array a procesar.
     * @param pos1 La primera posición a intercambiar.
     * @param pos2 La segunda posición a intercambiar.
     */
    template <typename T, size_t S>
    void permutar(Array<T, S> &array, size_t pos1, size_t pos2) {
        T selec = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = selec;
    }
    
    /**
     * @brief Invierte el orden de los elementos del array especificado.
     *
     * @tparam T El tipo de dato de los valores almacenados en el array.
     * @tparam S La cantidad máxima de elementos del array a procesar.
     * @param array El array a procesar.
     */
    template <typename T, size_t S>
    void invertirOrden(Array<T, S> &array) {
        for (size_t origen = 0; origen < (array.size() / 2); ++origen) {
            size_t destino = array.size() - origen - 1;
            permutar(array, origen, destino);
        }
    }
    
    /**
     * @brief Agrega el valor especificado al array múltiples veces, según la
     *  capacidad restante y la cantidad máxima especificada.
     *
     * @tparam T El tipo de dato de los valores almacenados en el array.
     * @tparam S La cantidad máxima de elementos del array a procesar.
     * @param array El array a procesar.
     * @param valor El valor a agregar al array.
     * @param maxIteraciones La cantidad máxima de elementos a agregar, aunque
     *  el array tenga mayor capacidad disponible.
     */
    template <typename T, size_t S>
    void completar(Array<T, S> &array, T valor, size_t maxIteraciones = -1) {
        for (size_t cont = 0; (cont < maxIteraciones) && !array.full(); ++cont) {
            array.push_back(valor);
        }
    }
    
    /**
     * @brief Agrega todos los elementos del array de entrada, al final del de
     *  salida.
     *
     * @tparam T El tipo de dato de los valores almacenados en ambos arrays.
     * @tparam S_ENTRADA La cantidad máxima de elementos del array de entrada.
     * @tparam S_SALIDA La cantidad máxima de elementos del array de salida.
     * @param entrada El array origen.
     * @param salida El array destino.
     */
    template <typename T, size_t S_ENTRADA, size_t S_SALIDA>
    void agregarFinal(Array<T, S_ENTRADA> &entrada, Array<T, S_SALIDA> &salida) {
        for (T selec: entrada) {
            salida.push_back(selec);
        }
    }
    
    /**
     * @brief Agrega todos los elementos del array de entrada (cuyo fin se
     *  alcanza al procesar el elemento igual al @c valorFinal), al final del de
     *  salida.
     *
     * @tparam T El tipo de dato de los valores almacenados en ambos arrays.
     * @tparam S_SALIDA La cantidad máxima de elementos del array de salida.
     * @param entrada El array origen.
     * @param salida El array destino.
     * @param valorFinal El valor que indica el fin del array.
     * @param agregarValorFinal @c true para agregar el @c valorFinal al final
     *  del array, @c false para el caso contrario.
     */
    template <typename T, size_t S_SALIDA>
    void agregarFinalArrayTerminado(const T *entrada, Array<T, S_SALIDA> &salida, T valorFinal, bool agregarValorFinal) {
        if (!entrada) {
            return;
        }
        
        T selec = *entrada;
        
        while (selec != valorFinal) {
            salida.push_back(selec);
            selec = *(++entrada);
        }
        
        if (!agregarValorFinal) {
            return;
        }
        
        if (salida.full()) {
            salida.pop_back();
        }
        
        salida.push_back(valorFinal);
    }
    
    /**
     * @brief Agrega el valor especificado al array múltiples veces, según la
     *  capacidad restante y la cantidad máxima especificada.
     *
     * @tparam T El tipo de dato de los valores almacenados en el array.
     * @tparam S La cantidad máxima de elementos del array a procesar.
     * @param array El array a procesar.
     * @param valor El valor a buscar en el array.
     * @returns @c true si el @c array contiene el @c valor, @c false en el caso
     *  contrario.
     */
    template <typename T, size_t S>
    bool contiene(const Array<T, S> &array, const T valor, bool (*comparador)(const T &, const T &) = &iguales) {
        for (const T &selec: array) {
            if (comparador(selec, valor)) {
                return true;
            }
        }
        
        return false;
    }
    
    /**
     * @brief Compara los dos arrays especificados.
     *
     * @tparam T El tipo de dato de los valores almacenados en el array.
     * @tparam S_ARRAY_1 La cantidad máxima de elementos del array 1.
     * @tparam S_ARRAY_2 La cantidad máxima de elementos del array 2.
     * @param array El array a procesar.
     * @param valor El valor a buscar en el array.
     * @returns @c true si los dos arrays son iguales, @c false en el caso
     *  contrario.
     */
    template <typename T, size_t S_ARRAY_1, size_t S_ARRAY_2>
    bool iguales(Array<T, S_ARRAY_1> &array1, Array<T, S_ARRAY_2> &array2, bool (*comparador)(const T &, const T &) = &iguales) {
        if (array1.size() != array2.size()) {
            return false;
        }
        
        for (size_t cont = 0; cont < array1.size(); ++cont) {
            if (!comparador(array1[cont], array2[cont])) {
                return false;
            }
        }
        
        return true;
    }
    
    /**
     * @brief Permite multiplicar una cantidad de iteraciones de una tarea (si
     *  es distinta a @c TASK_FOREVER) por otra cantidad.
     * 
     * @param numTerminos La cantidad de iteraciones de la tarea.
     * @param multiplicador La cantidad que multiplicará al número anterior.
     * @returns @c TASK_FOREVER si la cantidad de iteraciones es igual a
     *  @c TASK_FOREVER, el resultado de la multiplicación en caso contrario.
     */
    long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador);
    
    template <size_t CAPACIDAD_STRING_NUMERO>
    bool parsearNumero(Stream &entrada, JsonDocument &salida) {
        while (isSpace(entrada.peek())) {
            entrada.read();
        }
        
        int datoLeido = entrada.peek();
        Array<int, 3> caracteresPermitidos({'.', '+', '-'});
        
        if (!isDigit(datoLeido) && !contiene(caracteresPermitidos, datoLeido)) {
            return false;
        }

        StringEstatica<CAPACIDAD_STRING_NUMERO> bufferNumero;
        AdaptadorFuncionCondicion<int> detectorBlanco(&isSpace);
        bufferNumero.agregarCaracteresHasta(entrada, detectorBlanco);

        char *posBufferFinal;
        long entero = strtol(bufferNumero.getContenido(), &posBufferFinal, 0);

        if (*posBufferFinal == '\0') {
            salida.set(entero);
            return true;
        }

        double real = strtod(bufferNumero.getContenido(), &posBufferFinal);

        if (*posBufferFinal == '\0') {
            salida.set(real);
            return true;
        }
        
        return false;
    }
    
    template <size_t CAPACIDAD_STRING_NUMERO>
    bool parsearArgumento(Stream &entrada, JsonDocument &salida) {
        if (parsearNumero<CAPACIDAD_STRING_NUMERO>(entrada, salida)) {
            return true;
        }
        
        DeserializationError retorno = deserializeJson(salida, entrada);
        
        if (retorno != DeserializationError::Ok) {
            LOG("ERROR: Deserializar un argumento del stream falló con el error %s.", retorno.c_str());
            return false;
        }
        
        FLOGS("DOCUMENTO INTERMEDIO:");
        imprimir(salida);
        
        return true;
    }
#endif
