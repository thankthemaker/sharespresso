/* 
 Sharespresso by Thank-The-Maker.org
 
 is an Arduino-based RFID payment system for coffeemakers with toptronic logic unit, as Jura 
 Impressa S95 and others without modifying the coffeemaker itself. 

 Based on Oliver Krohns famous Coffeemaker-Payment-System 
 at https://github.com/oliverk71/Coffeemaker-Payment-System

 and 

 Sharespresso by c't/Peter Siering
 at https://www.heise.de/ct/artikel/Sharespresso-NFC-Bezahlsystem-fuer-Kaffeevollautomaten-3058350.html
 
 Hardware used: 
  - SparkFun ESP8266 Thing - Dev Board
  - AZDelivery 3er Set 128 x 64 Pixel 0,96 Zoll OLED Display
  - pn532/mfrc522 rfid card reader (13.56MHz), 
  - HC-05 bluetooth, male/female jumper wires (optional: ethernet shield, buzzer, button)
 
 The code is provided 'as is', without any guarantuee. Use at your own risk! 
*/

// needed for conditional includes to work, don't ask why ;-)
char trivialfix;

#include "settings.h"

// options to include into project
#define BUZPIN 0  // digital pin for buzzer
#define BT 1 // bluetooth module
#define SERLOG 1 // logging to serial port
#define DEBUG 1 // some more logging
// set your application specific settings here
#define MASTERCARD 3496110302 // card uid to enter/exit service mode
// coffemaker model
//#define X7 1 // x7/saphira
#define S95 1
#define PN532_SS   (2)
#define PN532_SCK  (14)
#define PN532_MISO (12)
#define PN532_MOSI (13)


#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "SSD1306Brzo.h" //OLED I2C
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_PN532.h> // NFC Card Reader
#include <PubSubClient.h>

// hardware specific settings
SSD1306Brzo display(0x3c, 4, 5);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
SoftwareSerial myCoffeemaker(15,16); // RX, TX
#if defined(BT)
SoftwareSerial myBT(7,8);
#endif

Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// product codes send by coffeemakers "?PA<x>\r\n", just <x>
#if defined(S95)
char products[] = "EFABJIG";
#endif
#if defined(X7)
char products[] = "ABCHDEKJFG";
#endif

// general variables (used in loop)
boolean buttonPress = false;
const int n = 40; // number of cards, max is (1024-11*2)/6=167 on Arduino Uno
String BTstring=""; // contains what is received via bluetooth (from app or other bt client)
unsigned long actTime; // timer for RFID etc
unsigned long buttonTime; // timer for button press 
boolean override = false;  // to override payment system by the voice-control/button-press app
unsigned long RFIDcard = 0;
int inservice=0;
int price=0;
String last_product="";

void setup()
{
#if defined(SERLOG) || defined(DEBUG)
  Serial.begin(9600);
#endif
#if defined(DEBUG)
//  EEPROM.setMaxAllowedWrites(100);
//  EEPROM.setMemPool(0, EEPROMSizeUno);
  Serial.println(sizeof(products));
#endif
  serlog("Initializing OLED");
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.clear();
  display.drawString(0, 26, "Welcome to Coffeemaker");
  display.display(); 
  
  message_print(F("sharespresso"), F("starting up"), 0);
  myCoffeemaker.begin(9600);         // start serial communication at 9600bps
#if defined(BT)
  serlog(F("Initializing bluetooth module"));
  myBT.begin(38400);
#endif
  // initialized rfid lib
#if defined(DEBUG)
  serlog(F("Initializing rfid reader"));
#endif
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
#if defined(DEBUG)
    serlog(F("Didn't find PN53x board"));
#endif
  }
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
  nfc.setPassiveActivationRetries(0xfe);
  // configure service button
  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);
  message_print(F("Ready to brew"), F(""), 2000);
  // activate coffemaker connection and inkasso mode
//  myCoffeemaker.listen();
  inkasso_on();
}

