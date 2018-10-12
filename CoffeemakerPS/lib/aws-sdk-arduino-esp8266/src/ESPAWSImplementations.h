#ifndef AWSESPIMPLEMENTATIONS_H_
#define AWSESPIMPLEMENTATIONS_H_

#include "DeviceIndependentInterfaces.h"

#if !defined  ARDUINO_ARCH_SAM && !defined ARDUINO_ARCH_SAMD
#include <WiFiClientSecure.h>
#else
#include <WiFiSSLClient.h>
#endif

#if defined  ARDUINO_ARCH_SAM || defined ARDUINO_ARCH_SAMD
#ifdef SERIALUSB
#define Serial SerialUSB
#endif
#endif

/* HttpClient implementation to be used on the Esp Core device. */
class EspHttpClient: public IHttpClient {
#if !defined ARDUINO_ARCH_SAM && !defined ARDUINO_ARCH_SAMD
    WiFiClientSecure sclient;
#else
    WiFiSSLClient sclient;
#endif
public:
    EspHttpClient();
    /* Send http request and return the response. */
    const char* send(const char *request, const char* serverUrl, int port);
    /* Returns false. Client uses raw http/https. */
    bool usesCurl(void);
};

class EspDateTimeProvider: public IDateTimeProvider {
    /* The time as a cstring in yyyyMMddHHmmss format. Is written to within and
     * returned by getDateTime(). */
    WiFiClient client;
    //char dateTime[15];
public:
    char dateTime[15];
    EspDateTimeProvider();
    /* Retrieve the current GMT date and time in yyyyMMddHHmmss format. */
    const char* getDateTime(void);
    /* Returns false because Esp has it's own mechanism for syncing that does
     * not require an argument. */
    bool syncTakesArg(void);
    /* Synchronizes Esp's date and time with Esp's servers. The dateTime
     * argument is ignored. */
    void sync(const char* dateTime);
};

#endif /* AWSESPIMPLEMENTATIONS_H_ */
