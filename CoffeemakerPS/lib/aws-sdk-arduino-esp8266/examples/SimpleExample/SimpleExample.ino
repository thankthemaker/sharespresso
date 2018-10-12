#include <AmazonIOTClient.h>
#include "ESPAWSImplementations.h"

EspHttpClient httpClient;
EspDateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

const char *ssid="MySSID";
const char *password="MyPASS";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WAP
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("eu-west-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("foobar.iot.eu-west-1.amazonaws.com");
  iotClient.setAWSPath("/things/example-1/shadow");
  iotClient.setAWSKeyID("ID");
  iotClient.setAWSSecretKey("SECRET");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop(){

  const char* shadow = "{\"state\":{\"reported\": {\"foobar\": \"bar\"}}}";
  const char* result = iotClient.update_shadow(shadow, actionError);

  Serial.print(result);

  delay(60000);
}

