
#include <Servo.h>

// micro servo
Servo ms;
byte servoP = 2;
int pos = 0;

// ultrasonic
byte trigP = 7;
byte echoP = 6;

// buzzer
byte buzzerP = 5;

// rgb led
byte redP = 9; 
byte greenP = 10;
byte blueP = 11; 

void setup()
{
  Serial.begin(9600);
    
  ms.attach(servoP);

  pinMode(trigP, OUTPUT);
  pinMode(echoP, INPUT);
  
  pinMode(buzzerP, OUTPUT);

  pinMode(redP, OUTPUT);
  pinMode(greenP, OUTPUT);
  pinMode(blueP, OUTPUT);

}

void loop()
{     
  for (pos = 0; pos <= 180; pos ++) {
    ms.write(pos);
    delay(10);
    detect();
  }
  
  for (pos = 180; pos >= 0; pos --) {
    ms.write(pos);
    delay(10);
    detect();
  }
  delay(500); 
}

void detect(){

  digitalWrite(trigP, LOW);
  delayMicroseconds(2);
  digitalWrite(trigP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigP, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  long dur = pulseIn(echoP, HIGH);

  // Convert the time into a distance (cm)
  long distcm = (dur/2)/29.1;

  if(distcm < 10){
    tone(buzzerP, 440, 300);
    analogWrite(redP, 255);
    analogWrite(greenP, 0);
    analogWrite(blueP, 0);

  }

   else if(distcm >= 10 && distcm <= 30){
    noTone(buzzerP);
    analogWrite(redP, 0);
    analogWrite(greenP, 0);
    analogWrite(blueP, 255);
  }

  else {  
    noTone(buzzerP);
    analogWrite(redP, 0);
    analogWrite(greenP, 255);
    analogWrite(blueP, 0);
  }
  
  Serial.println(distcm);

}
