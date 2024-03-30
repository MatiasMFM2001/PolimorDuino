
#include "CLASE_LectorADC.h"
//#include "CLASE_Ventilador.h"
#include <Arduino.h>
#include "CLASE_Ventilador.h"


LectorADC::LectorADC(byte pin, long msEntreLecturas, Ventilador* vent, Scheduler* planif)
    : Task(msEntreLecturas, TASK_FOREVER, planif, true)
    , pin(pin), vent(vent)
{}

bool LectorADC::Callback() {
    this -> vent -> setPWM(
        map(
            analogRead(this -> pin),
            0,
            1023,
            this -> vent -> getMinPWM(),
            this -> vent -> getMaxPWM()
        )
    );

    return true;
}
