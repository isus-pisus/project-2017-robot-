#include <Servo.h>

#include <AFMotor.h>

#include <Ultrasonic.h>

AF_DCMotor right(1);
AF_DCMotor left(2);

Servo s1, s2, s3;

Ultrasonic ultra1(25, 26), ultra2(27, 28);

int relay[] = {29, 30, 31, 32, 33};

int code [5];

int motorPin1 = 34;  
int motorPin2 = 35;    
int motorPin3 = 36;   
int motorPin4 = 37;    

int counter = 0;
int pass = 0;
int motorSpeed = 1200;  
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int magnet;

void stage1(), stage2(), stage3(), stage4();

void setup() {

  s1.attach(22);
  s2.attach(23);
  s3.attach(24);

  pinMode(relay[0], OUTPUT); // brown
  pinMode(relay[1], OUTPUT); //red
  pinMode(relay[2], OUTPUT); //orange
  pinMode(relay[3], OUTPUT); //yellow
  pinMode(relay[4], OUTPUT); //purple

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
}

void loop() {

 stage1();
 stage3();
 stage2();
 stage4();
 
   

      
         
}

void forwardfast()
{
  right.run(FORWARD);
  left.run(FORWARD);
  right.setSpeed(200);
  left.setSpeed(200);
  }

void forwardslow()
{
  right.run(FORWARD);
  left.run(FORWARD);
  right.setSpeed(90);
  left.setSpeed(90);
  
  }  

void rotate()
{
  right.run(FORWARD);
  left.run(BACKWARD);
  right.setSpeed(140);
  left.setSpeed(140);
  }


void pause()
{
  right.run(RELEASE);
  left.run(RELEASE);
  right.setSpeed(0);
  left.setSpeed(0);
  }


void servo_home()
{
  s1.write(10);
  s2.write(90);
  s3.write(90);
  }

void cubeostion()
{
  s1.write(90);
  s2.write(70);
  s3.write(90);
  }

void servo_position1()
{
  s1.write(60);
  s2.write(110);
  s3.write(90);
  }

void servo_position2()
{
  s1.write(30);
  s2.write(135);
  s3.write(90);
  }

void servo_position3()
{
  s1.write(60);
  s2.write(110);
  s3.write(90);
} 

  
  int determine (int i) {
    
  //pre determined values based on input voltages 
  int wire = 0;
  int diode_rb = 850;
  int diode_fb = 50;
  int capacitor = 739;
  int inductor = 300;
  int resistor = 600;
  
  // set component code values
  const int wire_value = 1;
  const int resistor_code = 2;
  const int capacitor_code = 3;
  const int inductor_code = 4;
  const int diode_code = 5;

  
  Serial.write("reading ");
  delay(1000);
  int sensorvalue = analogRead(A8);
  
   //wire
   if (sensorvalue < (wire + 5)) {
    Serial.println("wire ");
    return 1;
    
   }
  //resistor 
  if ( sensorvalue > (resistor - 50) && sensorvalue < (resistor + 50)) {
    Serial.println("resistor ");
    return 2;
    
   }
  //capacitor
  if ( sensorvalue > (capacitor - 70) && sensorvalue < (capacitor + 70)) {
    Serial.println("capacitor ");
    return 3;
   }
   
  //inductor
   if ( sensorvalue > (inductor - 60) && sensorvalue < (inductor + 60)) {
    Serial.println("inductor ");
    return 4;
   }
  
    //diode reverse biased
   if ( sensorvalue > (diode_rb - 10) ) {
    Serial.println("diode reverse biased ");
    return 5;
   }

  //diode biased
   if ( sensorvalue > (diode_fb - 20) && sensorvalue < (diode_fb + 20)) {
    Serial.println("diode forward biased ");
    return 5;
   }
  }

void stage1(){

  do{
    forwardfast();
    } while(ultra1.Ranging(CM) == 5);

    pause();
    servo_position1();
    
    do{
      forwardslow();
      }while(ultra1.Ranging(CM) == 3);

      pause();
      for (int i = 0; i<=4; i++){
        
        digitalWrite(relay[i], HIGH);
        code[i] = determine(i);
        digitalWrite(relay[i], LOW);   
        delay(1000);  
      } 
}


void stage3(){
  
  
   rotate();
   delay(4000);

  do{
    forwardfast();
    } while(ultra1.Ranging(CM) == 5);

    pause();
    servo_position3();

    do{
      forwardslow();
      }while(ultra1.Ranging(CM) == 3);

      pause();
       for (int i=0; i<=4; i++) {
    switch (i) {
      case 0:
        Serial.println("case 1");
        while (counter<(512*code[i])) {
          counter++;
          turn_clockwise(code[i]);
          if (counter>=(512*code[i])) {
            counter = 0;
            break;
          }
        }
        break;
        
      case 1:
        Serial.println("case 2");
        while (counter <= (512*code[i])) {
          counter++;
          
          turn_anticlockwise(code[i]);
          if (counter == (511*code[i]) ) {
            counter = 0;
            break;
          }  
        }
        break;
        
      case 2:
      Serial.println("case 3");
        while (counter<=(512*code[i])) {
          counter++;
          //Serial.println(counter);
          turn_clockwise(code[i]);
          if (counter==(512*code[i])) {
            counter = 0;
            break;
          }
        }
        break;
        
      case 3:
        Serial.println("case 4");
        while (counter <= (512*code[i])) {
          counter++;
          //Serial.println(counter);
          turn_anticlockwise(code[i]);
          if (counter >= (512*code[i]) ) {
            counter = 0;
            break;
          }  
        }
        break;
      case 4:
        Serial.println("case 5");
        while (counter<(512*code[i])) {
          counter++;
          turn_clockwise(code[i]);
          if (counter>=(512*code[i])) {
            counter = 0;
            break;
          }
        }
        break;
      
      default: 
        // if nothing else matches, do the default
        // default is optional
      break;
    }
}
}

int turn_clockwise (int clockwise_turns) {
      
     if(count < countsperrev * clockwise_turns)
      clockwise();
    count++;
    return count;
}

int turn_anticlockwise (int anticlockwise_turns) {
  count = 0;
  if(count < countsperrev * anticlockwise_turns)
    anticlockwise();
  count++;
  return count;
}


void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}


void stage2(){
  rotate();
   delay(4000);

   forwardfast();
   delay(2700);

   pause();
   delay(2000);
   rotate();
   delay(2700);

  do{
    forwardfast();
    } while(ultra1.Ranging(CM) == 5);

    pause();
    servo_position2();

    do{
      forwardslow();
      }while(ultra1.Ranging(CM) == 3);

      pause();


      for (int t=1; t<5; t++)
      {
        
        while(magnet == LOW)
        {};

        
      if (magnet == HIGH)
      {
     
        s3.write(135);
        
        for (int s = 135; s>90; s++)
        {
          s3.write(s);
          delay(800);
          }

         s3.write(135);
         
        }
      }
  
  }


void  stage4(){
  rotate();
   delay(4000);

  do{
    forwardfast();
    } while(ultra1.Ranging(CM) == 5);

    pause();
    servo_home();

    do{
      forwardslow();
      }while(ultra1.Ranging(CM) == 3);

      pause();
  }
