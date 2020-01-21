#include <Manchester.h>
#define RECEIVER_PIN 31

struct DataPack{
  uint8_t data_size;
  float temp  = 0.0f;
  float hum   = 0.0f;
  uint16_t counter = 0;
  uint16_t dht_chk = 0;
};

DataPack dataPack;
const uint8_t DATA_PACK_SIZE = sizeof(DataPack);
uint8_t DATA_PACK_BUFFER[DATA_PACK_SIZE];

int time_start = 0;
void setup()
{   
  Serial.begin(9600);
  delay(200);    

  Serial.println("MEGA STARTED\n");
  Serial.print("sizeof(DataPack)         = "); Serial.println(sizeof(DataPack));
  Serial.print("sizeof(dataPack)         = "); Serial.println(sizeof(dataPack));
  Serial.print("sizeof(DATA_PACK_BUFFER) = "); Serial.println(sizeof(DATA_PACK_BUFFER));
  Serial.print("DATA_PACK_SIZE           = "); Serial.println(DATA_PACK_SIZE);
  Serial.println("waiting for message..."); 

  man.setupReceive(RECEIVER_PIN, MAN_1200);
  man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
  //man.beginReceive(); 
}


int counter = 0;
void loop()
{   
  if(man.receiveComplete())
  { 
    Serial.println(" - - - RECEIVED SOMETHING - - -");
    //uint16_t m = man.getMessage();
    //Serial.println(m);
    memcpy(&dataPack, DATA_PACK_BUFFER, DATA_PACK_SIZE);

    
    Serial.print("RAW  : ");
    for(int i = 0; i < 12; i++){
      Serial.print("[");
      Serial.print(DATA_PACK_BUFFER[i]);
      Serial.print("]");      
    }

    
    Serial.print("\nDATA :");    
    Serial.print(dataPack.temp); Serial.print(" - ");
    Serial.print(dataPack.hum);  Serial.print(" - ");
    Serial.println(dataPack.counter);
        
    //man.beginReceive();
    //delay(500);
    man.beginReceiveArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);    
  }
  
  //Serial.println(counter);
  /*if((counter++) == 1000){
    counter = 0;
    Serial.println("waiting...");
  }
  delay(10);*/
}
