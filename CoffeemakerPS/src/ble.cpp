#include "ble.h";

#ifdef ESP32
BleConnection::BleConnection() : bleSerial(1) {}
#endif

void BleConnection::initBle() {
#ifdef ESP32
  bleSerial.begin(38400, SERIAL_8N1, BLE_RX_PIN, BLE_TX_PIN);
#endif
}

String BleConnection::readCommand() {
  String BTstring = "";
  while( bleSerial.available()) {
    BTstring +=String(char(bleSerial.read()));
    delay(7);
  }
  return BTstring;
}


#ifndef ESP32
SoftwareSerial BleConnection::getSerial() {
    return bleSerial;
}
#else
 HardwareSerial BleConnection::getSerial() {
    return bleSerial;
}
#endif    

