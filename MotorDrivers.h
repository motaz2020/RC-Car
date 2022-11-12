#define MD

//Movement Functions
void Right(byte speed, byte angle) {
  bool q=angle>45;
  byte s=q?map(angle, 45, 90, 255, 255-speed):map(angle, 0, 45, speed, 0);
  analogWrite(LM1, speed);
  digitalWrite(LM2, 0);
  analogWrite(RM1, s);
  digitalWrite(RM2, q);
  #ifdef DEBUG
  Serial.println((String)"Right : (" +s+", "+ q+")");
  #endif
}
void Left(byte speed, byte angle) {
  bool q=angle>45;
  byte s=q?map(angle, 45, 90, 255, 255-speed):map(angle, 0, 45, speed, 0);
  analogWrite(RM1, speed);
  digitalWrite(RM2, 0);
  analogWrite(LM1, s);
  digitalWrite(LM2, q);
  #ifdef DEBUG
  Serial.println((String)"Left : (" +s+", "+ q+")");
  #endif
}
void Forward(byte speed){
  analogWrite(LM1, speed);
  digitalWrite(LM2, 0);
  analogWrite(RM1, speed);
  digitalWrite(RM2, 0);
  #ifdef DEBUG
  Serial.println((String)"Forward : "+speed);
  #endif
}
void Backward(byte speed){
  analogWrite(LM1, 255-speed);
  digitalWrite(LM2, 1);
  analogWrite(RM1, 255-speed);
  digitalWrite(RM2, 1);
  #ifdef DEBUG
  Serial.println((String)"Backward : "+speed);
  #endif
}
void Stop(){
  analogWrite(LM1, 0);
  digitalWrite(LM2, 0);
  analogWrite(RM1, 0);
  digitalWrite(RM2, 0);
  #ifdef DEBUG
  Serial.println((String)"Backward : "+Speed);
  #endif
}
void TurnAround(){
  Left(Speed,90);
  delay(800);
  Stop();
  Forward(Speed);
  delay(300);
  Stop();
}
void Shot(byte DIR){
    Stop();
    Trigger.write(DIR?RED:Green);
    delay(500);
    Trigger.write(85);
    delay(500);
    Trigger.write(DIR?RED:Green);
    delay(500);
    Trigger.write(85);
    delay(500);
}
void testDrivers(){
  test=!test;
  while(test){
  for(int i=70;i<255;i+=4){
  Forward(i);
  delay(100);}
  Stop();
  delay(1000);
  for(int i=70;i<255;i+=4){
  Backward(i);
  delay(100);}
  Stop();
  delay(1000);
 // Right(Speed,90);
  //delay(2000);
 // Left(Speed,90);
//  delay(2000);
}
}