void loop()
{  
    if (!mqttClient.connected()) {
      mqttReconnect();
    }
    mqttClient.loop();
 
  // Check if there is a bluetooth connection and command
  BTstring = "";
  // handle serial and bluetooth input
#if defined(BT)
    while( myBT.available()) {
      BTstring +=String(char(myBT.read()));
      delay(7);
    }
#endif
  while( Serial.available() ){  
    BTstring += String(char(Serial.read()));
    delay(7);  
  }
  BTstring.trim();
  
  if (BTstring.length() > 0){
    executeCommand(BTstring);   
  }          

  // Get key pressed on coffeemaker
  String message = fromCoffeemaker();   // gets answers from coffeemaker 
  if (message.length() > 0){
    serlog( message);
    if (message.charAt(0) == '?' && message.charAt(1) == 'P'){     // message starts with '?P' ?
      buttonPress = true;
      buttonTime = millis();
      int product = 255;
      for (int i = 0; i < sizeof(products); i++) {
        if (message.charAt(3) == products[i]) {
          product = i;
          break;
        }
      }
      if ( product != 255) {
        String productname;
          switch (product) {
#if defined(S95)
            case 0: productname = F("Small cup"); break;
            case 1: productname = F("2 small cups"); break;
            case 2: productname = F("Large cup"); break;
            case 3: productname = F("2 large cups"); break;
            case 4: productname = F("Steam 2"); break;
            case 5: productname = F("Steam 1"); break;
            case 6: productname = F("Extra large cup"); break;
#endif
#if defined(X7)
            case 0: productname = F("Cappuccino"); break;
            case 1: productname = F("Espresso"); break;
            case 2: productname = F("Espresso dopio"); break;
            case 3: productname = F("Milchkaffee"); break;
            case 4: productname = F("Kaffee"); break;
            case 5: productname = F("Kaffee gross"); break;
            case 6: productname = F("Dampf links"); break;
            case 7: productname = F("Dampf rechts"); break;
            case 8: productname = F("Portion Milch"); break;
            case 9: productname = F("Caffee Latte"); break;
#endif
          }
          price=1;
//        price = EEPROM.readInt(product* 2+ 1000);
        last_product= String(message.charAt( 3))+ "/"+ String(product)+ " ";
        message_print(productname, printCredit(price), 0);
      } 
      else {
        message_print(F("Error unknown"), F("product"), 2000);
        buttonPress = false;
      }
      // boss mode, he does not pay
      if (override == true){
        price = 0;
      }
    }
  }
  // User has five seconds to pay
  if (buttonPress == true) {
    if (millis()-buttonTime > 5000){  
      buttonPress = false;
      price = 0;
      last_product = "";
      message_clear();
    }
  }
  if (buttonPress == true && override == true){
    toCoffeemaker("?ok\r\n");
    buttonPress == false;
    override == false;
  }
  // RFID Identification      
  RFIDcard = 0;  
  actTime = millis(); 
  do {
    RFIDcard = nfcidread();
    if (RFIDcard == MASTERCARD) {
      servicetoggle();
      delay(60);
      RFIDcard= 0;
    }
    if (RFIDcard != 0) {
      display.clear();
      break; 
    }           
  } 
  while ( (millis()-actTime) < 60 );  

  if (RFIDcard != 0){
    int k = n;
    for(int i=0;i<n;i++){         
//      if (((RFIDcard) == (EEPROM.readLong(i*6))) && (RFIDcard != 0 )){
      if(true) {
        k = i;
        int credit=1000;
 //       int credit= EEPROM.readInt(k*6+4);
        if(buttonPress == true){                 // button pressed on coffeemaker?
           if ((credit - price) > 0) {
            message_print(print10digits(RFIDcard), printCredit(credit), 0);
//            EEPROM.writeInt(k*6+4, ( credit- price));
            toCoffeemaker("?ok\r\n");            // prepare coffee
            buttonPress= false;
            price= 0;
            last_product= "";
          } 
          else {
            beep(2);
            message_print(printCredit(credit), F("Not enough"), 2000); 
          }
        } 
        else {                                // if no button was pressed on coffeemaker / check credit
          message_print(printCredit(credit), F("Remaining credit"), 2000);
        }
        i = n;      // leave loop (after card has been identified)
      }      
    }
    if (k == n){ 
      k=0; 
      beep(2);
      message_print(String(print10digits(RFIDcard)),F("card unknown!"),2000);
    }           
  }
}

