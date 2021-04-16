//Tic Tac Toe Soldering Kit
//By: Jim Heaney
//www.jim-heaney.com
//CC-BY-SA-NC 4.0

/*
  Modified by davedarko
  Added detection of player winning
  
*/

/*


 1 2 3
 4 5 6
 7 8 9

 x|x|x
 x|x|o
 x|o|x

Winning combinations
 A 1 2 3,
 B 1 5 9,
 C 1 4 7,
 D 2 5 8,
 E 3 5 7,
 F 3 6 9,
 G 4 5 6,
 H 7 8 9


1 A,B,C
2 A,D
3 A,E,F
4 C,G
5 B,D,E,G
6 F,G
7 C,E,H
8 D,H
9 B,F,H

o
1 A,C
2 A 
3 A,F
4 C 
 
6 F 
7 C,H
8 H
9 F,H

x
  B
2 D
3 E,F
4 G
  B,D,E,G
6 F,G
7 E,H
8 D,H
9 B,F,H

o| | 
 |x|
 | |x

o
  A,C
  A 
3 A
4 C 
 
6  
7 C
8 

o|o| 
 |x|
 | |x

x
  B
  
3 E,F
4 G
  B,E,G
6 F,G
7 E,H
8 H
  B,F,H
 
*/

const int C1 = A0;
const int C2 = A1;
const int C3 = A2;
const int R1X = A3;
const int R1O = A4;
const int R2X = A5;
const int R2O = 2;
const int R3X = 3;
const int R3O = 4;
const int C1B = 5;
const int C2B = 6;
const int C3B = 7;
const int R1B = 8;
const int R2B = 9;
const int R3B = 10;

uint8_t turn = 1;

uint8_t win_x[9] = {1,0,1,0,1,0,1,0,1};
uint8_t win_o[9] = {0,2,0,2,0,2,0,2,0};

uint8_t state[9] = {1,2,1,2,1,2,1,2,1};
int i;

unsigned long startuptime = 0;

int startuplevel = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(R1X, OUTPUT);
  pinMode(R1O, OUTPUT);
  pinMode(R2X, OUTPUT);
  pinMode(R2O, OUTPUT);
  pinMode(R3X, OUTPUT);
  pinMode(R3O, OUTPUT);
  pinMode(C1B, OUTPUT);
  pinMode(C2B, OUTPUT);
  pinMode(C3B, OUTPUT);

  pinMode(R1B, INPUT);
  pinMode(R2B, INPUT);
  pinMode(R3B, INPUT);

  startuptime = millis() + 1000;

  Serial.begin(115200);
  Serial.println("TicTac Oh no");

}

