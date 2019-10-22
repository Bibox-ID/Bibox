#include <DHT.h>
#include <ESP8266WiFi.h>

#define errorPin 16

#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int pinair = D0;
int pinsuara = D1;
int pinpir = D2;
int pinmakan = A0;

const int sleep_time = 20;
WiFiClient client;

String variable_id1 = "58805e8b7625427f42d457ec";
String variable_id2 = "58805e9b7625427f42d458a2";
String variable_id3 = "58805ea67625427f41387227";
String variable_id4 = "58805eb37625427f52d68293";
String variable_id5 = "58805eba7625427f413872b0";
String variable_id6 = "58805ecb7625427f42d45a5e";
String token = "pbLXUzyurgqxQEDTdfwMVyTrNLRYsi";

const char* ssid = "INTERNET RUMAH";
const char* password = "0271783051";

void ubiSave_value(String, String);

void setup()
{
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
  int air = digitalRead(pinair);
  int suara = digitalRead(pinsuara);
  int pir = digitalRead(pinpir);
  int makan = analogRead(pinmakan);

  ubiSave_value(String(variable_id1), String(pir));
  ubiSave_value(String(variable_id2), String(suara));
  ubiSave_value(String(variable_id3), String(air));
  ubiSave_value(String(variable_id4), String(temp));
  ubiSave_value(String(variable_id5), String(hum));
  ubiSave_value(String(variable_id6), String(makan));

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