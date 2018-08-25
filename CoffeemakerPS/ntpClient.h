#ifndef NTPCLIENT_H_
#define NTPCLIENT_H_

#include "Arduino.h"
#include <TimeLib.h>
#include <WiFi.h>;
#include <WiFiUdp.h>

// NTP Servers:
static const char ntpServerName[] = "de.pool.ntp.org";

class NtpClient {
  private:
    unsigned int localPort = 8888;  // local port to listen for UDP packets

  public:
    void setupNtp();
    void digitalClockDisplay();
    void printDigits(int digits);
};
#endif

