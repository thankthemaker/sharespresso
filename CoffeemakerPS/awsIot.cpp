/*
#include "awsIot.h";

static FP<void,String> fp;

void callbackAws(MQTT::MessageData& md) {
  MQTT::Message &message = md.message;

  Serial.print("Message arrived: qos ");
  Serial.print(message.qos);
  Serial.print(", retained ");
  Serial.print(message.retained);
  Serial.print(", dup ");
  Serial.print(message.dup);
  Serial.print(", packetid ");
  Serial.println(message.id);
  Serial.print("Payload ");
  char* msg = new char[message.payloadlen+1]();
  memcpy (msg,message.payload,message.payloadlen);
  Serial.println(msg);
  fp(String(msg));
  delete msg;

}

AwsIotClient::AwsIotClient() : awsWSclient(1000), ipstack(awsWSclient){};

//generate random mqtt clientID
char* AwsIotClient::generateClientID () {
  char* cID = new char[23]();
  for (int i=0; i<22; i+=1)
    cID[i]=(char)random(1, 256);
  return cID;
}

//connects to websocket layer and mqtt layer
bool AwsIotClient::connect () {
    if (client == NULL) {
      client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
    } else {

      if (client->isConnected ()) {    
        client->disconnect ();
      }  
      delete client;
      client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
    }


    //delay is not necessary... it just help us to get a "trustful" heap space value
    delay (1000);
    Serial.print (millis ());
    Serial.print (" - conn: ");
    Serial.print (++connection);
    Serial.print (" - (");
    Serial.print (ESP.getFreeHeap ());
    Serial.println (")");

   int rc = ipstack.connect(AWS_ENDPOINT, AWS_PORT);
    if (rc != 1)
    {
      Serial.println("error connection to the websocket server");
      return false;
    } else {
      Serial.println("websocket layer connected");
    }

    Serial.println("MQTT connecting");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    char* clientID = this->generateClientID ();
    data.clientID.cstring = clientID;
    rc = client->connect(data);
    delete[] clientID;
    if (rc != 0)
    {
      Serial.print("error connection to MQTT server");
      Serial.println(rc);
      return false;
    }
    Serial.println("MQTT connected");
    return true;
}

//subscribe to a mqtt topic
void AwsIotClient::subscribe () {
   //subscript to a topic
    int rc = client->subscribe(TOPIC_IN, MQTT::QOS0, callbackAws);
    if (rc != 0) {
      Serial.print("rc from MQTT subscribe is ");
      Serial.println(rc);
      return;
    }
    Serial.println("MQTT subscribed");
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

void AwsIotClient::publish_to_topic(const char* topic, const String& message) {
        MQTT::Message mqtt_message;
        std::unique_ptr<char []> buf(new char[message.length() + 1]());
        strcpy(buf.get(), message.c_str());
        mqtt_message.qos = MQTT::QOS0;
        mqtt_message.retained = false;
        mqtt_message.dup = false;
        mqtt_message.payload = (void*)buf.get();
        mqtt_message.payloadlen = strlen(buf.get())+1;
        client->publish(topic, mqtt_message); 
}
void AwsIotClient::init(FP<void,String>tmpFp) {
    //fill AWS parameters    
    awsWSclient.setAWSRegion(AWS_REGION);
    awsWSclient.setAWSDomain(AWS_ENDPOINT);
    awsWSclient.setAWSKeyID(AWS_KEY);
    awsWSclient.setAWSSecretKey(AWS_SECRET);
    awsWSclient.setUseSSL(true);

    fp = tmpFp;

    if (this->connect ()){
      this->subscribe ();
    }
}

void AwsIotClient::loop() {
  //keep the mqtt up and running
  if (awsWSclient.connected ()) {    
      client->yield();
  } else {
    //handle reconnection
    if (connect ()){
      this->subscribe ();      
    }
  }
}

void AwsIotClient::reconnect() {};

void AwsIotClient::publish(String message) {
        this->publish_to_topic(TOPIC_OUT, message);
 };
*/
