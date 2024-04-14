#ifndef CALLBACK_RESULTADO
#define CALLBACK_RESULTADO

#include <Printable.h>
    template <typename T>
    class CallbackResultado : public Printable {
        public:
            virtual void notificar(T resultado) = 0;
    };
#endif
