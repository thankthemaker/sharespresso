#include "ICoffeeMaker.h";

#if defined(GIGAX8)
#include "juragigax8.h";
#elif defined(X7)
#include "jurax7.h";
#elif defined(S95)
#include "juras95.h";
#endif

#ifndef ESP32
  SoftwareSerial myCoffeemaker(JURA_RX_PIN,JURA_TX_PIN); // RX, TX
#else
  HardwareSerial myCoffeemaker(2);
#endif
int inservice=0;

ICoffeeMaker::ICoffeeMaker(IDisplay *oled, Buzzer *buzzer) {
  this->oled = oled;
  this->buzzer = buzzer;
}

void ICoffeeMaker::initCoffeemaker() {
#ifndef ESP32
  myCoffeemaker.begin(9600);         // start serial communication at 9600bps
  // SoftwareSerial only alows one device listening at a time
  myCoffeemaker.listen();    
#else
  // start serial communication at 9600bps
  myCoffeemaker.begin(9600, SERIAL_8N1, JURA_RX_PIN, JURA_TX_PIN, false);         
        
#endif
}

String ICoffeeMaker::fromCoffeemaker(){
  String inputString = "";
  byte d0, d1, d2, d3;
  char d4 = 255;
  while (myCoffeemaker.available()){    // if data is available to read
    d0 = myCoffeemaker.read();
    delay (1); 
    d1 = myCoffeemaker.read();
    delay (1); 
    d2 = myCoffeemaker.read();
    delay (1); 
    d3 = myCoffeemaker.read();
    delay (7);
    bitWrite(d4, 0, bitRead(d0,2));
    bitWrite(d4, 1, bitRead(d0,5));
    bitWrite(d4, 2, bitRead(d1,2));
    bitWrite(d4, 3, bitRead(d1,5));
    bitWrite(d4, 4, bitRead(d2,2));
    bitWrite(d4, 5, bitRead(d2,5));
    bitWrite(d4, 6, bitRead(d3,2));
    bitWrite(d4, 7, bitRead(d3,5));
    inputString += d4;
  }
  inputString.trim();
  if ( inputString != "") {
        return(inputString);
  } 
}

void ICoffeeMaker::toCoffeemaker(String outputString)
{
  for (byte a = 0; a < outputString.length(); a++){
    byte d0 = 255;
    byte d1 = 255;
    byte d2 = 255;
    byte d3 = 255;
    bitWrite(d0, 2, bitRead(outputString.charAt(a),0));
    bitWrite(d0, 5, bitRead(outputString.charAt(a),1));
    bitWrite(d1, 2, bitRead(outputString.charAt(a),2));  
    bitWrite(d1, 5, bitRead(outputString.charAt(a),3));
    bitWrite(d2, 2, bitRead(outputString.charAt(a),4));
    bitWrite(d2, 5, bitRead(outputString.charAt(a),5));
    bitWrite(d3, 2, bitRead(outputString.charAt(a),6));  
    bitWrite(d3, 5, bitRead(outputString.charAt(a),7)); 
    myCoffeemaker.write(d0); 
    delay(1);
    myCoffeemaker.write(d1); 
    delay(1);
    myCoffeemaker.write(d2); 
    delay(1);
    myCoffeemaker.write(d3); 
    delay(7);
  }
}

boolean ICoffeeMaker::servicetoggle(void){
    inservice=not(inservice);
    if ( inservice) {
      this->oled->message_print(F("Service Mode"),F("started"),0);
#if defined(BT)
      myBT.listen();
#endif      
      return this->inkasso_off(true);
    } else {
      this->oled->message_print(F("Service Mode"),F("exited"),2000);
#ifndef ESP32
      //SoftwareSerial only allows one device listening at a time
      myCoffeemaker.listen();
#endif
      return this->inkasso_on(true);
    }
}

boolean ICoffeeMaker::inkasso_on(boolean feedback){
  this->toCoffeemaker("?M3\r\n");  // activates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (this->fromCoffeemaker() == "?ok"){
    if(feedback) {
      this->buzzer->beep(1);
      this->oled->message_print(F("Inkasso mode"),F("activated!"),2000); 
    }
    return true; 
  } else {
    if(feedback) {
      this->buzzer->beep(2);
      this->oled->message_print(F("Coffeemaker"),F("not responding!"),2000); 
    } 
    return false;
  }  
}

boolean ICoffeeMaker::inkasso_off(boolean feedback){
  this->toCoffeemaker("?M1\r\n");  // deactivates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (this->fromCoffeemaker() == "?ok"){
    if(feedback) {
      this->buzzer->beep(1);
      this->oled->message_print(F("Inkasso mode"),F("deactivated!"),2000);  
    }
    return true;
  } else {
    if(feedback) {
      this->buzzer->beep(2);
      this->oled->message_print(F("Coffeemaker"),F("not responding!"),2000);  
    }
    return false;
  }
}

int ICoffeeMaker::readRegister(String reg){
  this->toCoffeemaker("RE:" + reg + "\r\n"); 
  delay (100);               // wait for answer from coffeemaker
  String value = this->fromCoffeemaker();
  value.remove(0,3);
  value.remove(4); 
  long val = strtol(value.c_str(), NULL, 16);

  return val;    
}

std::map <char, String> ICoffeeMaker::getProducts() {
  return products;
}

int ICoffeeMaker::getIndexForProduct(char productCode) {
  String codeToIndex = "ABCDEFGHJ";
  int index = codeToIndex.indexOf(productCode);
  return index >= 0 ? index : 0;
}


