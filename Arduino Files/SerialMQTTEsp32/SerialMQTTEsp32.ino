#define RXD2 16
#define TXD2 17

#include <WiFi.h> 
#include <PubSubClient.h> 
 
const char* ssid = "YOURSSID";
const char* password = "YOURPASSWORD";
const char* mqttServer = "YOURCLOUDMQTTURL";
const int mqttPort = YOURPORT; //Your port number
const char* mqttUser = "YOURMQTTUSER";
const char* mqttPassword = "YOURMQTTPASSWORD";
char payload[512];
int counter=0;
int m1=0;      
int m2=0;  
int m3=0;  
int m4=0;  
int m5=0;  
int m6=0;  
int m7=0;  
int m8=0;  
int m9=0;  
int m10=0;  
int m11=0;
int tick =0; 
 
WiFiClient ESPClient;
PubSubClient client(ESPClient);

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}
 
void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Please wait while connecting to WiFi");
  }
 
  Serial.println("ESP > Connected to WiFi");
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("ESP > Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected to CloudMQTT");
 
    } else {
 
      Serial.print("ERROR > failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }  
  client.publish("ESP32", "Start OK");
  
}
 
void loop() { 
  client.loop();
  
  if(tick>10)
  {
    counter=0;
    tick=0;
  }
  tick++;
  while (Serial2.available()) {
    tick=0;
    counter++;
        if(counter==1)
    {
      m1=int(char(Serial2.read()));
    }
        if(counter==2)
    {
      m2=int(char(Serial2.read()));
    }
        if(counter==3)
    {
      m3=int(char(Serial2.read()));
    }
        if(counter==4)
    {
      m4=int(char(Serial2.read()));
    }
         if(counter==5)
    {
      m5=int(char(Serial2.read()));
    }
        if(counter==6)
    {
      m6=int(char(Serial2.read()));
    }
        if(counter==7)
    {
      m7=int(char(Serial2.read()));
    }
        if(counter==8)
    {
      m8=int(char(Serial2.read()));
    }
        if(counter==9)
    {
      m9=int(char(Serial2.read()));
    }
         if(counter==10)
    {
      m10=int(char(Serial2.read()));
    }
          if(counter==11)
    {
      m11=int(char(Serial2.read()));
      Serial.println("Send Message");
      mes();
    }
  }
}

void mes (void)
{
    String sm1="\"M1\":\""+String(m1)+"\",";
    String sm2="\"M2\":\""+String(m2)+"\",";
    String sm3="\"M3\":\""+String(m3)+"\",";
    String sm4="\"M4\":\""+String(m4)+"\",";
    String sm5="\"M5\":\""+String(m5)+"\",";
    String sm6="\"Mi1\":\""+String(m6)+"\",";
    String sm7="\"Mi2\":\""+String(m7)+"\",";
    String sm8="\"Mi3\":\""+String(m8)+"\",";
    String sm9="\"Mi4\":\""+String(m9)+"\",";
    String sm10="\"Mi5\":\""+String(m10)+"\",";
    String sm11="\"Mi6\":\""+String(m11)+"\"";
    String JSON = "{"+sm1+sm2+sm3+sm4+sm5+sm6+sm7+sm8+sm9+sm10+sm11+"}";
    sprintf(payload,string2char(JSON));
    client.publish("SMC", payload);
}
