#include "mbed.h"

class TMP36
{
public:
 TMP36(PinName pin);
 TMP36();
 float read();
private:
//class sets up the AnalogIn pin
 AnalogIn _pin;
};
//TMP36::TMP36(PinName pin) : _pin(pin) {} //This is an initializer list … more to come in class
// _pin(pin) means pass pin to the AnalogIn constructor
