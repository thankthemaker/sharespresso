
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

#ifdef ESP32
#include <rom/rtc.h>
#endif
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
#include "juragigax8.h"
#include "oled_spi.h"
#include "rc522nfc.h"

#include "chucknorris.h"

#include <MQTTClient.h>
std::map <char, String> products;

// general variables (used in loop)
boolean buttonPress = false;
boolean registeringStarted = false;


String BTstring=""; // contains what is received via bluetooth (from app or other bt client)
unsigned long actTime; // timer for RFID etc
unsigned long buttonTime; // timer for button press 
unsigned long tempInkassoOffTime; // timer for temporary inkasso mode press 
unsigned long lastAlive; // time of the last Alive signal send
unsigned long aliveCounter = 0;
unsigned long lastRegisterRead = 0;

boolean override = false;  // to override payment system by the voice-control/button-press app
unsigned long RFIDcard = 0;
int price=0;
int coffeecounter = 0;
String productname="undefined";
pricelist_t pricelist;

FP<void,String>fp;
Wifi wifi;
Buzzer *buzzer = new Buzzer();
IMessageBroker *messageBroker = MessageBrokerFactory::getInstance()->createMessageBroker();
IDisplay *oled = new OledSpiDisplay();
INfcReader *nfcReader = new Rc522NfcReader(messageBroker,oled, buzzer);
ICoffeeMaker *coffeemaker = new JuraGigaX8(oled, buzzer);
Chucknorris chucknorris;

HTTPClient http;

NtpClient ntpClient;
CoffeeLogger logger;
EEPROMConfig eepromConfig;

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

  http.setTimeout(5000);
  http.setReuse(true);

  SPI.begin();      // Init SPI bus, needed by RC522-Reader

  logger.log(LOG_DEBUG, "number of products: " + String(coffeemaker->getProducts().size()));
  logger.log(LOG_INFO, F("initializing Display"));
  oled->initDisplay();
  
  oled->message_print(F("sharespresso"), F("starting up"), 1500);
#ifdef COFFEEMAKER_ENABLED
  coffeemaker->initCoffeemaker(); // start serial communication at 9600bps

  int retries = 20;
  while(!coffeemaker->inkasso_off(false) && retries > 0) {
    logger.log(LOG_INFO, F("Unable to turn off Inkasso-Mode, retrying in 500ms"));
    retries--;
    delay(500);
  }
#endif

  // initialized rfid lib
  logger.log(LOG_INFO, F("initializing rfid reader"));
  nfcReader->initNfcReader();

  logger.log(LOG_INFO, F("reading pricelist and cards from EEPROM"));
  pricelist = eepromConfig.readPricelist();

  dumpPricelist(pricelist);

  oled->message_print(F("connecting"), F("WIFI"), 0);
  wifi.setup_wifi();
  oled->message_print(F("WLAN-IP:"), WiFi.localIP().toString(), F("SSID:"), WiFi.SSID(), 0);

  fp.attach(&executeCommand);
  messageBroker->init(fp);
  ntpClient.setupNtp();
  
  #ifdef COFFEEMAKER_ENABLED
  // activate coffemaker connection and inkasso mode
  retries = 5;
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
  #endif
}

void loop() {  
    wifi.loop();
    messageBroker->loop();

    if(millis() - lastAlive > 15000) {
      lastAlive = millis();
      ++aliveCounter;
      messageBroker->publish("coffeemaker is alive, count " + String(aliveCounter) + ", free Heap: " + ESP.getFreeHeap());
    }
 
  // Get key pressed on coffeemaker
  String message = "";
  message = coffeemaker->fromCoffeemaker();   // gets answers from coffeemaker 
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
      oled->message_print(F("Product"), productname, 0);
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
  
  if(!registeringStarted) {
    // RFID Identification      
    RFIDcard = 0;  
    actTime = millis(); 
    do {
      RFIDcard = nfcReader->nfcidread();
      if (RFIDcard != 0) {
        oled->message_clear();
        break; 
      }           
    } while ( (millis()-actTime) < 60 );  

    if (RFIDcard != 0) {
//      int k = MAX_CARDS;
//      for(int i=0;i<MAX_CARDS;i++){         
//        if (((RFIDcard) == (cardlist.cards[i].card)) && (RFIDcard != 0 )){
//          k = i;
            
        oled->message_print(F("Checking"), F("credit"), F(""), F("please wait..."), 0); 
        int credit = loadCard(RFIDcard);

//        if(buttonPress == true) { // button pressed on coffeemaker?
           if (credit > 0) {
//            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
//            delay(20);
//            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
//            delay(20);
//            coffeemaker->toCoffeemaker("?ok\r\n"); // prepare coffee
//            delay(20);
            oled->message_print(F("Credit"), F("remaining"), String(credit) + " Coffees", F("choose product"), 0);
//            messageBroker->sendmessage (logger.print10digits(RFIDcard), productname, (float)price / 100.0);   
//            buttonPress= false;
//            price= 0;
//            delay(500);
//            oled->message_print_scroll(chucknorris.getNextChucknorrisFact());
          } else {
            buzzer->beep(2);
            oled->message_print(F("Not enough"), F("credit"), 2000); 
          }
//        } 
//        else { // if no button was pressed on coffeemaker / check credit
//          oled->message_print(logger.printCredit(credit), F("Remaining credit"), 2000);
//        }
//        i = MAX_CARDS; // leave loop (after card has been identified)
//      }      
//    }
//    if (k == MAX_CARDS){ 
//      k=0; 
//      buzzer->beep(2);
//      oled->message_print(String(logger.print12digits(RFIDcard)),F("card unknown!"),2000);
//    }           
  }
  }
}

int loadCard(long card) {
  http.begin("https://t4ispau688.execute-api.us-west-2.amazonaws.com/prod/cards/" + logger.print12digits(card));
  Serial.println("Excecuting GET https://t4ispau688.execute-api.us-west-2.amazonaws.com/prod/cards/" + logger.print12digits(card));
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Payload " + payload);
      http.end();
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(payload);
      signed int credit =  json["credit"];
      Serial.println("Credit " + String(credit));
     return credit;
      } else {
        Serial.printf("[HTTP] GET... failed, code: %s", httpCode);
        return 0;
      }
    
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
    return 0;
  }
}

void executeCommand(String command) {
#if defined(DEBUG)
    logger.log("cmd=" + command);
#endif
    if( command == "RRR" ){          
      registerCards();
    }
 
    if(command.startsWith("CHA") == true){
      updatePricelist(command);
    }
    if(command.startsWith("REA") == true){
      readPricelist();
    } 

    if(command.startsWith("RESTART") == true) {
      messageBroker->publish(F("Gerät wird neu gestartet"));
      ESP.restart();
    }

    if(command == "?M3"){
      if(coffeemaker->inkasso_on(true)) {
        messageBroker->publish(F("Inkasso-mode turned ON"));
      }
    }
    if(command == "?M1"){
      if(coffeemaker->inkasso_off(true)) {
        messageBroker->publish(F("Inkasso-mode turned OFF"));
      }  
    }
 }

void dumpPricelist(pricelist_t pricelist) {
#if defined(DEBUG)
  for(int i=0; i<10; i++) {
    String message = "price for product[" + String(i) + "]: " + String(pricelist.prices[i]);
    logger.log(LOG_DEBUG, "msg=" + message);
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
  messageBroker->publish(F("Registering ended"));
  oled->message_clear();
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
   for (int i = 0; i < 11; i++) {
     price = pricelist.prices[i];
  }
  messageBroker->publish(F("Received pricelist from device"));
}
