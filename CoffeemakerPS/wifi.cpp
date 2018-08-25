#include "wifi.h"

Wifi::Wifi() : espClient() {};

void Wifi::setup_wifi() {

  delay(10);

#ifdef MULTI_WIFI
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  wifiMulti.addAP(WIFI_SSID2, WIFI_PASSWORD2);
  wifiMulti.addAP(WIFI_SSID3, WIFI_PASSWORD3);
#endif

#ifdef MULTI_WIFI
  while(wifiMulti.run() != WL_CONNECTED) {
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
#endif
    Serial.print(F("."));
    delay(500);
  }

  Serial.println(F(""));
  Serial.println(F("WiFi connected to"));
  Serial.println(WiFi.SSID());
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.println(F("MAC address: "));
  Serial.println(WiFi.macAddress());
}

void Wifi::loop() {
#ifdef MULTI_WIFI
  if (wifiMulti.run() != WL_CONNECTED) { //if we lost connection, retry
#else
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif
    Serial.println(F("WiFi lost, attemping reconnect..."));
    delay(500);
  }
}

