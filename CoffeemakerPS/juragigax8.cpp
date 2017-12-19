#include "juragigax8.h";

SoftwareSerial myCoffeemaker(15,16); // RX, TX
int inservice=0;

JuraGigaX8::JuraGigaX8(OledDisplay& oled, Buzzer& buzzer) {
  this->oled = &oled;
  this->buzzer = &buzzer;
};

void JuraGigaX8::initCoffeemaker() {
    myCoffeemaker.begin(9600);         // start serial communication at 9600bps
}

String JuraGigaX8::fromCoffeemaker(){
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

void JuraGigaX8::toCoffeemaker(String outputString)
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

void JuraGigaX8::servicetoggle(void){
    inservice=not(inservice);
    if ( inservice) {
      this->oled->message_print(F("Service Mode"),F("started"),0);
      this->inkasso_off();
#if defined(BT)
      myBT.listen();
#endif
    } else {
      this->oled->message_print(F("Service Mode"),F("exited"),2000);
//      myCoffeemaker.listen();
      this->inkasso_on();
    }
}

void JuraGigaX8::inkasso_on(void){
  this->toCoffeemaker("?M3\r\n");  // activates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (this->fromCoffeemaker() == "?ok"){
    this->buzzer->beep(1);
    this->oled->message_print(F("Inkasso mode"),F("activated!"),2000);  
  } else {
    this->buzzer->beep(2);
    this->oled->message_print(F("Coffeemaker"),F("not responding!"),2000);  
  }  
}

void JuraGigaX8::inkasso_off(void){
  this->toCoffeemaker("?M1\r\n");  // deactivates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (this->fromCoffeemaker() == "?ok"){
    this->buzzer->beep(1);
    this->oled->message_print(F("Inkasso mode"),F("deactivated!"),2000);  
  } else {
    this->buzzer->beep(2);
    this->oled->message_print(F("Coffeemaker"),F("not responding!"),2000);  
  }
}
