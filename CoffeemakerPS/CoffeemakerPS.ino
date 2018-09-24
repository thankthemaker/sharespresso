
/* 
 IoT-Sharespresso by Thank-The-Maker.org
 
 is an Arduino-based RFID payment system for coffeemakers with toptronic logic unit, as Jura 
 Impressa S95 and others without modifying the coffeemaker itself. 

 Based on Oliver Krohns famous Coffeemaker-Payment-System 
 at https://github.com/oliverk71/Coffeemaker-Payment-System

 and 

 Sharespresso by c't/Peter Siering
 at https://www.heise.de/ct/artikel/Sharespresso-NFC-Bezahlsystem-fuer-Kaffeevollautomaten-3058350.html
 
 Hardware used: 
  - Sparkfun ESP32 Thing
  - Waveshare 1.5inch OLED Display Module 128x128 Pixels
  - pn532/mfrc522 rfid card reader (13.56MHz), 
  - HC-05 bluetooth, male/female jumper wires (not used any longer)
  - piezo buzzer 

Read more about the project at http://www.thank-the-maker.org 

 The code is provided 'as is', without any guarantuee. Use at your own risk! 
*/

// needed for conditional includes to work, don't ask why ;-)
char trivialfix;

#include <SPI.h>
#include <Wire.h>
#include <map>
#include "logging.h"
#include "settings.h"
#include "eepromconfig.h"
#include "wifi.h"
#include "NtpClient.h"
#include "IDisplay.h"
#include "INfcReader.h"
#include "ICoffeeMaker.h"
#include "IMessageBroker.h"
//#include "ble.h"
#include "otaupdate.h"
#include "juragigax8.h"
//#include "journal.h"
#include "chucknorris.h"

#include <MQTTClient.h>
std::map <char, String> products;


// general variables (used in loop)
boolean buttonPress = false;
boolean tempInkassoOff = false;

boolean registeringStarted = false;
boolean waitForAnswer = false;


String BTstring=""; // contains what is received via bluetooth (from app or other bt client)
unsigned long actTime; // timer for RFID etc
unsigned long buttonTime; // timer for button press 
unsigned long tempInkassoOffTime; // timer for temporary inkasso mode press 
unsigned long lastAlive; // time of the last Alive signal send
unsigned long aliveCounter = 0;

boolean override = false;  // to override payment system by the voice-control/button-press app
unsigned long RFIDcard = 0;
int price=0;
int coffeecounter = 0;
String productname="undefined";
pricelist_t pricelist;
cardlist_t cardlist;

FP<void,String>fp;
//Journal journal;
Wifi wifi;
Buzzer *buzzer = new Buzzer();
IMessageBroker *messageBroker = MessageBrokerFactory::getInstance()->createMessageBroker();
IDisplay *oled = DisplayFactory::getInstance()->createDisplay();
INfcReader *nfcReader = NfcReaderFactory::getInstance()->createNfcReader(oled, buzzer);
//ICoffeeMaker *coffeemaker =  CoffeeMakerFactory::getInstance()->createCoffeeMaker(oled, buzzer);
ICoffeeMaker *coffeemaker = new JuraGigaX8(oled, buzzer);
Chucknorris chucknorris;

NtpClient ntpClient;
//BleConnection bleConnection;
CoffeeLogger logger;
EEPROMConfig eepromConfig;
OTAUpdate update(oled);

