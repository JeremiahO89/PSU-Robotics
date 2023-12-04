#include <NewPing.h>

// Pin Inputs
const int L_MOTOR_FORWARD = 3;
const int L_MOTOR_BACKWARD = 4;
const int R_MOTOR_FORWARD = 5;
const int R_MOTOR_BACKWARD = 6;
const int IR_Right = 2;
const int IR_Left = 9;
const int IR_Turn = 8;
const int Trig_Left = 13; 
const int Echo_Left = 12;
const int Trig_Middle = 11;
const int Echo_Middle = 10;

NewPing sonarLeft(Trig_Left, Echo_Left, 50);
NewPing sonarMiddle(Trig_Middle, Echo_Middle, 100);

// Constant variables
const int wall_dist = 20;
const int NINE_DEG = 125;
const int ONE_EIGHT_DEG = 300;

int status_Left = 0;
int status_Right = 0;
int status_Turn = 0;

int distance_Left = 0;
int distance_Middle = 0;
int right_check = 0;

// motor positions
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
  digitalWrite(L_MOTOR_FORWARD, LOW);
  digitalWrite(L_MOTOR_BACKWARD, HIGH);
  digitalWrite(R_MOTOR_FORWARD, HIGH);
  digitalWrite(R_MOTOR_BACKWARD, LOW);
}
void turnLeft(){
  digitalWrite(L_MOTOR_FORWARD, HIGH);
  digitalWrite(L_MOTOR_BACKWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, HIGH);
}
void spinOut(){
  digitalWrite(L_MOTOR_FORWARD, HIGH);
  digitalWrite(L_MOTOR_BACKWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, LOW);
  digitalWrite(R_MOTOR_BACKWARD, HIGH);
  delay(1000000000000);
}

void IR_get_data(){
  status_Left = digitalRead(IR_Left);
  status_Right = digitalRead(IR_Right);
  status_Turn = digitalRead(IR_Turn);
}

void setup() {
  //Serial.begin(9600);
  // Pin Setup
  pinMode (L_MOTOR_FORWARD, OUTPUT);
  pinMode (L_MOTOR_BACKWARD, OUTPUT);
  pinMode (R_MOTOR_FORWARD, OUTPUT);
  pinMode (R_MOTOR_BACKWARD, OUTPUT);
  pinMode (IR_Right, INPUT);
  pinMode (IR_Left, INPUT);
  pinMode (IR_Turn, INPUT);

// 5 second pause
  stopMoving();
  delay(5000);
 
  }


int timer = 0;

void loop() {

  IR_get_data();

  if (timer % 300 == 0){
  distance_Left = (sonarLeft.ping_cm());
  distance_Middle = (sonarMiddle.ping_cm());}
  //Serial.println(distance_Middle);
  
  // turn 180 no more path
  if (((distance_Middle <= 25) && (distance_Middle > 0)) && ((distance_Left < 15) && (distance_Left > 0))) {
    //spinOut();
    // turn the first 90
    turnLeft(); 
    delay(340);
    moveForward;
    delay(100);
    stopMoving();
    delay(500);
    right_check = (sonarLeft.ping_cm());
    if ((right_check >= 12 || right_check == 0)) {
      turnLeft(); 
      delay(200);
      stopMoving();
      delay(500);
    }
  }

  // Turn 90deg left   there is an open path
  else if (status_Turn == 1 && (distance_Left >= 15 || distance_Left == 0)) {
    //spinOut();
    // turn the first 90
    turnLeft(); 
    delay(100);
    stopMoving();
    delay(500);
  }

  // Drive on the Line
  // Center to the right 
  
    else if (status_Left == 0 && status_Right == 1 && status_Turn == 0) {
    turnRight();
    delay(2);
    stopMoving();
    delay(.25);
    }
// center to the left
  else if (status_Left == 1 && status_Right == 0 && status_Turn == 0) {
    turnLeft(); 
    delay(2);
    stopMoving();
    delay(.25);
    }
  
  // else drive forwards
  else if (((status_Left == 0 && status_Right == 0) || (status_Left == 1 && status_Right == 1)) && (distance_Middle >= 10 || distance_Middle < 4) && (status_Turn == 0 || distance_Left < 15)){
    
      moveForward(); 
      delay(5);
      stopMoving();
      delay(.25);

    if (status_Turn == 1 && distance_Left < 15){
      moveForward(); 
      delay(5);
      stopMoving();
      delay(.25);

    }
  }
  else {
    turnLeft(); 
    delay(40);
    stopMoving();
    delay(500);
  }
}
