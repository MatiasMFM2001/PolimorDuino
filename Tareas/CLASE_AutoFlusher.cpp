#include "CLASE_AutoFlusher.h"
#include <Arduino.h>

AutoFlusher::AutoFlusher(Print* impresora, long msEntreLlamados, Scheduler* planif)
    : Task(msEntreLlamados, TASK_FOREVER, planif, false)
    , impresora(impresora)
{}
        
bool AutoFlusher::Callback() {
    //Serial.println("EJECUTANDO AutoFlusher::Callback()");
    this -> impresora -> flush();
    
    return true;
}