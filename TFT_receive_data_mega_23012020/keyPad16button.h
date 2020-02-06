#include "Arduino.h"


class KeyPad16button {
  
  private:    
    //storage for key name. Used for serial.print
    char keyName[4];
    
    //Pin ids of Columns and Rows
    int Cpin[4];
    int Rpin[4];

    //Placeholder for keystatus: false -> was not pressed, true "was pressed"
    bool keyStatus[16];
    
  private:
    void turnOnAllRows();
    void turnOffRow(int row);
    void turnOnRow(int row);
    bool isColPressed(int col);

    int getKeyNumber(int row, int col);

    void setAllKeyStatus(bool keyStatus);

  public:
    KeyPad16button(int C1, int C2, int C3, int C4, 
      int R1, int R2, int R3, int R4);
    ~KeyPad16button(){};

    void init();
    bool isKeyPressed(int keyNum);
    bool processAllKeys();

    bool serialPrintON = false;
  };
