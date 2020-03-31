  
/*
The purpose of this code is to allow the Arduino to use with the robot JeepBot. 
Author: Magali Bardou
Created: 26 ‎april ‎2019
Licenced CC BY-NC-SA
Version 0.1
*/

#include "Motors.h"
#include "LineDetector.h"
 

// Ports numériques associés aux entrées de contrôle (les entrées PWM doivent être connectées à des ports PWM de l'Arduino)
#define PWMA 5
#define AIN2 A3
#define AIN1 A4
#define STBY A5
#define BIN1 A2
#define BIN2 A1
#define PWMB 3

#define RS 7
#define CS 8
#define LS 9

#define backRS 6
#define backLS 10

#define trigPin 11
#define echoPin 12
#define FrontLed A0
#define BackLed 4
 
// Initialisation des moteurs
Motors M(PWMA, AIN1, AIN2,
         PWMB, BIN1, BIN2,
         STBY);

// Lecture des capteurs (=0 --> noir, =1 --> blanc)
LineDetector LD(RS, CS, LS);
bool SumoProgram = true;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(FrontLed, OUTPUT);
  pinMode(BackLed, OUTPUT);
  digitalWrite(FrontLed, LOW);
  digitalWrite(BackLed, LOW);
  
  M.Start();
  delay(5000);
}
 
void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  
  if(digitalRead(backRS) == HIGH || digitalRead(backLS) == HIGH)
  {
    digitalWrite(FrontLed,LOW);
    digitalWrite(BackLed,HIGH); 
    Serial.println("Détection ligne, dégage de là !");
    M.Vitess(200, 200);
  }
  else if(digitalRead(RS) == HIGH || digitalRead(CS) == HIGH || digitalRead(LS) == HIGH)
  {
    digitalWrite(FrontLed,HIGH); 
    digitalWrite(BackLed,LOW);
    Serial.println("Détection ligne, dégage de là !");
    M.Vitess(-200, -200);
  }
  else if (distance < 30) 
  {  
    digitalWrite(FrontLed,HIGH);
    digitalWrite(BackLed,LOW); 
    Serial.println("Détection ennemi, bourre dedans !");
    M.Vitess(200, 200);
  }
  else 
  {
    M.Vitess(100, -50); 
    digitalWrite(FrontLed,LOW);
    digitalWrite(BackLed,LOW);
  }
}
