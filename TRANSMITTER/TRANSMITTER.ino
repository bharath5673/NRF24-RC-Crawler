#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10); // CE, CSN

#define LED A2

//const byte address[6] = "00001";
const uint64_t address = 0xe7e7e7e7e7;
char xyData[32] = "";
int joystick[2];
//int  xAxis, yAxis;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);  
  radio.stopListening();
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

//  for (int i=0;i<5;i++) 
//  {
//  digitalWrite(LED,10);  // flash led
//  delay(30);
//  digitalWrite(LED,0);
//  delay(30);    
//  } 

}


void loop() {
  
  joystick[0] = analogRead(A4);
  joystick[1] = analogRead(A3);
  
  radio.write( joystick, sizeof(joystick) );

//    Serial.println(joystick[0]);
//    Serial.println(joystick[1]);
    Serial.print("X = "),Serial.print(joystick[0]),Serial.print("  Y = "),Serial.print(joystick[1]);
    Serial.println(" ");
    

}