void loop() {
  // put your main code here, to run repeatedly:

  //Startup lights
  if ((millis() >= startuptime) && startuplevel == 0){
    for (i = 0; i <=9; i++){
      if (state[i] == 1){
        state[i] = 2;
      }
      else{
        state[i] = 1;
      }
      startuplevel = 1;
      startuptime = millis() + 1000;
    }
  }
  
  if ((millis() >= startuptime) && startuplevel == 1){
    for (i = 0; i <=9; i++){
      state[i] = 0;
      startuplevel = 2;
      startuptime = millis() + 1000;
    }
  }

  if (startuplevel == 2)
  {
    //Check for button presses. If there is a press on an unoccupied space, set the space color and change turns.
    digitalWrite(C1B, HIGH);
    playerTurn(R1B, 0);
    playerTurn(R2B, 3);
    playerTurn(R3B, 6);
    digitalWrite(C1B, LOW);
    
    digitalWrite(C2B, HIGH);
    playerTurn(R1B, 1);
    playerTurn(R2B, 4);
    playerTurn(R3B, 7);
    digitalWrite(C2B, LOW);
    
    digitalWrite(C3B, HIGH);
    playerTurn(R1B, 2);
    playerTurn(R2B, 5);
    playerTurn(R3B, 8);
    digitalWrite(C3B, LOW);
  }

  if ((millis() >= startuptime) && startuplevel == 3)
  {
    for (uint8_t i=0; i<9; i++)
    {
       state[i] = win_x[i];
    }
    startuptime = millis() + 2000;
    startuplevel = 5;
  }

  if ((millis() >= startuptime) && startuplevel == 4)
  {
    for (uint8_t i=0; i<9; i++)
    {
       state[i] = win_o[i];
    }
    startuptime = millis() + 2000;
    startuplevel = 5;
  }

  if ((millis() >= startuptime) && startuplevel == 5)
  {
    startuplevel = 0;
  }

  //Project the current states onto the LEDs. X = 1, O = 2.
  digitalWrite(C1, HIGH);
  if (state[0] == 0){
  }
  if (state[0] == 1){
    digitalWrite(R1X, LOW);
  }
  if(state[0] == 2){
    digitalWrite(R1O, LOW);
  }
  digitalWrite(R1X, HIGH);
  digitalWrite(R1O, HIGH);
  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  if (state[1] == 0){
  }
  if (state[1] == 1){
    digitalWrite(R1X, LOW);
  }
  if(state[1] == 2){
    digitalWrite(R1O, LOW);
  }
  digitalWrite(R1X, HIGH);
  digitalWrite(R1O, HIGH);
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
    if (state[2] == 0){
  }
  if (state[2] == 1){
    digitalWrite(R1X, LOW);
  }
  if(state[2] == 2){
    digitalWrite(R1O, LOW);
  }
  digitalWrite(R1X, HIGH);
  digitalWrite(R1O, HIGH);
  digitalWrite(C3, LOW);

  digitalWrite(C1, HIGH);
  if (state[3] == 0){
  }
  if (state[3] == 1){
    digitalWrite(R2X, LOW);
  }
  if(state[3] == 2){
    digitalWrite(R2O, LOW);
  }
  digitalWrite(R2X, HIGH);
  digitalWrite(R2O, HIGH);
  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  if (state[4] == 0){
  }
  if (state[4] == 1){
    digitalWrite(R2X, LOW);
  }
  if(state[4] == 2){
    digitalWrite(R2O, LOW);
  }
  digitalWrite(R2X, HIGH);
  digitalWrite(R2O, HIGH);
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
    if (state[5] == 0){
  }
  if (state[5] == 1){
    digitalWrite(R2X, LOW);
  }
  if(state[5] == 2){
    digitalWrite(R2O, LOW);
  }
  digitalWrite(R2X, HIGH);
  digitalWrite(R2O, HIGH);
  digitalWrite(C3, LOW);

  digitalWrite(C1, HIGH);
  if (state[6] == 0){
  }
  if (state[6] == 1){
    digitalWrite(R3X, LOW);
  }
  if(state[6] == 2){
    digitalWrite(R3O, LOW);
  }
  digitalWrite(R3X, HIGH);
  digitalWrite(R3O, HIGH);
  digitalWrite(C1, LOW);
  digitalWrite(C2, HIGH);
  if (state[7] == 0){
  }
  if (state[7] == 1){
    digitalWrite(R3X, LOW);
  }
  if(state[7] == 2){
    digitalWrite(R3O, LOW);
  }
  digitalWrite(R3X, HIGH);
  digitalWrite(R3O, HIGH);
  digitalWrite(C2, LOW);
  digitalWrite(C3, HIGH);
    if (state[8] == 0){
  }
  if (state[8] == 1){
    digitalWrite(R3X, LOW);
  }
  if(state[8] == 2){
    digitalWrite(R3O, LOW);
  }
  digitalWrite(R3X, HIGH);
  digitalWrite(R3O, HIGH);
  digitalWrite(C3, LOW);
}

/*
Winning combinations
 A 1 2 3,
 B 1 5 9,
 C 1 4 7,
 D 2 5 8,
 E 3 5 7,
 F 3 6 9,
 G 4 5 6,
 H 7 8 9
*/
void check_for_win(uint8_t buttonPressed){
  Serial.print("Turn of: ");
  Serial.print(turn);
  Serial.print(" - button: ");
  Serial.println(buttonPressed);

  // A 1 2 3
  if (
    state[0] == turn && 
    state[1] == turn && 
    state[2] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // B 1 5 9
  if (
    state[0] == turn && 
    state[4] == turn && 
    state[8] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // C 1 4 7
  if (
    state[0] == turn && 
    state[3] == turn && 
    state[6] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // D 2 5 8
  if (
    state[1] == turn && 
    state[4] == turn && 
    state[7] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // E 3 5 7
  if (
    state[2] == turn && 
    state[4] == turn && 
    state[6] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // F 3 6 9
  if (
    state[2] == turn && 
    state[5] == turn && 
    state[8] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

  // G 4 5 6
  if (
    state[3] == turn && 
    state[4] == turn && 
    state[5] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }

 // H 7 8 9
  if (
    state[6] == turn && 
    state[7] == turn && 
    state[8] == turn
  ){
    startuptime = millis() + 1000;
    startuplevel = 2+turn;
    Serial.println("YAY");
  }
}

void playerTurn(uint8_t row, uint8_t i)
{
  if((digitalRead(row) == 1) && (state[i] == 0)) {
    state[i] = turn;
    check_for_win(i);
    
    if (turn == 1){
      turn = 2;
    }
    else{
      turn = 1;
    }
  }
}
