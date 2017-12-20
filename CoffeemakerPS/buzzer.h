#include "Arduino.h";
#ifndef SETTINGS_H_
 #include "settings.h";
#endif

#define BUZZER_H_

#ifndef BUZPIN
 #define BUZPIN 0  // digital pin for buzzer
#endif

class Buzzer {
    public:
        Buzzer() {}
        void beep(byte number);
};
