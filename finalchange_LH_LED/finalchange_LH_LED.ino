#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "AM"; //ชื่อไวไฟ
const char* pass = "aaaa2541"; //รหัสไวไฟ
const char* mqtt_server = "broker.mqttdashboard.com"; // 161.246.38.29 (ใช้ในตอนที่สอบ)
char Topic[] = "privateserver"; //หัวข้อtopicตามที่อ.บอก
WiFiClient samClient; //ชื่อclient
PubSubClient client(samClient);

void callback(char* topic, byte* message, unsigned int length);
void reconnect();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(D0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected());{
    reconnect();
  }
  client.loop();
}

void reconnect(){
  while(!client.connected()){
    String id = "sam"; //เปลี่ยนเป็นชื่อตัวเองไม่ก็รหัสนักศึกษาตัวเอง
    id += String(random(0xffff), HEX);
    client.connect(id.c_str());
    client.subscribe(Topic);
  }
}
void callback(char* topic, byte* message, unsigned int length){
  String messageStr = String();
  for (int i = 0;i <length;i++){
    messageStr += (char)message[i];
  }
  Serial.println(messageStr);
  int number = messageStr.toInt();
  analogWrite(D0, number);
}

