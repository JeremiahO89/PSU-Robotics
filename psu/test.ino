#include <NewPing.h>

const int L_MOTOR_FORWARD = 3;
const int L_MOTOR_BACKWARD = 4;
const int R_MOTOR_FORWARD = 5;
const int R_MOTOR_BACKWARD = 6;

const int IR_Right = 2;
const int IR_Mid = 8;
const int IR_Left = 9;

const int Trig_Left = 13; 
const int Echo_Left = 12;
const int Trig_Middle = 11;
const int Echo_Middle = 10;
const int Trig_Right = 1;
const int Echo_Right = 0;

NewPing sonarLeft(Trig_Left, Echo_Left, 200);
NewPing sonarMiddle(Trig_Middle, Echo_Middle, 200);
NewPing sonarRight(Trig_Right, Echo_Right, 200);


void stopMoving(){
  digitalWrite(L_MOTOR_FORWARD, LOW);
  digitalWrite(L_MOTOR_BACKWARD, LOW);

  digitalWrite(R_MOTOR_FORWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, LOW);
}
void moveForward(){
  digitalWrite(L_MOTOR_FORWARD, HIGH);
  digitalWrite(L_MOTOR_BACKWARD, LOW);

  digitalWrite(R_MOTOR_FORWARD, HIGH);
  digitalWrite(R_MOTOR_BACKWARD, LOW);
}
void moveBackward(){
  digitalWrite(L_MOTOR_FORWARD, LOW);
  digitalWrite(L_MOTOR_BACKWARD, HIGH);

  digitalWrite(R_MOTOR_FORWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, HIGH);
}
void turnRight(){
  digitalWrite(L_MOTOR_FORWARD, HIGH);
  digitalWrite(L_MOTOR_BACKWARD, LOW);

  digitalWrite(R_MOTOR_FORWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, HIGH);
}
void turnLeft(){
  digitalWrite(L_MOTOR_FORWARD, LOW);
  digitalWrite(L_MOTOR_BACKWARD, HIGH);

  digitalWrite(R_MOTOR_BACKWARD, HIGH);
  digitalWrite(L_MOTOR_BACKWARD, LOW);
}



const int wall_dist = 20;
const int NINE_DEG = 2000;
const int ONE_EIGHT_DEG = 4000;

int status_Left = 0;
int status_Mid = 0;
int status_Right = 0;

int distance_Left = 0;
int distance_Middle = 0;
int distance_Right = 0;

void setup() {
  Serial.begin(9600);

  // Pin Setup
  pinMode (L_MOTOR_FORWARD, OUTPUT);
  pinMode (L_MOTOR_BACKWARD, OUTPUT);
  pinMode (R_MOTOR_FORWARD, OUTPUT);
  pinMode (R_MOTOR_BACKWARD, OUTPUT);
  pinMode (IR_Right, INPUT);
  pinMode (IR_Mid, INPUT);
  pinMode (IR_Left, INPUT);

  pinMode (7, OUTPUT);
  digitalWrite(7, HIGH);  

  stopMoving();
  delay(5000);
  digitalWrite(7, LOW); 
  }


void loop() {
  status_Left = digitalRead(IR_Left);
  status_Mid = digitalRead(IR_Mid);
  status_Right = digitalRead(IR_Right);

  
  Serial.println(status_Left);
  Serial.println(status_Mid);
  Serial.println(status_Right);

  distance_Left = sonarLeft.ping_cm();
  distance_Middle = sonarMiddle.ping_cm();
  distance_Right = sonarRight.ping_cm();

  Serial.println("Left" + String(distance_Left));
  Serial.println("Middle" + String(distance_Middle));
  Serial.println("Right" + String(distance_Right));
  

  pinMode(7, LOW);
  delay(100); // update frequency (if to jittery increase)
  pinMode(7,HIGH);
}

