#include "ble.h";

BleConnection::BleConnection() : bleSerial(1) {}

void BleConnection::initBle() {
  bleSerial.begin(38400, SERIAL_8N1, BLE_RX_PIN, BLE_TX_PIN);
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

