#ifndef BUFFER_DATOS
#define BUFFER_DATOS

#include <Print.h>
#include <Array.h>
    template <size_t TNumBytes>
    
    class BufferDatos: public Print {
        private:
            Array<byte, TNumBytes> datos;
            Print* salida;
        
        public:
            BufferDatos(Print* salida = nullptr)
                : Print()
                , salida(salida)
            {}
        
            size_t write(byte ingr) override {
                if (this -> datos.full()) {
                    return 0;
                }
                
                this -> datos.push_back(ingr);
                return 1;
            }
            
            void flush() override {
                if (this -> salida == nullptr) {
                    return;
                }
                
                this -> salida -> write(this -> datos.data(), this -> datos.size());
                this -> datos.clear();
            }
    };
#endif