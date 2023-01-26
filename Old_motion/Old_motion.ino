 #include <Wire.h>
#include "Servo.h"
//5,10,12,14,2,4,6,8

//
#define pinA 13
#define pinB 9
#define pinC 5
#define pinD 11
#define pinE 3
#define pinF 7

/*
yellow: E
green : C
blue  : F
purple: B
before last: D
last: A
*/

#define led_pin 13
#define grip_pin 33

int i = 0;
String ToSendSerially = "";
char c;

Servo A, B, C, D, E, F;
#define MAX_BUF 128
char buffer[MAX_BUF];

int motorvalA = 1500, motorvalB = 1500, motorvalC = 1500, motorvalD = 1500, motorvalE = 1500, motorvalF = 1500;
//int flyA, flyB, flyC, flyD, flyF, flyD;
int led = 0, gripper = 0;

void setup(void) 
{
  Serial.begin(57600);
    init_thrusters();
    //E.attach(pinE);
   //F.attach(pinF);
    pinMode(grip_pin, OUTPUT);
    pinMode(led_pin, OUTPUT);
    
//A.attach(pinA);
//A.writeMicroseconds (1500);
//delay(3000);
}




void loop(void) 
{
  read_from_ros(); 
  
}


void read_from_ros()
{
    while (Serial.available())
    {      
      c = Serial.read();

      if (i< MAX_BUF -1)
      buffer[i++] = c;
      else break;
             
      
      if (c == 'Z')
      {
        ToSendSerially = String(buffer);
        Serial.print(ToSendSerially);
        i=0;          
        motor_values(buffer);
        moveROV();
      }
       
    }
}



/*f - ecrc  
b - 
d - */

void init_thrusters()
{
   A.attach(pinA);
   B.attach(pinB);
   C.attach(pinC);
   D.attach(pinD);
   E.attach(pinE);
   F.attach(pinF);
   
   A.writeMicroseconds(1500);
   B.writeMicroseconds(1500);
   C.writeMicroseconds(1500);
   D.writeMicroseconds(1500);
   E.writeMicroseconds(1500);
   F.writeMicroseconds(1500);
   //delay(1000);      
   //pinMode(grip_pin, OUTPUT);
  //END OF THRUSTERS
}

void motor_values(String inp)  //  this void required to separate the string data into motor values
{
  motorvalA = (inp.substring(inp.indexOf('A') + 1, inp.indexOf('B'))).toInt(); 
  motorvalB = (inp.substring(inp.indexOf('B') + 1, inp.indexOf('C'))).toInt(); 
  motorvalC = (inp.substring(inp.indexOf('C') + 1, inp.indexOf('D'))).toInt();
  motorvalD = (inp.substring(inp.indexOf('D') + 1, inp.indexOf('E'))).toInt();
  motorvalE = (inp.substring(inp.indexOf('E') + 1, inp.indexOf('F'))).toInt();
  motorvalF = (inp.substring(inp.indexOf('F') + 1, inp.indexOf('G'))).toInt();
  gripper   = (inp.substring(inp.indexOf('G') + 1, inp.indexOf('L'))).toInt();
  led       = (inp.substring(inp.indexOf('L') + 1, inp.indexOf('Z'))).toInt();
  
  }

void moveROV()
{
  if(motorvalA > 1900 || motorvalA < 1100)
      motorvalA = 1500;
  if(motorvalB > 1900 || motorvalB < 1100)
      motorvalB = 1500;
  if(motorvalC > 1900 || motorvalC < 1100)
      motorvalC = 1500;
  if(motorvalD > 1900 || motorvalD < 1100)
      motorvalD = 1500;
  if(motorvalE > 1900 || motorvalE < 1100)
      motorvalE = 1500;
  if(motorvalF > 1900 || motorvalF < 1100)
      motorvalF = 1500;
      
  A.writeMicroseconds (motorvalA);
  B.writeMicroseconds (motorvalB);
  C.writeMicroseconds (motorvalC);
  D.writeMicroseconds (motorvalD);
  E.writeMicroseconds (motorvalE);
  F.writeMicroseconds (motorvalF);
  
  digitalWrite(led_pin, LOW);
  digitalWrite(grip_pin, LOW);
}
