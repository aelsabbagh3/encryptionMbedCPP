#include "TMP36.h"



float TMP36::read()
{
 return ((_pin.read()*3.3)-0.500)*100.0;
}


TMP36::TMP36(PinName pin) : _pin(pin) {}

