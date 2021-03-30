/*       
 *        Arduino Car NRF24L01
 *        
 *        ForbiddenBit.com
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
#define in1 3
#define in2 4
#define enA 5 
#define enB 6   
#define in3 7
#define in4 8

RF24 radio(9,10); // CE, CSN
//const byte address[6] = "00001";
const uint64_t address = 0xe7e7e7e7e7;
char receivedData[32] = "";
int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
int joystick[2]; 

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
void loop() {

  if (radio.available()) {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );

    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = joystick[1];
    
//    Serial.println(yAxis);
//    Serial.println(xAxis);

//    Serial.print("X = "),Serial.print(analogRead(xAxis)),Serial.print("  Y = "),Serial.print(analogRead(yAxis));
    Serial.print("X = "),Serial.print(xAxis),Serial.print("  Y = "),Serial.print(yAxis);
    Serial.println(" ");
  }

  
  if (yAxis < 370) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    motorSpeedA = map(yAxis, 370, 0, 0, 255);
    Serial.println("moving backward");
    

  }
  else if (yAxis > 750) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);    
    motorSpeedA = map(yAxis, 750, 1023, 0, 255);
    Serial.println("moving forward");
  }

  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  if (xAxis < 470) {

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
    Serial.println("turning left");
    
  }
  
  if (xAxis > 550) {

    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255); 
    Serial.println("turning right");   
    
  }

  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
}
