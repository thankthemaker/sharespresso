#ifndef BUZZER_H_
#define BUZZER_H_

#include "Arduino.h";
#include "settings.h";


#ifndef BUZPIN
 #define BUZPIN 0  // digital pin for buzzer
#endif

class Buzzer {
    public:
        Buzzer();
        void beep(byte number);
};
#endif

