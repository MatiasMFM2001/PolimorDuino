// Robado de https://stackoverflow.com/a/1872506

#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_ACUMULANDO_0(what, impresora, ...) 0

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

#define GET_ARG_COUNT(...) INTERNAL_GET_ARG_COUNT_PRIVATE(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define INTERNAL_GET_ARG_COUNT_PRIVATE(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

#define FOR_EACH_ACUMULANDO_(N, what, impresora, ...) CONCATENATE(FOR_EACH_ACUMULANDO_, N)(what, impresora, __VA_ARGS__)
#define FOR_EACH_ACUMULANDO(what, impresora, ...) FOR_EACH_ACUMULANDO_(GET_ARG_COUNT(__VA_ARGS__), what, impresora, __VA_ARGS__)
