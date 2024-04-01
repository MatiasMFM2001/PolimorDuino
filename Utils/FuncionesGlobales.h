#ifndef FUNCIONES_GLOBALES
#define FUNCIONES_GLOBALES

#include "InclusionTaskSchedulerDeclarations.h"
#include "ENUM_Prioridad.h"
#include "InclusionLog4Arduino.h"
#include <Arduino.h>
#include "DeclaracionVariablesGlobales.h"
    bool enRango(short valor, short min, short max);
  	short limitarRango(short valor, short min, short max);
  	bool iguales(short num1, short num2, short difMax);
  	//Scheduler* getNivel(Prioridad ingr);
  	bool esPar (short num);
    long multiplicarNumIteraciones(long numTerminos, unsigned long multiplicador);
    
    void notificarAlarma();
    void activarAlarma();
    void desactivarAlarma();
#endif
