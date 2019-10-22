#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP_SSD1306.h>    
#include <Adafruit_GFX.h>   
#include <SPI.h>           
#include <Wire.h>          
#define OLED_RESET  18  
ESP_SSD1306 display(OLED_RESET);

#define errorPin 16

#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int pinpir = D2;

const int sleep_time = 20;
WiFiClient client;

String variable_id1 = "58805e8b7625427f42d457ec";
String variable_id2 = "58805e9b7625427f42d458a2";
String variable_id3 = "58805ea67625427f41387227";
String variable_id4 = "58805eb37625427f52d68293";
String variable_id5 = "58805eba7625427f413872b0";
String variable_id6 = "58805ecb7625427f42d45a5e";
String variable_id7 = "5886e48c7625425e2793f212";
String token = "pbLXUzyurgqxQEDTdfwMVyTrNLRYsi";

const char* ssid = "INTERNET RUMAH";
const char* password = "0271783051";

void ubiSave_value(String, String);

int totalChannels = 8; //dari 0 s/d 7

int addressA = D8; //pin A D8 nodemcu
int addressB = D7; //pin B D7
int addressC = D6; //pin C D6

int A = 0;      //Address pin A
int B = 0;      //Address pin B
int C = 0;      //Address pin C

int makan; int mandi; int kasur; int suara;

void setup()
{
  pinMode(addressA, OUTPUT);
  pinMode(addressB, OUTPUT);
  pinMode(addressC, OUTPUT);
  pinMode(A0, INPUT);
  
  display.begin();  // Switch OLED
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,10);
  display.println("Bibox");
  display.setCursor(20,40);
  display.println(" IoT ");
  display.display();

pinMode(errorPin, OUTPUT); 
  for (int i=0;i<4; i++)
  {
    digitalWrite(errorPin ,HIGH);
    delay(200);
    digitalWrite(errorPin ,LOW);
    delay(200);
  }
  Serial.begin(115200);
  dht.begin();
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  int n = WiFi.scanNetworks();
  Serial.println("scan done"); 
  if (n == 0)
  {
    Serial.println("no networks found");
    Serial.println("Going into sleep");
// ESP.deepSleep(sleep_time * 1000000);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi connected");
}

void loop()
{
  float temp = dht.readTemperature(false);
  float hum = dht.readHumidity();
  ubiSave_value(String(variable_id4), String(temp));
  ubiSave_value(String(variable_id5), String(hum));

  int pir = digitalRead(pinpir);
  ubiSave_value(String(variable_id1), String(pir));

    A = bitRead(0,0); //Take first bit from binary value of i channel.
    B = bitRead(0,1); //Take second bit from binary value of i channel.
    C = bitRead(0,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai0 = analogRead(A0);
 if (nilai0 < 150) {makan = 0;} 
 if (nilai0 > 150 && nilai0 < 460) {makan = 1;}
 if (nilai0 > 460 && nilai0 < 790) {makan = 2;}
 if (nilai0 > 790) {makan = 3;}
 ubiSave_value(String(variable_id6), String(makan));

    A = bitRead(3,0); //Take first bit from binary value of i channel.
    B = bitRead(3,1); //Take second bit from binary value of i channel.
    C = bitRead(3,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai3 = analogRead(A0);  
 if (nilai3 < 150) {mandi = 0;} 
 if (nilai3 > 150 && nilai3 < 460) {mandi = 1;}
 if (nilai3 > 460 && nilai3 < 790) {mandi = 2;}
 if (nilai3 > 790) {mandi = 3;}
 ubiSave_value(String(variable_id7), String(mandi));

    A = bitRead(5,0); //Take first bit from binary value of i channel.
    B = bitRead(5,1); //Take second bit from binary value of i channel.
    C = bitRead(5,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai5 = analogRead(A0);
 if (nilai5 > 200) {kasur = 0;}
 if (nilai5 < 200) {kasur = 1;}
 ubiSave_value(String(variable_id3), String(kasur));

    A = bitRead(7,0); //Take first bit from binary value of i channel.
    B = bitRead(7,1); //Take second bit from binary value of i channel.
    C = bitRead(7,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai7 = analogRead(A0);
 if (nilai7 > 100) {suara = 0;}
 if (nilai7 < 100) {suara = 1;}
 ubiSave_value(String(variable_id2), String(suara));

  Serial.println("Ubidots data");
  Serial.println("temperature: "+String(temp));
  Serial.println("humidity: "+String(hum));
  
  Serial.println(" Going to Sleep for a while !" );
  delay(sleep_time*1000);  
}

void ubiSave_value(String variable_id, String value)
{
  String var = "{\"value\": " + value +"}"; // We'll pass the data in JSON format
  String length = String(var.length());

  if (client.connect("things.ubidots.com", 80))
  {
    Serial.println("Connected to Ubidots...");
    delay(100);

    client.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    Serial.println("POST /api/v1.6/variables/"+variable_id+"/values HTTP/1.1");
    client.println("Content-Type: application/json");
    Serial.println("Content-Type: application/json");
    client.println("Content-Length: "+ length);
    Serial.println("Content-Length: "+ length);
    client.println("X-Auth-Token: "+ token);
    Serial.println("X-Auth-Token: "+ token);
    client.println("Host: things.ubidots.com\n");
    Serial.println("Host: things.ubidots.com\n");
    client.print(var);
    Serial.print(var+"\n");
  }
  else
  {
    Serial.println("Ubidots connection failed...");
  }
  
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  
  if (client.connected())
  {
    Serial.println("Disconnecting from Ubidots...");
    client.stop();
  }
}