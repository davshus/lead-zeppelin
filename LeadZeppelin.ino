#include <DynamixelSerial.h>
void moveFret(int, int);
int genID(int, int);
void handleKey(int);
void hitString(int);
void syncMove(int, int);
int stringIDs[] = {4, 5, 6, 12};
const int fretPos[] = {341, 682, 1024};
int rows[] = {3, 4, 5};
int columns[] = {6, 7, 8, 9};
int last = -1;
#define playing 621
#define aboveplaying 600
boolean buttonsPressed[] = {false, false, false, false, false, false, false, false, false, false, false, false}; //12 falses
void setup() {
  // put your setup code here, to run once:
  Dynamixel.begin(1000000,2);

//  Serial.begin(9600);
  delay(1000);
  Dynamixel.setPunch(10, 0x20);
  for (int i = 0; i < 3; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(i, LOW);
  }
  
  for (int i = 0; i < 4; i++) {
    pinMode(columns[i], INPUT);
  }
}

void loop() {

  for (int i = 0; i < 3; i++) {
    digitalWrite(rows[i], HIGH);
    for (int j = 0; j < 4; j++) {
      int value = digitalRead(columns[j]);
      int id = genID(i, j);
      if (value == HIGH && !buttonsPressed[id]) {
        buttonsPressed[id] = true;
        handleKey(i, j);
      } else if (value != HIGH) {
        buttonsPressed[id] = false;
      }
    }
    digitalWrite(rows[i], LOW);
  }
  // put your main code here, to run repeatedly:

}

void moveFret(int string, int fret) {
   Dynamixel.move(stringIDs[string], fretPos[fret]);
}
int genID(int row, int column) {
  return (column*3)+row;
}
boolean lift = false;
    int vals[6][2] = {{505,535},{490, 510},{480,500},{470,495},{455,475},{440,460}};
void handleKey(int row, int col) {
  int id = genID(row, col);
  if (id <= 5) {
    if (lift) {
      
    Dynamixel.move(18, aboveplaying);
    delay(50);
    }
    lift = false;
    int string = 5 - id;
    Dynamixel.move(10, vals[string][0]);
    delay(100);
    Dynamixel.move(18, playing);
    delay(100);
    Dynamixel.move(10, vals[string][1]);
    delay(50);
    Dynamixel.move(18, aboveplaying);
  } else if (id < 9) {
    lift = true;
    Dynamixel.move(10, vals[0][1]);
    delay(100);
    Dynamixel.move(18, playing-5);
    delay(100);
    Dynamixel.move(10, vals[5][0]);
//    delay(200);
//    Dynamixel.move(18, aboveplaying);
    
  } else {
    lift = true;
    Dynamixel.move(10, vals[5][0]);
    delay(100);
    Dynamixel.move(18, playing-8);
    delay(100);
    Dynamixel.move(10, vals[0][1]);
//    delay(200);
//    Dynamixel.move(18, aboveplaying);
    
  }
  
}
//  int n = 100/8;
//  int x = 1024/4;
//  if (id < 8) {
//    Dynamixel.move(10, (n*id)+450);
//  } else if (id < 10) {
//    Dynamixel.move(18, aboveplaying);
//  } else {
//    Dynamixel.move(18, playing);
//  }
//}
void hitString(int string) {
//  Dynamixel.move(18, aboveplaying);
//  delay(50);
  
}
void syncMove(int id, int val) {
  Dynamixel.move(id, val);
  while (abs(Dynamixel.readPosition(id) - val) > 10) {
    
  }
}
//void 