void setup() {
#if defined(SERLOG) || defined(DEBUG)
  Serial.begin(9600);
#endif

  products['A'] = "Americano";
  products['B'] = "Kaffee groß";
  products['C'] = "Espresso";
  products['D'] = "Heißwasser";
  products['E'] = "Cappuccino groß";
  products['F'] = "Kaffee";
  products['G'] = "Milchkaffee";
  products['H'] = "Latte Machiatto";
  
  products['J'] = "Sonstiges";

  SPI.begin();      // Init SPI bus, needed by RC522-Reader

  //journal.initJournal();
  logger.log(LOG_DEBUG, "number of products: " + String(coffeemaker->getProducts().size()));
  logger.log(LOG_INFO, F("initializing Display"));
  oled->initDisplay();
  
  oled->message_print(F("sharespresso"), F("starting up"), 1500);
//  oled->print_logo();
  coffeemaker->initCoffeemaker(); // start serial communication at 9600bps

//  logger.log(LOG_INFO, "initializing bluetooth module");
//  bleConnection.initBle();

  // initialized rfid lib
  logger.log(LOG_INFO, F("initializing rfid reader"));
  nfcReader->initNfcReader();

  logger.log(LOG_INFO, F("reading pricelist and cards from EEPROM"));
  pricelist = eepromConfig.readPricelist();
  cardlist = eepromConfig.readCards();

  dumpPricelistAndCards(pricelist, cardlist);

  oled->message_print(F("connecting"), F("WIFI"), 0);
  wifi.setup_wifi();
  oled->message_print(F("WLAN-IP:"), WiFi.localIP().toString(), F("SSID:"), WiFi.SSID(), 0);

  fp.attach(&executeCommand);
  messageBroker->init(fp);
  ntpClient.setupNtp();
  
  // activate coffemaker connection and inkasso mode
  int retries = 5;
  while(!coffeemaker->inkasso_on(true) && retries > 0) {
    logger.log(LOG_INFO, "retrying in 5 seconds, retries left: " + String(retries));
    retries--;
    delay(5000);
  }
  if(retries == 0) {
    logger.log(LOG_ERR, F("unable to connect to coffeemaker"));
    oled->message_print(F("no connection"), F("to coffeemaker"), 0);
    buzzer->beep(4);
  } else {
      oled->message_print(F("Ready to brew"), F(""), 2000);
  }
}

void loop() {  
    wifi.loop();
    messageBroker->loop();

    if(millis() - lastAlive > 15000) {
      lastAlive = millis();
      ++aliveCounter;
      messageBroker->publish("coffeemaker is alive, count " + String(aliveCounter) + ", free Heap: " + ESP.getFreeHeap());
    }
 
  // Check if there is a bluetooth connection and command
  // handle serial and bluetooth input
//  BTstring = bleConnection.readCommand();

//  while( Serial.available() ){  
//    BTstring += String(char(Serial.read()));
//    delay(7);  
//  }
//  BTstring.trim();
  
//  if (BTstring.length() > 0){
//    executeCommand(BTstring);   
//  }          

  // Get key pressed on coffeemaker
  String message = "";
  // Only read answer when not already listening or temporary deactivated inkasso mode 
  if(!waitForAnswer && !tempInkassoOff) {
    message = coffeemaker->fromCoffeemaker();   // gets answers from coffeemaker 
  }
  if (message.length() > 0 && message != ""){
    logger.log("msg=" + message);
    if (message.charAt(0) == '?' && message.charAt(1) == 'P'){     // message starts with '?P' ?
      buttonPress = true;
      buttonTime = millis();

      //std::map<char,String>::iterator it = coffeemaker->getProducts().find(message.charAt(3));
      std::map<char,String>::iterator it = products.find(message.charAt(3));
      //if(it == coffeemaker->getProducts().end()) {
      if(it == products.end()) {
        // Key not found
        logger.log("unknown product=" + String(message.charAt(3)));
        oled->message_print(F("Error unknown"), F("product"), 2000);
        buttonPress = false;   
      } else {
        // Key found -- the corresponding item is in:
        productname = it->second;
      }
      price = pricelist.prices[coffeemaker->getIndexForProduct(message.charAt(3))];
      oled->message_print(logger.printCredit(price), productname, 0);
      // boss mode, he does not pay
      if (override == true){
        price = 0;
      }
    }
  }
  // User has five seconds to pay
  if (buttonPress == true) {
    if (millis()-buttonTime > 5000){  
      buzzer->beep(2);
      buttonPress = false;
      price = 0;
      oled->message_clear();
    }
  }
  if (buttonPress == true && override == true){
    coffeemaker->toCoffeemaker("?ok\r\n");
    buttonPress == false;
    override == false;
  }

  if(tempInkassoOff == true) {
     // activate temporary deactivated inkassomode if coffee is ready or after 45 seconds
     int tmpCounter = coffeemaker->readRegister("0004");
     Serial.printf_P(PSTR("tempcounter: %d, expected %d\n"), tmpCounter, coffeecounter+1);
     delay(200);
     if (coffeecounter+1 == tmpCounter || millis()-tempInkassoOffTime > 45000){  
      tempInkassoOff = false;
      waitForAnswer = true;
      for(int i=1; i<=10 && !coffeemaker->inkasso_on(false); i++) {
        delay(20);
        if(i==10) {
          logger.log(LOG_DEBUG, F("Failed to activate inkasso mode"));
        }
      }
      waitForAnswer = false;
      oled->message_print(F("Ready to brew"), F(""), 2000); 
    }
  }
  
  if(!registeringStarted) {
  // RFID Identification      
  RFIDcard = 0;  
  actTime = millis(); 
  do {
    RFIDcard = nfcReader->nfcidread();
    if (RFIDcard == MASTERCARD) {
      coffeemaker->servicetoggle();
      delay(60);
      RFIDcard= 0;
    }
    if (RFIDcard != 0) {
      oled->message_clear();
      break; 
    }           
  } 
  while ( (millis()-actTime) < 60 );  

  if (RFIDcard != 0){
    int k = MAX_CARDS;
    for(int i=0;i<MAX_CARDS;i++){         
      if (((RFIDcard) == (cardlist.cards[i].card)) && (RFIDcard != 0 )){
        k = i;
        int credit = eepromConfig.readCredit(k*6+4);
        if(buttonPress == true) { // button pressed on coffeemaker?
           if ((credit - price) > 0) {
            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
            delay(20);
            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
            delay(20);
            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
            delay(20);
            oled->message_print(logger.print10digits(RFIDcard), logger.printCredit(credit), 0);
            eepromConfig.updateCredit(k*6+4, ( credit- price));
            messageBroker->sendmessage (logger.print10digits(RFIDcard), productname, (float)price / 100.0);   
//            journal.writeJournal(String(now()), logger.print10digits(RFIDcard), productname, String((float)price / 100.0));
            buttonPress= false;
            price= 0;
            tempInkassoOff = true;
            tempInkassoOffTime = millis();
            waitForAnswer = true;
            coffeecounter = coffeemaker->readRegister("0004");
            delay(100);
            Serial.printf_P(PSTR("coffeecounter: %d"), coffeecounter);
            for(int i=1; i<= 10 && !coffeemaker->inkasso_off(false); i++) {
              delay(20);
              if(i==10) {
                logger.log(LOG_DEBUG, F("Failed to activate inkasso mode"));
              }
            }
            waitForAnswer = false;
            delay(500);
            oled->message_print_scroll(chucknorris.getNextChucknorrisFact());
          } 
          else {
            buzzer->beep(2);
            oled->message_print(logger.printCredit(credit), F("Not enough"), 2000); 
          }
        } 
        else { // if no button was pressed on coffeemaker / check credit
          oled->message_print(logger.printCredit(credit), F("Remaining credit"), 2000);
        }
        i = MAX_CARDS; // leave loop (after card has been identified)
      }      
    }
    if (k == MAX_CARDS){ 
      k=0; 
      buzzer->beep(2);
      oled->message_print(String(logger.print10digits(RFIDcard)),F("card unknown!"),2000);
    }           
  }
  }
}

