// Robado de https://stackoverflow.com/a/1872506

#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_ACUMULANDO_1(what, impresora, x, ...) what(impresora, x)

#define FOR_EACH_ACUMULANDO_2(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_1(what, impresora, __VA_ARGS__)

#define FOR_EACH_ACUMULANDO_3(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_2(what, impresora, __VA_ARGS__)
  
#define FOR_EACH_ACUMULANDO_4(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_3(what, impresora, __VA_ARGS__)
  
#define FOR_EACH_ACUMULANDO_5(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_4(what, impresora, __VA_ARGS__)
  
#define FOR_EACH_ACUMULANDO_6(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_5(what, impresora, __VA_ARGS__)
  
#define FOR_EACH_ACUMULANDO_7(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_6(what, impresora, __VA_ARGS__)
  
#define FOR_EACH_ACUMULANDO_8(what, impresora, x, ...)\
    what(impresora, x) + FOR_EACH_ACUMULANDO_7(what, impresora, __VA_ARGS__)

#define FOR_EACH_ACUMULANDO_NARG(...) FOR_EACH_ACUMULANDO_NARG_(__VA_ARGS__, FOR_EACH_ACUMULANDO_RSEQ_N())
#define FOR_EACH_ACUMULANDO_NARG_(...) FOR_EACH_ACUMULANDO_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ACUMULANDO_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N // Retorna la cantidad de parámetros enviados a FOR_EACH()
#define FOR_EACH_ACUMULANDO_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_ACUMULANDO_(N, what, impresora, x, ...) CONCATENATE(FOR_EACH_ACUMULANDO_, N)(what, impresora, x, __VA_ARGS__)
#define FOR_EACH_ACUMULANDO(what, impresora, x, ...) FOR_EACH_ACUMULANDO_(FOR_EACH_ACUMULANDO_NARG(x, __VA_ARGS__), what, impresora, x, __VA_ARGS__)
