#include "ESPAWSImplementations.h"
#include "DeviceIndependentInterfaces.h"

#include <stdio.h>
#include <string.h>

int delayTime = 500;
const char* fingerprint = "20 E4 92 1C D4 B6 39 57 8C EB 41 8B 23 15 9E A4 69 F0 8B F5";
char* updateCurTime(void);

EspHttpClient::EspHttpClient() {
}

const char*
EspHttpClient::send(const char* request, const char* serverUrl, int port)
{
    //port = 443;
#if !defined ARDUINO_ARCH_SAM && !defined ARDUINO_ARCH_SAMD
    WiFiClientSecure sclient;
#else
    WiFiSSLClient sclient;
#endif
    Serial.println(serverUrl);
    Serial.println(port);
    Serial.println(request);
    Serial.println("");
    Serial.println("");

    String response = "";
    
    if (sclient.connect(serverUrl, port)) {
#ifdef ESP8266
        if(sclient.verify(fingerprint,serverUrl)){
            Serial.println("Certificate Matches");
        } else {
            Serial.println("Certificate Does Not Match");
        }
#endif

        // Send the request
        sclient.print(request);
        // keep reading the response until it's finished
        while(sclient.connected()) {
            bool availableSeen = false;
            while(sclient.available()){
                availableSeen = true;
                char c = sclient.read();
                response.concat(c);
            }
            if(availableSeen)
                sclient.stop(); // disconnect any open connections
        }

    } else {
        Serial.println("Connection Unsuccessful");
        // connection was unsuccessful
        sclient.stop();
        return "can't setup SSL connection";
    }

    // convert the string into a char and return
    int len = response.length();
    char* response_char = new char[len + 1]();
    response.toCharArray(response_char, len + 1);
    return response_char;
}

bool EspHttpClient::usesCurl() {
    /* Does not use curl command. */
    return false;
}

EspDateTimeProvider::EspDateTimeProvider() {
}

const char* EspDateTimeProvider::getDateTime() {
    return updateCurTime();
}
bool EspDateTimeProvider::syncTakesArg(void) {
    return true;
}

void EspDateTimeProvider::sync(const char* dateTime) {
  // should have no need for an implementation
}

////////////////////////////////////
// convert month to digits
////////////////////////////////////
String getMonth(String sM) {
  if(sM=="Jan") return "01";
  if(sM=="Feb") return "02";
  if(sM=="Mar") return "03";
  if(sM=="Apr") return "04";
  if(sM=="May") return "05";
  if(sM=="Jun") return "06";
  if(sM=="Jul") return "07";
  if(sM=="Aug") return "08";
  if(sM=="Sep") return "09";
  if(sM=="Oct") return "10";
  if(sM=="Nov") return "11";
  if(sM=="Dec") return "12";
  return "01";
}

////////////////////////////////////
// Scrape UTC Time from server
////////////////////////////////////
char* updateCurTime(void) {
    static int timeout_busy=0;
    int ipos;
    timeout_busy=0; //reset

    const char* timeServer = "aws.amazon.com";

    // send a bad header on purpose, so we get a 400 with a DATE: timestamp
    const char* timeServerGet = "GET example.com/ HTTP/1.1";
    String utctime;
    String GmtDate;
    static char dateStamp[20];

    WiFiClient client;
    if (client.connect(timeServer, 80)) {
        //Send Request
        client.println(timeServerGet);
        client.println();
        while((!client.available())&&(timeout_busy++<5000)){
          // Wait until the client sends some data
          delay(1);
        }

        // kill client if timeout
        if(timeout_busy>=5000) {
            client.flush();
            client.stop();
            Serial.println("timeout receiving timeserver data\n");
            return dateStamp;
        }

        // read the http GET Response
        const int buflen = 1024;
        uint8_t buffer[buflen];
        client.read(buffer, buflen);
        String req2 = (char*)buffer;
        // Serial.println("");
        // Serial.println("");
        // Serial.print(req2);
        // Serial.println("");
        // Serial.println("");

        // close connection
        delay(1);
        client.flush();
        client.stop();

        ipos = req2.indexOf("Date:");
        if(ipos>0) {
          GmtDate = req2.substring(ipos,ipos+35);
          Serial.println(GmtDate);
          utctime = GmtDate.substring(18,22) + getMonth(GmtDate.substring(14,17)) + GmtDate.substring(11,13) + GmtDate.substring(23,25) + GmtDate.substring(26,28) + GmtDate.substring(29,31);
          Serial.println(utctime.substring(0,14));
          utctime.substring(0,14).toCharArray(dateStamp, 20);
        }
    }
    else {
      Serial.println("did not connect to timeserver\n");
    }
    timeout_busy=0;     // reset timeout
    return dateStamp;   // Return latest or last good dateStamp
}
