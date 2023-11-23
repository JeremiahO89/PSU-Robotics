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

NewPing sonarLeft(Trig_Left, Echo_Left, 100);
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

void leftLoop(){
    while (status_Left == 1 && status_Right == 0){
        IR_get_data();
        turnRight(); 
        delay(.5);
        stopMoving();
        delay(.25);
        }
}

void rightLoop(){
    while (status_Left == 0 && status_Right == 1){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);
        }
}

void IR_get_data(){
  status_Left = digitalRead(IR_Left);
  status_Right = digitalRead(IR_Right);
  status_Turn = digitalRead(IR_Turn);
}

void setup() {
  Serial.begin(19200);

  // Pin Setup
  pinMode (L_MOTOR_FORWARD, OUTPUT);
  pinMode (L_MOTOR_BACKWARD, OUTPUT);
  pinMode (R_MOTOR_FORWARD, OUTPUT);
  pinMode (R_MOTOR_BACKWARD, OUTPUT);
  pinMode (IR_Right, INPUT);
  pinMode (IR_Left, INPUT);
  pinMode (IR_Turn, INPUT);

// lights
  pinMode (7, OUTPUT);
  pinMode (1, OUTPUT);
  digitalWrite(7, LOW);  
  digitalWrite(1, LOW);  

// 5 second pause
  stopMoving();
  delay(5000);

// lights
  digitalWrite(7, HIGH); 
  digitalWrite(1, HIGH); 
  }

void loop() {
  IR_get_data();
  distance_Left = (sonarLeft.ping_cm());
  distance_Middle = (sonarMiddle.ping_cm());

  //Serial.println("Left: " + String(distance_Left) + "   Middle: " + String(distance_Middle));
  //Serial.println("IR_L: " + String(status_Left) + "   IR_R:" + String(status_Right));
  
  // turn 180 no more path
  if (((distance_Middle < 10) && (distance_Middle > 2)) && ((distance_Left < 10) && (distance_Left > 2))) {
    
    // turn the first 90
    while (status_Left == 0){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
    delay(250);
    //turn the over the line
    while (status_Left == 1){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
    delay(250);
    //turn the second 90 
    while (status_Left == 0){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
    delay(250);
    // center on the line
    while (status_Right == 0){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
  }

  // Turn 90deg left   there is an open path
  else if (status_Turn == 1 && distance_Left > 25) {
    // turn the first 90
    while (status_Left == 0){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
    
    delay(250);
    // center on the line
    while (status_Right == 0){
        IR_get_data();
        turnLeft(); 
        delay(.5);
        stopMoving();
        delay(.25);}
  }

  // Drive on the Line
  else if (status_Left == 0 && status_Right == 1) {
    while (status_Left == 0 && status_Right == 1) {
    IR_get_data();
    turnRight();
    delay(.5);
    stopMoving();
    delay(.25);
    }
  }
  else if (status_Left == 1 && status_Right == 0) {
    while (status_Left == 1 && status_Right == 0){
    IR_get_data();
    turnLeft(); 
    delay(.5);
    stopMoving();
    delay(.25);
    }
  }
  
  // else drive forwards
  else {
    int timer = 0;

    while (((status_Left == 0 && status_Right == 0) || (status_Left == 1 && status_Right == 1)) && status_Turn == 0 && distance_Middle > 5){
    
      // adds a delay between sonic pings
      if ((timer % 200) == 0){
        distance_Left = (sonarLeft.ping_cm());
        distance_Middle = (sonarLeft.ping_cm());}

      IR_get_data();
      moveForward(); 
      delay(.5);
      stopMoving();
      delay(.25);
      timer += 1;
    }
  }
}

