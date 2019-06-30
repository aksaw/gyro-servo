#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <Servo.h>

#define SERVO_PIN 9
Servo myservo;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  myservo.attach(SERVO_PIN);  
  myservo.write(0);   
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
}

void loop() {
  if (radio.available()) {
    float ypr2 = 0;
    radio.read(&ypr2, sizeof(float));
    Serial.println(ypr2);
    myservo.write(180-(90+ ypr2 * 180/M_PI));   
  }
}
