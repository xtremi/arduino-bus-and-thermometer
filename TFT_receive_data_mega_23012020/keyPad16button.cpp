#include "keyPad16button.h"


KeyPad16button::KeyPad16button(int C1, int C2, int C3, int C4, int R1, int R2, int R3, int R4){
  Cpin[0] = C1; Cpin[1] = C2; Cpin[2] = C3; Cpin[3] = C4;
  Rpin[0] = R1; Rpin[1] = R2; Rpin[2] = R3; Rpin[3] = R4;
}

void KeyPad16button::init(){
  //Init pin mode
  //Rows OUTPUT / Column INPUT (Pullup)
  for(int i = 0; i<4; i++){
    pinMode(Cpin[i], INPUT_PULLUP);
    pinMode(Rpin[i], OUTPUT);
  }

  setAllKeyStatus(false);

  //Set all rows to HIGH
  turnOnAllRows();
}

//Set all key statuses to keyStatus
void KeyPad16button::setAllKeyStatus(bool _status){
  for(int i = 0; i<16; i++)
    keyStatus[i] = _status;
  }

bool KeyPad16button::processAllKeys(){
    setAllKeyStatus(false);

    //For each row of keys
    for(int i = 0; i<4; i++){
      turnOffRow(i);

      //For each column of keys
      for(int j = 0; j<4; j++){
        if(isColPressed(j)){  

          //Set key status to true
          int keyIndex = getKeyNumber(i,j)-1; 
          keyStatus[keyIndex] = true;
          
          if(serialPrintON == true){
            Serial.print("S");
            Serial.println(keyIndex + 1);           
            //delay(50);      
          }
        }
      
      }//col
      turnOnRow(i);    
  }//ro
}

//Returns true if key number keyNumb was pressed
bool KeyPad16button::isKeyPressed(int keyNum){  
  return keyStatus[keyNum-1];
}

//Set all row pins to HIGH
void KeyPad16button::turnOnAllRows(){
  for (int i=0;i<4;i++){
    digitalWrite(Rpin[i], HIGH);
  }
}

//Set Row pin to LOW
void KeyPad16button::turnOffRow(int row){
  digitalWrite(Rpin[row], LOW);
}
//Set Row pin to HIGH
void KeyPad16button::turnOnRow(int row){
  digitalWrite(Rpin[row], HIGH);
}

//Returns true if key in Column is pressed
bool KeyPad16button::isColPressed(int col){
  int colStatus = digitalRead(Cpin[col]);
  if(colStatus == LOW)
    return true;
  else
    return false; 
}



//Return the key number [1-16] based on row and col number
int KeyPad16button::getKeyNumber(int row, int col){
  return (row)*4 + col + 1;
}
