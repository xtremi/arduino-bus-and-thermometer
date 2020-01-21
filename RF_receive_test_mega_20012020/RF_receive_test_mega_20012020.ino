#include <Manchester.h>
#define RECEIVER_PIN 31

struct DataPack{
  float temp  = 0.0f;
  float hum   = 0.0f;
  int counter = 0;
  int dht_chk = 0;
};

DataPack dataPack;
const uint8_t DATA_PACK_SIZE = sizeof(DataPack);
uint8_t DATA_PACK_BUFFER[DATA_PACK_SIZE];

int time_start = 0;
void setup()
{   
  Serial.begin(9600);
  Serial.println("STARTED\n");
  delay(200);    
  man.setupReceive(RECEIVER_PIN, MAN_1200);
  man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
  //man.beginReceive();
  delay(200);
  Serial.println("waiting for message...");

  for(int i = 0; i < 12; i++)
    DATA_PACK_BUFFER[i] = 4;
  
}


int counter = 0;
void loop()
{   
  if(man.receiveComplete())
  { 
    Serial.println(" - - - RECEIVED SOMETHING - - -");

    for(int i = 0; i < 12; i++)
      Serial.println(DATA_PACK_BUFFER[i]);

    
    memcpy(&dataPack, DATA_PACK_BUFFER, DATA_PACK_SIZE);
    Serial.print(dataPack.temp); Serial.print(" - ");
    Serial.print(dataPack.hum);  Serial.print(" - ");
    Serial.println(dataPack.counter);
    
    /*uint16_t m = man.getMessage();
    Serial.println(m);*/
    
    //man.beginReceive();
    man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
    delay(2000);
  }
  
  //Serial.println(counter);
  /*if((counter++) == 1000){
    counter = 0;
    Serial.println("waiting...");
  }
  delay(10);*/
}
