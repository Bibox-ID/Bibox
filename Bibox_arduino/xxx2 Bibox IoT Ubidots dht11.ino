#include <DHT.h>
#include <ESP8266WiFi.h>
#define errorPin 16
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const int sleep_time = 20;
WiFiClient client;

String variable_id1 = "5875a4a17625427ff2864af0";
String variable_id2 = "5875a4b17625427fec83c60e";
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

  ubiSave_value(String(variable_id1), String(temp));
  ubiSave_value(String(variable_id2), String(hum));

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