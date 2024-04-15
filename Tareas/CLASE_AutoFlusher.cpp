#include "CLASE_AutoFlusher.h"
#include <Arduino.h>
#include "../Inclusiones/InclusionLog4Arduino.h"

AutoFlusher::AutoFlusher(Print *impresora, long msEntreLlamados, Scheduler *planif)
    : Task(msEntreLlamados, TASK_FOREVER, planif, false)
    , impresora(impresora)
{}
        
bool AutoFlusher::Callback(void) {
    LOG("EJECUTANDO AutoFlusher::Callback()");
    
    if (this -> impresora != nullptr) {
        this -> impresora -> flush();
    }
    else {
        LOG("AutoFlusher::Callback() - Saliendo porque this -> impresora == nullptr");
    }

    return true;
}
