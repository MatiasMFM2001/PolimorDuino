#ifndef FUNCIONES_GLOBALES
#define FUNCIONES_GLOBALES

#include <Array.h>
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
    
    template <typename T, size_t S>
    void permutar(Array<T, S> &array, size_t pos1, size_t pos2) {
        T selec = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = selec;
    }
    
    template <typename T, size_t S>
    void invertirOrden(Array<T, S> &array) {
        for (size_t origen = 0; origen < (array.size() / 2); ++origen) {
            size_t destino = array.size() - origen - 1;
            permutar(array, origen, destino);
        }
    }
    
    template <typename T, size_t S>
    void completar(Array<T, S> &array, T valor, size_t maxIteraciones = -1) {
        for (size_t cont = 0; (cont < maxIteraciones) && !array.full(); ++cont) {
            array.push_back(valor);
        }
    }
    
    template <typename T, size_t S_ENTRADA, size_t S_SALIDA>
    void agregarFinal(Array<T, S_ENTRADA> &entrada, Array<T, S_SALIDA> &salida) {
        for (T selec: entrada) {
            salida.push_back(selec);
        }
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
#endif
