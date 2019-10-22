#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 8
Adafruit_SSD1306 display(OLED_RESET);

const int makanpin = 0; //potensio A0
int makan;

const int mandipin = 1; //potensio A1
int mandi;

const int sonpin = 2; //sensor suara A2
int suarabayi;

const int watpin = 3; //sensor air A3
int kasurnya;

#include <dht.h>
dht DHT;

const int pirpin = 2; //pir D2 
int pirstatus = 0;

int lampu = 4; //led D4
int kipas = 5; //kipas D5

char input;

String PIR, SON, WAT, MKN, MND;

void setup(){
  Serial.begin(9600);
 
  display.begin();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,5);
  display.println("Bibox"); 
  display.display();
  display.invertDisplay(true);
  delay(3000); 
  display.invertDisplay(false); 
  display.clearDisplay();

  pinMode(pirpin, INPUT);
  pinMode(lampu, OUTPUT);
  pinMode(kipas, OUTPUT);
  digitalWrite(lampu, LOW);
  digitalWrite(kipas, HIGH);
}

void loop(){

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,5);
  display.println("Bibox"); 
  display.display();
  display.invertDisplay(false); 
  display.clearDisplay();

 makan = analogRead(makanpin);
 if (makan < 150) {MKN = "0x";} 
 if (makan > 150 && makan < 460) {MKN = "1x";}
 if (makan > 460 && makan < 790) {MKN = "2x";}
 if (makan > 790) {MKN = "3x";}   

 mandi = analogRead(mandipin);
 if (mandi < 150) {MND = "0x";} 
 if (mandi > 150 && mandi < 460) {MND = "1x";}
 if (mandi > 460 && mandi < 790) {MND = "2x";}
 if (mandi > 790) {MND = "3x";}

 suarabayi = analogRead(sonpin);
 if (suarabayi > 100) {SON = "Mewek";} 
 if (suarabayi < 40 && suarabayi > 30) {SON = "Resah";}
 else {SON = "Tenang";} 

 kasurnya = analogRead(watpin);
 if (kasurnya > 50 && kasurnya < 200) {WAT = "Lembab";}
 if (kasurnya > 200) {WAT = "Basah";}
 else {WAT = "Kering";} 

 DHT.read11(3); //D3
 
 pirstatus = digitalRead(pirpin);
 if (pirstatus == LOW) {PIR = "Awas!";}  
 else {PIR = "Ada";}

  String data="/"+String(PIR)+"/"+String(SON)+"/"+String(WAT)+"/"+String("Bagus")+"/"+String(DHT.temperature,1)+"/"+String(DHT.humidity,1)+"/"+String
(MKN)+"/"+String(MND)+"/";
  Serial.println(data);
  delay(1000);

 if (Serial.available()) {
    input = Serial.read();
    if (input == 'a' || input == 'A') {digitalWrite(lampu, HIGH);}
    if (input == 'b' || input == 'B') {digitalWrite(lampu, LOW);}
    if (input == 'c' || input == 'C') {digitalWrite(kipas, LOW);}
    if (input == 'd' || input == 'D') {digitalWrite(kipas, HIGH);}
    if (input == 'e' || input == 'E') {}
    if (input == 'f' || input == 'F') {}
    }
}