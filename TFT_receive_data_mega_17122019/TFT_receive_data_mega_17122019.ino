// UTFT_Demo_480x320 (C)2013 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//#include <VirtualWire.h>
#include <Manchester.h>
#include "Graph.h"

#define RECEIVER_PIN 31

#if !defined(SmallFont)
extern uint8_t SmallFont[];    //.kbv GLUE defines as GFXFont ref
#endif

Axes axes(W, H, YELLOW, 300);
Graph graph(&axes);

struct DataPack{
  float temp = 0.0f;
  float hum = 0.0f;
  int counter = 0;
  int dht_chk = 0;
};

DataPack dataPack;
const int DATA_PACK_SIZE = sizeof(DataPack);
uint8_t DATA_PACK_BUFFER[DATA_PACK_SIZE];

int time_start = 0;
void setup()
{   
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);
  
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);  
  myGLCD.clrScr();
  myGLCD.setTextSize(1);

  fillScreen(BLACK);  
  axes.setTicks(12, 4, 0, 60, -10, 30);
  axes.drawAll();
  myGLCD.setTextSize(2);

  
    
  /*vw_setup(500);
  vw_set_rx_pin(RECEIVER_PIN);
  vw_set_ptt_inverted(true);  
  vw_rx_start();*/
  man.setupReceive(RECEIVER_PIN, MAN_1200);
  //man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
  man.beginReceive();

  drawText("19.01.2020", Pos(W/2 - 60, 20),  GREEN, BLACK);
}






long int currentTime = 0, previousTime = 0;
int dt = 0;
long int timeSinceLastReceived = 0, timeReceived = 0;
int loopCounter = 0;
long int localShortTime = 0;
long int localLongTime  = 0;

struct test_struct{
  int i[4];
  float f[2];
  char c[128];  
};
test_struct data;
void receiveFromESP8266(){

  if(Serial1.available() >= sizeof(test_struct)){
    Serial1.readBytes((char*)&data, sizeof(test_struct));

    Serial.print("i: "); Serial.print(data.i[0]); Serial.println(data.i[1]);
    Serial.print("f: "); Serial.print(data.f[0]); Serial.println(data.f[1]);
    Serial.print("c: "); Serial.println(data.c); 
  }
  
}



char* DHT_CHK_STR[4] ={"DHTLIB_OK", "DHTLIB_ERROR_CHECKSUM", "DHTLIB_ERROR_TIMEOUT", "INVALID_DHT_CODE"};
char* getDHTCHKstr(int chk){
  chk = -chk;
  if(chk < 0 || chk > 2)
    chk = 3;
  return DHT_CHK_STR[chk];  
}

bool dataPackOk(DataPack* dp);



void loop()
{   

  receiveFromESP8266();
  
  currentTime   = millis();
  dt            = (int)(currentTime - previousTime);
  previousTime  = currentTime;
    
  localShortTime += dt;
  localLongTime  += dt;
  if(localShortTime >  60000){
     localShortTime = 0;
     fillScreen(BLACK);
     graph.resetGraph();
  }
  if(localLongTime  > 120000) localLongTime  = 0;

  if(man.receiveComplete())
  //if(vw_have_message())
  {  
    timeReceived = currentTime;
    //vw_get_message(buf, &buflen);
    drawText("RECEIVED SOMETHING", Pos(W/2, H/2), RED, BLUE);
    memcpy(&dataPack, DATA_PACK_BUFFER, DATA_PACK_SIZE);
    Serial.println("vw_have_message()");
    //if(true)
    if(dataPackOk(&dataPack))
    {
      myGLCD.setTextSize(2);
      drawFloat(dataPack.temp,  Pos(W/2 + 120, 40), 1, GREEN, BLACK);
      myGLCD.setTextSize(1);
      drawFloat(dataPack.hum,   Pos(W/2 + 120, 60), 1, GREEN, BLACK);
      drawInt(dataPack.counter, Pos(W/2 + 120, 70),    WHITE, BLACK);
      drawText(getDHTCHKstr(dataPack.dht_chk), Pos(W/2 + 120, 80),  WHITE, BLACK);
    }    
    else
    { 
      myGLCD.setTextSize(1);     
      drawText("invalid data",Pos(W/2 + 120, 80), RED, BLACK);
    }
    
    uint16_t m = man.getMessage();
    man.beginReceive();
    //man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
    
    if(timeSinceLastReceived >= 2000)
    {
      VecF dataPoint((float)localShortTime/1000.0, dataPack.temp);
      graph.addDataPoint(dataPoint);      
    }
  }
  timeSinceLastReceived = currentTime - timeReceived;

  if(!(loopCounter%100)){
    myGLCD.setTextSize(1);
    drawFloat((float)timeSinceLastReceived/1000, Pos(0,0), 1, BLACK, WHITE);    
    drawInt((int)(currentTime/1000), Pos(W/2,0), GREEN, BLUE);

    myGLCD.setTextSize(2);
    drawFloat((float)localShortTime/1000.0, Pos(W-80, 0), 1, YELLOW, BLACK);    
    drawFloat((float)localLongTime/1000.0,  Pos(W-80, 20), 1, YELLOW, BLACK);
  }

  loopCounter++;  
}

bool dataPackOk(DataPack* dp){
  return true;
  //return dp->status[0] == 'o' && dp->status[1] == 'k';
}
