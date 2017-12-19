#include "Arduino.h";

#define BUZZER_H_
#define BUZPIN 0  // digital pin for buzzer

class Buzzer {
    public:
        Buzzer() {}
        void beep(byte number);
};