void executeCommand(String command) {
#if defined(DEBUG)
    logger.log("cmd=" + command);
#endif
    if( command == "RRR" ){          
      registerCards();
    }
    if(command == "LLL"){  // 'L' for 'list' sends RFID card numbers to app   
      listCards();
    }
    if(command.startsWith("DDD") == true){
      deleteCard(command);
    }    
    if((command.startsWith("CCC") == true) ){
      chargeCard(command);
    } 
    if(command.startsWith("CHA") == true){
      updatePricelist(command);
    }
    if(command.startsWith("REA") == true){
      readPricelist();
    } 

    if(command.startsWith("UPDATE") == true) {
      messageBroker->publish(F("Firmwareupdate requested"));
      update.startUpdate();
    }

    if(command.startsWith("RESTART") == true) {
      messageBroker->publish(F("Gerät wird neu gestartet"));
      ESP.restart();
    }

//    if(command.startsWith("JOURNAL") == true) {
//      messageBroker->publish(journal.exportJournal());
//    }

    if(command == "?M3"){
      waitForAnswer = true;
      if(coffeemaker->inkasso_on(true)) {
        messageBroker->publish(F("Inkasso-mode turned ON"));
      }
      waitForAnswer = false;
    }
    if(command == "?M1"){
      waitForAnswer = true;
      if(coffeemaker->inkasso_off(true)) {
        messageBroker->publish(F("Inkasso-mode turned OFF"));
      }  
      waitForAnswer = false;
    }
    if(command == "FA:04"){        // small cup ordered via app
      coffeemaker->toCoffeemaker("FA:04\r\n"); 
      override = true;
    }
    if(command == "FA:06"){        // large cup ordered via app
      coffeemaker->toCoffeemaker("FA:06\r\n");  
      override = true;
    }
    if(command == "FA:0C"){        // extra large cup ordered via app
      coffeemaker->toCoffeemaker("FA:0C\r\n");  
      override = true;
    } 
 }

