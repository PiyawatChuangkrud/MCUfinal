#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Super 4"; //ชื่อไวไฟ
const char* pass = "samsamsam2830"; //รหัสไวไฟ
const char* mqtt_server = "broker.mqttdashboard.com"; // 161.246.38.29 (ใช้ในตอนที่สอบ)
char Topic[] = "private2"; //หัวข้อtopicตามที่อ.บอก
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
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
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
  //อัลกอที่ใช้ในการดูค่า
  messageStr.toLowerCase();
  if(messageStr == "red"){
    digitalWrite(D0, HIGH);              
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
  }
  else if(messageStr == "blue"){
    digitalWrite(D0, LOW);              
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
  }
  else if(messageStr == "green"){
    digitalWrite(D0, LOW);              
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
  }
  //ส่วนนี้คือในกรณีที่ค่าที่ได้รับเป็นช่วงเลข(ช่วงสีให้ปรับตามคำสั่ง)
  /*int number = messageStr.toInt();
  if(number >=0 && number <=100){
    digitalWrite(D0, HIGH);              
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
  }
  else if(number >100 && number <= 200){
    digitalWrite(D0, LOW);              
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
  }
  else if(number > 200 && number <= 300){
    digitalWrite(D0, LOW);              
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
  }*/
}

