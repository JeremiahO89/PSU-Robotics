#include <NewPing.h>


const int L_MOTOR_FORWARD = 3;
const int L_MOTOR_BACKWARD = 4;
const int R_MOTOR_FORWARD = 5;
const int R_MOTOR_BACKWARD = 6;
const int MOTOR_ENABLE = 7;

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

  // Drive on the Line
  if ((status_Left == 0 && status_Right == 0) || status_Mid == 1) {
    moveForward();
  }
  else if (status_Left == 0 && status_Right == 1 && status_Mid == 0) {
    turnLeft();
  }
  else if (status_Left == 1 && status_Right == 0 && status_Mid == 0) {
    turnRight();
  }
  else{
    moveForward();
  } // there is an intersection bc it is reading 3 lines



  int distance_Left = sonarLeft.ping_cm();
  int distance_Middle = sonarMiddle.ping_cm();
  int distance_Right = sonarRight.ping_cm();
  // pings should be atleast 29ms apart
  if ( ((distance_Left + distance_Right) > wall_dist) && (distance_Left > (distance_Right + 2)) ) {
    turnLeft();
    delay(NINE_DEG);
    stopMoving();

  }

  else if(distance_Middle > 5);{
    moveForward();
  }

  // if else(((distance_Left + distance_Right) < wall_dist) && (distance_Mid < 5))
  // {
  //   moveLeft();
  //   delay(ONE_EIGHT_DEG);
  // }

  delay(50); // update frequency (if to jittery increase)
}

