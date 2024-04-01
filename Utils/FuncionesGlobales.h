#ifndef FUNCIONES_GLOBALES
#define FUNCIONES_GLOBALES

#include "InclusionTaskSchedulerDeclarations.h"
#include "ENUM_Prioridad.h"
#include "InclusionLog4Arduino.h"
#include <Arduino.h>
#include "DeclaracionVariablesGlobales.h"
	/**
	 * @brief Determina si el valor ingresado está dentro de los límites
	 *  (inclusivos) especificados.
     * 
     * @param valor El valor ingresado.
     * @param min El valor mínimo del rango especificado.
     * @param max El valor máximo del rango especificado.
     * @returns @code true si el valor está dentro de los límites, @code false
     *  en caso contrario.
     */
    bool enRango(short valor, short min, short max);
    
    /**
	 * @brief Se asegura que el valor ingresado esté dentro de los límites
	 *  (inclusivos) especificados.
     * 
     * @param valor El valor ingresado.
     * @param min El valor mínimo del rango especificado.
     * @param max El valor máximo del rango especificado.
     * @returns El valor ingresado si está dentro de los límites, el valor
     *  mínimo si éste es mayor al ingreado, o el valor máximo si éste es menor
     *  al ingresado.
     */
  	short limitarRango(short valor, short min, short max);
    
    /**
	 * @brief Determina si dos números son cercanos entre sí, teniendo en cuenta
     *  el valor de tolerancia máximo.
     * 
     * @param num1 El primer número a comparar.
     * @param num2 El segundo número a comparar.
     * @param max La tolerancia/distancia máxima a contemplar.
     * @returns @code true si la diferencia entre los números es menor o igual a
     *  la tolerancia máxima, @code false en caso contrario.
     */
  	bool iguales(short num1, short num2, short difMax);
  	
    /**
	 * @brief Determina si el número ingresado es par.
     * 
     * @param num El número a verificar.
     * @returns @code true si el número es par, @code false en caso contrario.
     */
  	bool esPar(short num);
    long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador);
#endif
