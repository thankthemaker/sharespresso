#include "chucknorris.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Number of facts to be cached
const int factscount = 5;

// Cache-variable
String facts[factscount];

// Counter for fact to be displayed
int currentFact = -1;

Chucknorris :: Chucknorris() {}

void prefetchFacts(int amount) {
  Serial.println("Prefetch facts");
  HTTPClient http;
  http.setTimeout(5000);
  http.begin("http://api.icndb.com/jokes/random/" + String(amount) + "?escape=javascript&limitTo=[nerdy]");
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(payload);
        JsonArray& factsjson = (json["value"]);
        for (int i = 0; i < amount; i++) {
          String fact = factsjson[i]["joke"].as<String>();
          facts[i] = fact;
        }
      } else {
        Serial.printf("[HTTP] GET... failed, code: %s", httpCode);
      }
    
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void incrementCurrentFact() {
    currentFact++;
    // prefetch facts from api if facts not filled 
    // or all facts has been already displayed
    if (facts[0] == "" || factscount < currentFact + 1) {
      prefetchFacts(factscount);
      currentFact = 0;
    }
  }

String Chucknorris :: getNextChucknorrisFact() {
  incrementCurrentFact();
  String fact = facts[currentFact];
  return fact;
}

