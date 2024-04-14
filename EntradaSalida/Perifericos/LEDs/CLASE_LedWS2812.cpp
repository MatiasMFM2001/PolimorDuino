#include "CLASE_LedWS2812.h" 

LedWS2812::LedWS2812(ColorRGBW colorApagado, ColorRGBW colorEncendido, Adafruit_NeoPixel *tiraRGBW, size_t indiceTira, bool estadoInicial)
    : LedRGBW(colorApagado, colorEncendido, estadoInicial)
    , tiraRGBW(tiraRGBW), indiceTira(indiceTira)
{}

void LedWS2812::mostrar(void) {
    ColorRGBW color = this -> getColorActual();
    
    this -> tiraRGBW -> setPixelColor(this -> indiceTira, color.rojo, color.verde, color.azul, color.blanco);
    this -> tiraRGBW -> show();
}

size_t LedWS2812::printTo(Print& impresora) const {
    return OBJETO_A_JSON(impresora, "LedWS2812", indiceTira) + SUPERCLASES_A_JSON(impresora, LedRGBW);
}
