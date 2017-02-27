#include <Servo.h>
Servo myservo;

void setup() {
  Serial.begin(9600);
  }

void loop() {
  //section that records the position of the servo
  Serial.println("Recording"); 
  delay(5000);
  int num [200]; //aray that stores positions
  for (int n=1; n< 20; n++) // n in the for loop controls the number of postions stored
    {
    int pos = analogRead(A0);  //reads positions 
    num[n]= (pos - 111)/1.9723; // coonvertsthe feedback into values between 0-180
    Serial.print(n);
    delay(500); // increase or decresing the delay can make the rotation of the servo smoother
    }

 //section that plays back the positions 
 Serial.println("Playback");
  delay(5000);
  myservo.attach(8); //attaches servo to pin 8
  for (int m=1; m<20; m++) // m controls number of positions played
    {
      myservo.write(num[m]);
      delay(500); //delay controls rotation speed
    }
  myservo.detach(); //dettach servo, this is important so that the servo can record aagin after. you cant move the servo while its attach it will resist movement
    
}