void dumpPricelistAndCards(pricelist_t pricelist, cardlist_t cardlist) {
#if defined(DEBUG)
  for(int i=0; i<10; i++) {
    String message = "price for product[" + String(i) + "]: " + String(pricelist.prices[i]);
    logger.log(LOG_DEBUG, "msg=" + message);
    yield(); // Enable ESP8266 to do background tasks and make Watchdog happy
  }
  for(int i=0; i<MAX_CARDS; i++) {
    String message = "registered card[" + String(i) + "]: " + String(cardlist.cards[i].card);
    logger.log(LOG_DEBUG, message);
    yield(); // Enable ESP8266 to do background tasks and make Watchdog happy
  }
#endif
}

void registerCards() {
  actTime = millis();
  buzzer->beep(1);
  oled->message_print(F("Registering"),F("new cards"),0);
  messageBroker->publish(F("Registering new cards"));
  registeringStarted = true;
  nfcReader->registernewcards();
  registeringStarted = false;
  cardlist = eepromConfig.readCards();
  messageBroker->publish(F("Registering ended"));
  oled->message_clear();
}

void listCards() {
  String cards = "";
  for(int i=0;i<MAX_CARDS;i++){
    unsigned long card=cardlist.cards[i].card;
#ifdef BLE_ENABLED
//    bleConnection.getSerial().print(logger.print10digits(card)); 
#endif
    if(card > 0) cards += logger.print10digits(card);
    if (i < (MAX_CARDS-1)) {
#ifdef BLE_ENABLED
//     bleConnection.getSerial().write(',');  // write comma after card number if not last
#endif
      if(card > 0) cards += ",";
    }
  }
  messageBroker->publish("CARDS:" + cards);
}

void deleteCard(String command) {
  command.remove(0,3); // removes "DDD" and leaves the index
  int index = command.toInt();
  index--; // list picker index (app) starts at 1, while RFIDcards array starts at 0
  unsigned long card= cardlist.cards[index].card;
  int credit= eepromConfig.readCredit(index*6+4);      
  oled->message_print(logger.print10digits(card), F("deleting"), 2000);    
  eepromConfig.deleteCard(index*6, 0);
  eepromConfig.deleteCredit(index*6+2, 0);
  buzzer->beep(1);
  messageBroker->publish("Deleted card: " + String(card));
}

void chargeCard(String command) {
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
  int credit= eepromConfig.readCredit(i*6+4);
  credit+= j;
  eepromConfig.updateCredit(i*6+4, credit);
  buzzer->beep(1);
  unsigned long card=cardlist.cards[i].card;
  oled->message_print(logger.print10digits(card),"+"+logger.printCredit(j),2000);    
  messageBroker->publish("Charged card " + String(card) + ", new credit: " + logger.printCredit(j));
}

void updatePricelist(String command) {
  int k = 3;
  pricelist_t pricelist;
  for (int i = 0; i < 11;i++){  
    String tempString = "";
    do {
      tempString += command.charAt(k);
      k++;
    } while (command.charAt(k) != ','); 
    int j = tempString.toInt();
#if defined(DEBUG)        
    logger.log(String(i*2) + PRICELIST_ADDRESS_OFFSET);
#endif
    if(i!=10) {
      pricelist.prices[i] = j;
    } else {
      pricelist.defaultCredit = j;
    }
    k++;
  }
  eepromConfig.updatePricelist(pricelist);
  buzzer->beep(1);
  oled->message_print(F("Pricelist"), F("updated!"), 2000);
  messageBroker->publish(F("Updated pricelist on device"));
}

void readPricelist() {
    // delay(100); // testweise      
   for (int i = 0; i < 11; i++) {
     price = pricelist.prices[i];
#ifdef BLE_ENABLED
 //   bleConnection.getSerial().print(int(price/100));
 //   bleConnection.getSerial().print('.');
 //   if ((price%100) < 10){
 //     bleConnection.getSerial().print('0');
 //   }
 //   bleConnection.getSerial().print(price%100);
 //   if (i < 10) bleConnection.getSerial().write(',');
#endif
  }
  messageBroker->publish(F("Received pricelist from device"));
}

