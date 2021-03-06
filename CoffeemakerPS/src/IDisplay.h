#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "Arduino.h"
#include "settings.h"

class IDisplay {
    public:
        // pure virtual (abstract) method definitions
        virtual void initDisplay() = 0;
        virtual void print_logo() = 0;
        virtual void message_print(String msg1, String msg2, int wait) = 0;
        virtual void message_print(String msg1, String msg2, String msg3, int wait) = 0;
        virtual void message_print(String msg1, String msg2, String msg3, String msg4, int wait) = 0;
        virtual void message_print_scroll(String msg) = 0;
        virtual void message_clear() = 0;
};

class DisplayFactory {
    public:
        static DisplayFactory* getInstance();
        IDisplay* createDisplay();

    private:
        DisplayFactory();    
        static DisplayFactory *instance;    
};
#endif

