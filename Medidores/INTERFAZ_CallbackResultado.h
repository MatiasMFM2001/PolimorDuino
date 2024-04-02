#ifndef CALLBACK_RESULTADO
#define CALLBACK_RESULTADO
    template <typename T>
    class CallbackResultado {
        public:
            virtual void notificar(T resultado) = 0;
    }
#endif
