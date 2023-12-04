
#include <NewPing.h>

const int L_MOTOR_FORWARD = 3;
const int L_MOTOR_BACKWARD = 4;
const int R_MOTOR_FORWARD = 5;
const int R_MOTOR_BACKWARD = 6;

const int IR_Right = 2;
// const int IR_Mid = 8;
const int IR_Left = 9;

const int Trig_Left = 13; 
const int Echo_Left = 12;
const int Trig_Middle = 11;
const int Echo_Middle = 10;
// const int Trig_Right = 0;
// const int Echo_Right = 1;

NewPing sonarLeft(Trig_Left, Echo_Left, 100);
NewPing sonarMiddle(Trig_Middle, Echo_Middle, 100);
// NewPing sonarRight(Trig_Right, Echo_Right, 100);


const int wall_dist = 20;
const int NINE_DEG = 2000;
const int ONE_EIGHT_DEG = 4000;

int status_Left = 0;
// int status_Mid = 0;
int status_Right = 0;

int distance_Left = 0;
int distance_Middle = 0;
// int distance_Right = 0;


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

void IR_get_data(){
  status_Left = digitalRead(IR_Left);
  //status_Mid = digitalRead(IR_Mid);
  status_Right = digitalRead(IR_Right);
  Serial.println("Left: " + String(distance_Left) + "   Middle: " + String(distance_Middle));
}

void turn180(){
  turnLeft();
  delay(ONE_EIGHT_DEG);
  stopMoving();
}

void turn90(){
  turnLeft();
  delay(NINE_DEG);
  stopMoving();
}



void setup() {
  Serial.begin(9600);

  // Pin Setup
  pinMode (L_MOTOR_FORWARD, OUTPUT);
  pinMode (L_MOTOR_BACKWARD, OUTPUT);
  pinMode (R_MOTOR_FORWARD, OUTPUT);
  pinMode (R_MOTOR_BACKWARD, OUTPUT);
  pinMode (IR_Right, INPUT);
  // pinMode (IR_Mid, INPUT);
  pinMode (IR_Left, INPUT);

  pinMode (7, OUTPUT);
  digitalWrite(7, LOW);  

  stopMoving();
  delay(5000);
  digitalWrite(7, HIGH); 
  }


void loop() {
  IR_get_data();

  distance_Left = (sonarLeft.ping_cm());
  distance_Middle = (sonarMiddle.ping_cm());
  //distance_Right = (sonarRight.ping() / 58);

  //Serial.println("IR_L: " + String(status_Left) + "   IR_M: " + String(status_Mid) + "   IR_R:" + String(status_Right));

  // if ((distance_Middle < 4) && (distance_Middle > 2)) {
  //   digitalWrite(7, LOW);  
  //   delay(10);
  //   distance_Middle = (sonarMiddle.ping() / 58);
  //   if ((distance_Middle < 4) && (distance_Middle > 2)){
  //     stopMoving();
  //     delay(5000);}
  //   digitalWrite(7, HIGH);  
  // }


  if (((distance_Middle < 4) && (distance_Middle > 2)) && ((distance_Left < 5) && (distance_Left >20))) {
    turn180();
    while (status_Left != 0 && status_Right != 0){
    IR_get_data();
    turnLeft(); 
    delay(.5);
    stopMoving();
    delay(.25);
    }

  }

  // Turn 90deg left   there is an open path
  else if ((distance_Left < 5) && (distance_Left >2)) {
    turn90();
    while (status_Left != 0 && status_Right != 0){
    IR_get_data();
    turnLeft(); 
    delay(.5);
    stopMoving();
    delay(.25);
    }
  }


  // Drive on the Line
  if (status_Left == 0 && status_Right == 1) {
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

  else if (status_Left == 1 && status_Right == 1) {
    while (status_Left == 1 && status_Right == 1){
    IR_get_data();
    turnLeft(); 
    delay(.5);
    stopMoving();
    delay(.25);
    }
  }
  else{
    while (status_Left == 0 && status_Right == 0){
    IR_get_data();
    moveForward(); 
    delay(.5);
    stopMoving();
    delay(.25);
    }
  }


}