String fromCoffeemaker(){
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

void toCoffeemaker(String outputString)
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

String printCredit(int credit){
  int euro = ((credit)/100);  //  int euro = ((credit*10)/100);
  int cent = ((credit)%100);  //  int cent = ((credit*10)%100); 
  String(output);
  output = String(euro);
  output += ',';
  output += String(cent);
  if (cent < 10){
    output += '0';
  }
  output += F(" EUR");  
  return output;
}

String print10digits(unsigned long number) {
  String(tempString) = String(number);
  String(newString) = "";
  int i = 10-tempString.length();
  for (int a = 0; a < (10-tempString.length()); a++){
    newString += "0";
  }
  newString += number;
  return newString;
}

String print2digits(int number) {
  String partString;
  if (number >= 0 && number < 10) {
    partString = "0";
    partString += number;
  } 
  else partString = String(number);
  return partString;
}

void serlog(String msg) {
#if defined(SERLOG)
  Serial.println(msg);
#endif
}

void message_print(String msg1, String msg2, int wait) {
#if defined(SERLOG)
  if (msg1 != "") { Serial.print(msg1 + " "); }
  if (msg2 != "") { Serial.print(msg2); }
  if ((msg1 != "") || (msg2 != "")) { Serial.println(""); }
#endif
  display.clear();
  if (msg1 != "") {
    display.drawString(0, 10, msg1);
  }
  if (msg2 != "") {
    display.drawString(0, 30, msg2);
  }
  display.display(); 
  if (wait > 0) { 
    delay(wait);
      display.clear();
  }
}

void message_clear() {
  display.clear();
}

void beep(byte number){
  int duration = 200;
  switch (number) {
  case 1: // positive feedback
    tone(BUZPIN,1500,duration);
    delay(duration);
    break;
  case 2: // negative feedback
    tone(BUZPIN,500,duration);
    delay(duration);
    break;     
  case 3:  // action stopped (e.g. registering) double beep
    tone(BUZPIN,1000,duration);
    delay(duration);
    tone(BUZPIN,1500,duration);
    delay(duration);    
    break; 
  case 4:  // alarm (for whatever)
    for (int a = 0; a < 3; a++){
      for (int i = 2300; i > 600; i-=50){
        tone(BUZPIN,i,20);
        delay(18);
      }     
      for (int i = 600; i < 2300; i+=50){
        tone(BUZPIN,i,20);
        delay(18);
      }
    }  
  }
}

void registernewcards() {
  do {
    RFIDcard = 0;
    do {
      RFIDcard = nfcidread();
      if (RFIDcard != 0) {
        message_clear();
        break;
      }
    } while ( (millis()-actTime) < 60 );  
    int k = 255;
    if (RFIDcard != 0) {
      if ( RFIDcard == MASTERCARD) {
        break;
      }
      for(int i=0;i<n;i++){
//        if (RFIDcard == EEPROM.readLong(i*6)) {
          message_print(print10digits(RFIDcard), F("already exists"), 0);
          beep(2);
          k=254;         
          break;
//        }
//        if ((EEPROM.readLong(i*6) == 0) && (k == 255)) { // find first empty slot
          k=i;
//        }
      }
      if ( k == 255) {
        message_print(F("no slot left"),F(""),0);         
        break;
      }
      if ( k != 254) {
        message_print( print10digits(RFIDcard), F("registered"),0);
        int credit=1000;
//        int credit= EEPROM.readInt(1000+2*10);
//        EEPROM.updateLong(k*6, RFIDcard);
//        EEPROM.updateInt(k*6+4, credit);
        beep(1);
      }
      actTime = millis();
    }
  } while ( (millis()-actTime) < 10000 );
  message_print(F("Registering"),F("ended"),2000);
  beep(3);  
}

unsigned long nfcidread(void) {
  unsigned long id=0;
  uint8_t success;
  uint8_t uid[] = { 0,0,0,0,0,0,0,0 };
  uint8_t uidLength;
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);  
  if (success) {
    // ugly hack: fine for mifare classic (4 byte)
    // also fine for our ultras (last 4 bytes ever the same)
    // nfc.PrintHex(uid, uidLength);
    id = (unsigned long)uid[0]<<24;
    id += (unsigned long)uid[1]<<16;
    id += (unsigned long)uid[2]<<8;
    id += (unsigned long)uid[3];
  }
  return id;
}

void servicetoggle(void){
    inservice=not(inservice);
    if ( inservice) {
      message_print(F("Service Mode"),F("started"),0);
      inkasso_off();
#if defined(BT)
      myBT.listen();
#endif
    } else {
      message_print(F("Service Mode"),F("exited"),2000);
//      myCoffeemaker.listen();
      inkasso_on();
    }
}

void inkasso_on(void){
  toCoffeemaker("?M3\r\n");  // activates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (fromCoffeemaker() == "?ok"){
    beep(1);
    message_print(F("Inkasso mode"),F("activated!"),2000);  
  } else {
    beep(2);
    message_print(F("Coffeemaker"),F("not responding!"),2000);  
  }  
}

