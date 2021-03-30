/*       
 *        Arduino Car NRF24L01
 *        
 *        ForbiddenBit.com
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
#define in1 4
#define in2 5  
#define in3 6
#define in4 7

#define LED A1

RF24 radio(9,10); // CE, CSN
//const byte address[6] = "00001";
const uint64_t address = 0xe7e7e7e7e7;


char receivedData[32] = "";
int  xAxis, yAxis;
int joystick[2]; 

void setup() {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(LED, HIGH);
   
}
void loop() {

  if (radio.available()) {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );




//      for (int i=0;i<5;i++) 
//      {
//       digitalWrite(LED,10);  // flash led
//       delay(30);
//       digitalWrite(LED,0);
//       delay(30);    
//      }  





    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = joystick[1];
    
//    Serial.println(yAxis);
//    Serial.println(xAxis);

//    Serial.print("X = "),Serial.print(analogRead(xAxis)),Serial.print("  Y = "),Serial.print(analogRead(yAxis));
//    Serial.print("X = "),Serial.print(xAxis),Serial.print("  Y = "),Serial.print(yAxis);
    Serial.println(" ");
    

  }
  
  if (xAxis < 500) {
    digitalWrite(in2, HIGH);
    Serial.println("turning left");
  }
  
  else if (xAxis > 600) {
    digitalWrite(in1, HIGH);
    Serial.println("turning right");
  }

  else if (yAxis < 500) {
    digitalWrite(in4, HIGH);
    Serial.println("moving down");
  }

  else if (yAxis > 600) {
    digitalWrite(in3, HIGH);
    Serial.println("moving up");
  }

  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    Serial.println("stoped..");

  }

}



    
