#include <NewPing.h>

const int L_MOTOR_FORWARD = 3;
const int L_MOTOR_BACKWARD = 4;
const int R_MOTOR_FORWARD = 5;
const int R_MOTOR_BACKWARD = 6;
const int MOTOR_ENABLE = 7;

const int IR_Right = 0;
const int IR_Mid = 1;
const int IR_Left = 2;

const int Trig_Left = 13; 
const int Echo_Left = 12;
const int Trig_Middle = 11;
const int Echo_Middle = 10;
const int Trig_Right = 9;
const int Echo_Right = 8;

NewPing sonarSensorLeft(Trig_Left, Echo_Left, 200);
NewPing sonarSensorMiddle(Trig_Middle, Echo_Middle, 200);
NewPing sonarSensorRight(Trig_Right, Echo_Right, 200);


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




class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class Tree {
public:
Tree*root;

}

void setup() {
  Serial.begin(9600);

  // Pin Setup
  pinMode (L_MOTOR_FORWARD, OUTPUT);
  pinMode (L_MOTOR_BACKWARD, OUTPUT);
  pinMode (R_MOTOR_FORWARD, OUTPUT);
  pinMode (R_MOTOR_BACKWARD, OUTPUT);
  pinMode (MOTOR_ENABLE, OUTPUT);
  pinMode (IR_Right, INPUT);
  pinMode (IR_Mid, INPUT);
  pinMode (IR_Left, INPUT);

  stopMoving();
  delay(5000);
  }


void loop() {
  int status_Left = digitalRead(IR_Left);
  int status_Mid = digitalRead(IR_Mid);
  int status_Right = digitalRead(IR_Right);

  if ((status_Left == 0 && status_Right == 0) || status_Mid == 1) {
    moveForward();
  }

  if else (status_Left == 0 && status_Right == 1 && status_mid == 0) {
    moveLeft();
  }

  if else (status_Left == 1 && status_Right == 0 && status_mid == 0) {
    moveRight();
  }

  else {moveForward} // there is an intersection bc it is reading 3 lines



  


  int previous_L = status_Left;
  int previous_M = status_Mid;
  int previous_R = status_Right;

}