void inkasso_off(void){
  toCoffeemaker("?M1\r\n");  // deactivates incasso mode (= no coffee w/o "ok" from the payment system! May be inactivated by sending "?M3" without quotation marks)
  delay (100);               // wait for answer from coffeemaker
  if (fromCoffeemaker() == "?ok"){
    beep(1);
    message_print(F("Inkasso mode"),F("deactivated!"),2000);  
  } else {
    beep(2);
    message_print(F("Coffeemaker"),F("not responding!"),2000);  
  }
}

void mqttReconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("Jura Giga X8", mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish(mqtt_topic_out, "Jura Giga X8 is ready now...");
      // ... and resubscribe
      mqttClient.subscribe(mqtt_topic_in);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String command  = "";
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
  Serial.print(command);
  executeCommand(command);
  Serial.println();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void executeCommand(String command) {
    // BT: Start registering new cards until 10 s no valid, unregistered card
#if defined(DEBUG)
    serlog(command);
#endif
    if( command == "RRR" ){          
      actTime = millis();
      beep(1);
      message_print(F("Registering"),F("new cards"),0);
      registernewcards();
      message_clear();
    }
    // BT: Send RFID card numbers to app    
    if(command == "LLL"){  // 'L' for 'list' sends RFID card numbers to app   
      for(int i=0;i<n;i++){
#if defined(BT)
        unsigned long card=12345678;
//        unsigned long card=EEPROM.readLong(i*6);
        myBT.print(print10digits(card)); 
        if (i < (n-1)) myBT.write(',');  // write comma after card number if not last
#endif
      }
    }
    // BT: Delete a card and referring credit   
    if(command.startsWith("DDD") == true){
      command.remove(0,3); // removes "DDD" and leaves the index
      int i = command.toInt();
      i--; // list picker index (app) starts at 1, while RFIDcards array starts at 0
//      unsigned long card= EEPROM.readLong(i*6);
      unsigned long card= 12345678;
      int credit= 1000;      
//      int credit= EEPROM.readInt(i*6+4);      
      message_print(print10digits(card), F("deleting"), 2000);    
//      EEPROM.updateLong(i*6, 0);
//      EEPROM.updateInt(i*6+2, 0);
      beep(1);
    }    
    // BT: Charge a card    
    if((command.startsWith("CCC") == true) ){
      char a1 = command.charAt(3);  // 3 and 4 => card list picker index (from app)
      char a2 = command.charAt(4);
      char a3 = command.charAt(5);  // 5 and 6 => value to charge
      char a4 = command.charAt(6);    
      command = String(a1)+String(a2); 
      int i = command.toInt();    // index of card
      command = String(a3)+String(a4);
      int j = command.toInt();   // value to charge
      j *= 100;
      i--; // list picker index (app) starts at 1, while RFIDcards array starts at 0  
      int credit=1000;
//      int credit= EEPROM.readInt(i*6+4);
      credit+= j;
//      EEPROM.writeInt(i*6+4, credit);
      beep(1);
//      unsigned long card=EEPROM.readLong(i*6);
      unsigned long card=12345678;
      message_print(print10digits(card),"+"+printCredit(j),2000);    
    } 
    // BT: Receives (updated) price list from app.  
    if(command.startsWith("CHA") == true){
      int k = 3;
      for (int i = 0; i < 11;i++){  
        String tempString = "";
        do {
          tempString += command.charAt(k);
          k++;
        } 
        while (command.charAt(k) != ','); 
        int j = tempString.toInt();
        Serial.println(i*2+1000);
//        EEPROM.updateInt(i*2+1000, j);
        k++;
      }
      beep(1);
      message_print(F("Pricelist"), F("updated!"), 2000);
    }
    // BT: Sends price list to app. Product 1 to 10 (0-9), prices divided by commas plus standard value for new cards
    if(command.startsWith("REA") == true){
      // delay(100); // testweise      
      for (int i = 0; i < 11; i++) {
#if defined(BT)
        price=1;
//        price= EEPROM.readInt(1000+i*2);
        myBT.print(int(price/100));
        myBT.print('.');
        if ((price%100) < 10){
          myBT.print('0');
        }
        myBT.print(price%100);
        if (i < 10) myBT.write(',');
#endif
      }
    } 

    if(command == "?M3"){
      inkasso_on();
    }
    if(command == "?M1"){
      inkasso_off();  
    }
    if(command == "FA:04"){        // small cup ordered via app
      toCoffeemaker("FA:04\r\n"); 
      override = true;
    }
    if(command == "FA:06"){        // large cup ordered via app
      toCoffeemaker("FA:06\r\n");  
      override = true;
    }
    if(command == "FA:0C"){        // extra large cup ordered via app
      toCoffeemaker("FA:0C\r\n");  
      override = true;
    } 
 }
