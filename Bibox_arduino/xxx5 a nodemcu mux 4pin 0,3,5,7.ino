int totalChannels = 8; //dari 0 s/d 7

int addressA = D8; //pin A D8 nodemcu
int addressB = D7; //pin B D7
int addressC = D6; //pin C D6

int A = 0;      //Address pin A
int B = 0;      //Address pin B
int C = 0;      //Address pin C

void setup() {
  Serial.begin(9600);
  pinMode(addressA, OUTPUT);
  pinMode(addressB, OUTPUT);
  pinMode(addressC, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
    A = bitRead(0,0); //Take first bit from binary value of i channel.
    B = bitRead(0,1); //Take second bit from binary value of i channel.
    C = bitRead(0,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai0 = analogRead(A0);
    Serial.print(nilai0);
    Serial.print(" / ");

    A = bitRead(3,0); //Take first bit from binary value of i channel.
    B = bitRead(3,1); //Take second bit from binary value of i channel.
    C = bitRead(3,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai3 = analogRead(A0);
    Serial.print(nilai3);
    Serial.print(" / ");    

    A = bitRead(5,0); //Take first bit from binary value of i channel.
    B = bitRead(5,1); //Take second bit from binary value of i channel.
    C = bitRead(5,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai5 = analogRead(A0);
    Serial.print(nilai5);
    Serial.print(" / ");

    A = bitRead(7,0); //Take first bit from binary value of i channel.
    B = bitRead(7,1); //Take second bit from binary value of i channel.
    C = bitRead(7,2); //Take third bit from value of i channel.
    digitalWrite(addressA, A);
    digitalWrite(addressB, B);
    digitalWrite(addressC, C);
    int nilai7 = analogRead(A0);
    Serial.println(nilai7);

  delay(2000);
}