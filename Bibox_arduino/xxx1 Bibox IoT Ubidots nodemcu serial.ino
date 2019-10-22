
#include <DHT.h>
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int pushButton0 = D0;
int pushButton1 = D1;
int pushButton2 = D2;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton0, INPUT);
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  dht.begin();
}

void loop() {
  Serial.print(digitalRead(pushButton0));
  Serial.print(" / ");
  Serial.print(digitalRead(pushButton1));
  Serial.print(" / ");
  Serial.print(digitalRead(pushButton2));
  Serial.print(" / ");
  Serial.print(dht.readTemperature(false));
  Serial.print(" / ");
  Serial.print(dht.readHumidity());
  Serial.print(" / ");
  Serial.println(analogRead(A0));
  delay(1000);
}