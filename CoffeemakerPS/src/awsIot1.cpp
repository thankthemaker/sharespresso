#ifdef ESP32
#include "awsIot1.h";

static FP<void,String> fp;

void callbackAws(char *topicName, int payloadLen, char *payLoad) {
  Serial.print(F("Payload "));
  char* msg = new char[payloadLen+1]();
  memcpy (msg,payLoad,payloadLen);
  Serial.println(msg);
  fp(String(msg));
  delete msg;
}

AwsIotClient::AwsIotClient() {};

//generate random mqtt clientID
char* AwsIotClient::generateClientID () {
  char* cID = new char[23]();
  for (int i=0; i<22; i+=1)
    cID[i]=(char)random(1, 256);
  return cID;
}

//connects to websocket layer and mqtt layer
bool AwsIotClient::connect () {
  int rc = 0;
  do {
    int rc = awsIot.connect(AWS_ENDPOINT,this->generateClientID());
    if(rc == 0) {
      Serial.println("Connected to AWS");
    } else {
      Serial.println("AWS connection failed");
    }
    delay(500);
  } while(rc == -30); // Keep in retry loop until client is idle
  return true;
}

//subscribe to a mqtt topic
void AwsIotClient::subscribe () {
  int rc = 0;
  do {
    int rc = awsIot.subscribe(TOPIC_IN,callbackAws);
    if(rc == 0){
      Serial.println("Subscribe successfull");
    } else {
      Serial.println("Subscribe failed");
    }
    delay(500);
  } while(rc == -30); // Keep in retry loop until client is idle

}

//send a message to a mqtt topic
void AwsIotClient::sendmessage(const String cardId, const String product, const float price){ 
        StaticJsonBuffer<maxMQTTpackageSize> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["cardid"] = cardId;
        root["timestamp"] = now();
        root["product"] = product;
        root["price"] = price;

        std::unique_ptr<char []> buffer(new char[maxMQTTpackageSize]());
        root.printTo(buffer.get(), maxMQTTpackageSize);

        this->publish_to_topic(TOPIC_COFFEE, buffer.get());
}

//send a message to a mqtt topic
void AwsIotClient::sendmessage(const String cardId, const int credit){ 
        StaticJsonBuffer<maxMQTTpackageSize> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["userId"] = "123";
        root["cardId"] = cardId;
        root["credit"] = credit;
        root["preregistred"] = true;

        std::unique_ptr<char []> buffer(new char[maxMQTTpackageSize]());
        root.printTo(buffer.get(), maxMQTTpackageSize);

        this->publish_to_topic(TOPIC_CARD, buffer.get());
}

void AwsIotClient::publish_to_topic(const char* topic, const String& message) {
  char payload[512];
  sprintf(payload, message.c_str());

  int rc = 0;
  do {
    rc = awsIot.publish(const_cast<char*>(topic), payload);
    if(rc == 0) {        
      Serial.print("Publish Message:");
      Serial.println(message);
    } else if(rc == -13) {
      this->reconnect();
    } else{
      Serial.println("Publish failed(" + String(rc) + "), retrying...");
    }
    delay(500);
  } while(rc == -30 || rc == -13); // Keep in retry loop until client is idle
}

void AwsIotClient::init(FP<void,String>tmpFp) {
    fp = tmpFp;
    if (this->connect ()){
      this->subscribe ();
    }
}

void AwsIotClient::loop() {}

void AwsIotClient::reconnect() {
     if (this->connect ()){
      this->subscribe ();
    }
};

void AwsIotClient::publish(String message) {
        this->publish_to_topic(TOPIC_OUT, message);
 };
 #endif