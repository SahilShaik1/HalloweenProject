#include <Servo.h>

#define holderAPin 6
#define holderBPin 8
#define leftFingerPin 7
#define middleFingerPin 10
#define rightFingerPin 5
#define trigPin 13
#define echoPin 12
#define soundPin 2
#define lightPin 3
Servo holderA;
Servo holderB;
Servo leftFinger;
Servo middleFinger;
Servo rightFinger;

long baseDist;
void setup() {
  // put your setup code here, to run once:
  leftFinger.attach(leftFingerPin);
  middleFinger.attach(middleFingerPin);
  rightFinger.attach(rightFingerPin);
  leftFinger.write(0);
  rightFinger.write(0);
  middleFinger.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(soundPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  Serial.begin(9600);
  baseDist = GetDist();
  Serial.println(baseDist);
  delay(20);
}
 


void loop() {
  // put your main code here, to run repeatedly:
  long dist = GetDist();
  Serial.println(dist);
  if(baseDist > (5 * dist)){
    //Initiate Sequence
    ScareSequence();
  }

}

void ScareSequence(){
  for(int i = 0; i < 180; i++){
    if(i%2==0){
      digitalWrite(soundPin, HIGH);
      digitalWrite(lightPin, HIGH);
    } else {
      digitalWrite(soundPin, LOW);
      digitalWrite(lightPin, LOW);
    }
    leftFinger.write(i);
    middleFinger.write(i);
    rightFinger.write(i);
    
    delay(20);
  }
  for(int i = 180; i >0; i--){
    if(i%2==0){
      digitalWrite(soundPin, HIGH);
      digitalWrite(lightPin, HIGH);
    } else {
      digitalWrite(soundPin, LOW);
      digitalWrite(lightPin, LOW);
    }
    leftFinger.write(i);
    middleFinger.write(i);
    rightFinger.write(i);
    delay(20);
  }
}

long GetDist(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  double pulse_width = pulseIn(echoPin, HIGH);
  double distance = (pulse_width * 0.343) / 2;
  delay(500);
  return distance;
}
