/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

// Robado de https://stackoverflow.com/a/1872506

/**
 * @brief Convierte a String el token de pre-preprocesador especificado.
 * @param arg El token a convertir
 * @returns El token convertido a un string-literal de C
 */
#define STRINGIZE(arg)  STRINGIZE1(arg)

#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

/**
 * @brief Concatena ambos tokens de pre-preprocesador especificados.
 * @param arg1 El primer token a convertir
 * @param arg2 El segundo token a convertir
 * @returns Un nuevo token, creado concatenando los otros dos tokens
 */
#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)

#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_0(what, x, ...)

#define FOR_EACH_1(what, x, ...) what(x)

#define FOR_EACH_2(what, x, ...)\
  what(x);\
  FOR_EACH_1(what,  __VA_ARGS__);

#define FOR_EACH_3(what, x, ...)\
  what(x);\
  FOR_EACH_2(what, __VA_ARGS__);

#define FOR_EACH_4(what, x, ...)\
  what(x);\
  FOR_EACH_3(what,  __VA_ARGS__);

#define FOR_EACH_5(what, x, ...)\
  what(x);\
 FOR_EACH_4(what,  __VA_ARGS__);

#define FOR_EACH_6(what, x, ...)\
  what(x);\
  FOR_EACH_5(what,  __VA_ARGS__);

#define FOR_EACH_7(what, x, ...)\
  what(x);\
  FOR_EACH_6(what,  __VA_ARGS__);

#define FOR_EACH_8(what, x, ...)\
  what(x);\
  FOR_EACH_7(what,  __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N // Retorna la cantidad de parámetros enviados a FOR_EACH()
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, ...) CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__)

/**
 * @brief Ejecuta la función/macro especificada sobre todos los argumentos especificados.
 * @param what La función/macro especificada
 * @param ... La lista de elementos a procesar individualmente
 */
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)
