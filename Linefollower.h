#ifndef MD
#include "MotorDrivers.h"
#endif

byte ReadColor() {
  tcs.getRawData(&r, &g, &b, &c);

  int sum = r + g + b;
  if ((r - g) > 0.1 * sum && (r - b) > 0.1 * sum) {

#ifdef DEBUG
    Serial.println("RED");
    bluetooth.println("RED");
#endif
    return 1;
  } else if ((b - g) > 0.1 * sum && (b - r) > 0.1 * sum) {
#ifdef DEBUG
    Serial.println("Blue");
    bluetooth.println("Blue");
#endif
  } else if ((g - r) > 0.1 * sum && (g - b) > 0.1 * sum) {
#ifdef DEBUG
    Serial.println("Green");
    bluetooth.println("Green");
#endif
    return 0;
  } else if ((r - b) > 0.15 * sum) {

#ifdef DEBUG
    Serial.println("yellow");
    bluetooth.println("yellow");
#endif
    return 2;
  } else {
    Serial.println("No Color");
  }
  return 99;
}
void ReadSensors() {
  Line[0] = digitalRead(LIR);
  Line[1] = digitalRead(MIR);
  Line[2] = digitalRead(RIR);
#ifdef DEBUGall
  Serial.print("Left Sensor: ");
  Serial.print(Line[0]);
  Serial.print(" - Mid Sensor: ");
  Serial.print(Line[1]);
  Serial.print(" - Right Sensor: ");
  Serial.println(Line[2]);
  bluetooth.print("Left Sensor: ");
  bluetooth.print(Line[0]);
  bluetooth.print(" - Mid Sensor: ");
  bluetooth.print(Line[1]);
  bluetooth.print(" - Right Sensor: ");
  bluetooth.println(Line[2]);
#endif
}
int ReadDistance() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = pulseIn(echo, HIGH) * 0.034 / 2;
  return distance;
#ifdef DEBUG
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
#endif
}
byte TrackLine() {
  ReadSensors();
  if ((Line[0]) && (!Line[1]) && (!Line[2])) //left
    Left(Speed, 45);
  else if ((!Line[0]) && (Line[1]) && (!Line[2])) //mid
    Forward(Speed);
  else if (!Line[0] && (!Line[1]) && (Line[2])) //right
    Right(Speed, 45);
  else if (Line[0] && (Line[1]) && (!Line[2])) { //mid left
    Left(Speed, 90);
    delay(400);
    section = (section == 0) ? 2 : section;

#ifdef DEBUG
    bluetooth.println("hard Left");
#endif
    return 0;
  }
  else if (!Line[0] && (Line[1]) && (Line[2])) { //mid right
    Right(Speed, 90);
    delay(400);
    section = (section == 0) ? 1 : section;

#ifdef DEBUG
    bluetooth.println("hard Right");
#endif
    return 0;
  }
  else if (!Line[0] && (!Line[1]) && (!Line[2])) //all
  {}
  else { //ALL BLACK
    Stop();
    return 0;
  }
  return 1;
}
byte findBasket(byte DIR) { // A routine To find The basket after Entering the square
  byte found = 0;

  while (TrackLine() && color > 1) {
    color = ReadColor();
  }
  unsigned long startTime = millis();
  while (((millis() - startTime) < 300) && !found && color > 1) {
    color = ReadColor();
  }
  Stop();
  if (color < 2) {
    found = ReadDistance() < (DIR ? 80 : 100);
    startTime = millis();
    while (((millis() - startTime) < 1000) && !found) {
      Left(Speed - 40, 90);
      found = ReadDistance() < (DIR ? 80 : 100);
    }
    Stop();
    startTime = millis();
    while (((millis() - startTime) < 1000) && !found) {
      Right(Speed - 40, 90);
      found = ReadDistance() < (DIR ? 80 : 100);
    }
    Stop();
  }
  return found;
}
void sendUnlockRequest() {
  //TODO: Connect to the gate
  bluetooth.begin(9600);
  bluetooth.write("O");
#ifndef DEBUG
  bluetooth.end();
#endif
}
