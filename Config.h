#define DEBUG
#define DEBUGall


//libraries

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>
#include <SoftwareSerial.h>

//Circuit Diagram:
//General
#define BT_RX 2
#define BT_TX 3
#define SW    4
//MOTORS
#define LM1   5
#define LM2   9
#define RM1   6
#define RM2   10

#define Trigger_Angle 60
#define RED 85-Trigger_Angle
#define Green 85+Trigger_Angle

//Sensors
#define LIR   A0
#define MIR   A1
#define RIR   A2
#define SDA   A4
#define SCL   A5
#define trig  A6
#define echo  A7

//Global Variables
byte Line[]={0,0,0};
byte Speed =120;
int distance=0;
bool test=0;
byte DistanceDet=10;
byte section=0;
byte color = 99;
byte ToShoot=99;
int r, g, b,c;


Servo Trigger;
SoftwareSerial bluetooth(12, 13);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_4X);
//Other Files
#include "Linefollower.h"


void ConfigPins() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(LIR,INPUT);
  pinMode(MIR,INPUT);
  pinMode(RIR,INPUT);
  
}
