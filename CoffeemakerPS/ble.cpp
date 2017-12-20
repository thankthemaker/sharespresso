#include "ble.h";

BleConnection::BleConnection() : myBT(BLE_RX_PIN, BLE_TX_PIN) {}

void BleConnection::initBle() {
  myBT.begin(38400);
}

String BleConnection::readCommand() {
  String BTstring = "";
  while( myBT.available()) {
    BTstring +=String(char(myBT.read()));
    delay(7);
  }
  return BTstring;
}

SoftwareSerial BleConnection::getSerial() {
    return myBT;
}
