#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Super 4"; //ชื่อไวไฟ
const char* pass = "samsamsam2830"; //รหัสนักศึกษา
const char* mqtt_server = "broker.mqttdashboard.com"; // 161.246.38.29 (ใช้ตอนสอบ)
char Topic[] = "private"; //เปลี่ยนชื่อtopicตามที่จารย์บอก
int value;
int button;

WiFiClient samClient; //ชื่อclient
PubSubClient client(samClient);

void reconnect();
void setup() {

  // put your setup code here, to run once:
  WiFi.begin(ssid, pass);
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  pinMode(A0, INPUT); // ขาตัวแปรปรับค่าได้
  pinMode(D0, INPUT); //สวิทซ์
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  delay(2000); //1000 = 1วินาที
  button = digitalRead(D0); //ถ้ากดปุ่มสวิทซ์ค้างค่าbuttonจะเป็น0
  if (!digitalRead(D0)) 
  {
    digitalWrite(D0, HIGH);
  }
  else
  {
    digitalWrite(D0,LOW);
  }
  Serial.println(button);
  value = analogRead(A0);
  String publishStr = String();
  publishStr.concat("Value = "); //.concat() คือการต่อคำ พยายามเข้าใจตรงนี้เองนะ
  publishStr.concat(String(value)); 
  publishStr.concat(" and button = ");
  publishStr.concat(String(button));
  client.publish(Topic, publishStr.c_str());
}

void reconnect(){
  while(!client.connected()){
    String id = "sam"; //ชื่อตัวเองไม่ก็รหัสนักศึกษา
    client.connect(id.c_str());
  }
}
