// Default
// Here we go
// Commentation
// Project HoverCraft
/*
- Motor 1 F - 2
- Motor 1 R - 5
- Motor 2 F - 6
- Motor 2 R - 7
- Motor 3 F - 8
- Motor 3 R - 9
- Motor 4 F - 10
- Motor 4 R - 11
- Ping1 echo - 22
- Ping1 trig - 23
- Ping2 echo - 24
- Ping2 trig - 25
- Stepper1 - 40
- Stepper2 - 41
- Stepper3 - 42
- Stepper4 - 43
- Pins 1,3,4 are used by SPI communication
*/
int motorpins[][2] = {{2, 5}, {6, 7}, {8, 9}, {10, 11}};

#define UNDEFINED -1
#define RIGHT    0
#define FORWARD  1
#define LEFT     2
#define BACKWARD 3
#define UP       4
#define DOWN     5
#define STANDARD 0
#define REVERSE  1
#define HYPERSPEED   255
#define NORMALSPEED  192
#define LAGSPEED     128

int current_direction = UP;

void fly()  {
  analogWrite(motorpins[LEFT][STANDARD], HYPERSPEED);
  analogWrite(motorpins[RIGHT][STANDARD], HYPERSPEED);
  analogWrite(motorpins[FORWARD][STANDARD], HYPERSPEED);
  analogWrite(motorpins[BACKWARD][STANDARD], HYPERSPEED);
}


void standardize()  {
  analogWrite(motorpins[LEFT][STANDARD], NORMALSPEED);
  analogWrite(motorpins[RIGHT][STANDARD], NORMALSPEED);
  analogWrite(motorpins[FORWARD][STANDARD], NORMALSPEED);
  analogWrite(motorpins[BACKWARD][STANDARD], NORMALSPEED);
}

void hover()  {
  unpitch();
  standardize();
}

void move(int thedirection)  {
  pitch(thedirection);
  fly();
}

int get_reverse(int thedirection)  {
  if (thedirection == LEFT)
    return RIGHT;
  else if (thedirection == RIGHT)
    return LEFT;
  else if (thedirection == FORWARD)
    return BACKWARD;
  else if (thedirection == BACKWARD)
    return FORWARD;
  else if (thedirection == UP)
    return DOWN;
  else if (thedirection == DOWN)
    return UP;
  return -1;
}

void pitch(int thedirection)  {
  unpitch();
  int normal1, normal2, hyper, lag;
  if (thedirection == RIGHT)  {
    hyper = LEFT; lag = RIGHT;
    normal1 = FORWARD; normal2 = BACKWARD;
  }
  else if (thedirection == LEFT)  {
    hyper = RIGHT; lag = LEFT;
    normal1 = FORWARD; normal2 = BACKWARD;
  }
  else if (thedirection == FORWARD)  {
    hyper = BACKWARD; lag = FORWARD;
    normal1 = RIGHT; normal2 = LEFT;
  }
  else if (thedirection == BACKWARD)  {
    hyper = FORWARD; lag = BACKWARD;
    normal1 = RIGHT; normal2 = LEFT;
  }
   
   analogWrite(motorpins[hyper][STANDARD], HYPERSPEED);
   analogWrite(motorpins[normal1][STANDARD], NORMALSPEED);
   analogWrite(motorpins[normal2][STANDARD], NORMALSPEED);
   analogWrite(motorpins[lag][STANDARD], LAGSPEED);
   delay(400);
   standardize(); 
   current_direction = thedirection; 
}

void unpitch()  {
  if (current_direction != UNDEFINED)  {
    pitch(get_reverse(current_direction));
  }
  current_direction = UNDEFINED;
}
