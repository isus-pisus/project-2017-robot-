#include <Servo.h>
Servo servo1;

void setup() {
  Serial.begin(9600);
  }

void loop() {
  Serial.println("Recording"); 
  delay(5000);
  int num [200];
  for (int n=1; n< 20; n++)
    {
    int pos = analogRead(A0);
    num[n]= (pos - 111)/1.9723;
    Serial.print(n);
    delay(500);
    }

 Serial.println("Playback");
  delay(5000);
  servo1.attach(8);
  for (int m=1; m<20; m++)
    {
      servo1.write(num[m]);
      delay(500);
    }
  servo1.detach();
    
}
