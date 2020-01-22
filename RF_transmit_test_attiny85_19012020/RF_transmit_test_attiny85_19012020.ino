#include <Manchester.h>
#define LED_PIN 1
#define TRANSMIT_PIN 3

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

void blinkMulti(int pin, int N, int d1 = 200, int d2 = 200);
void blink(int pin, int d1 = 200, int d2 = 200);

void setup() { 
  dataPack.data_size = DATA_PACK_SIZE;
   
  delay(500);  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); 
  //man.workAround1MhzTinyCore();
  man.setupTransmit(TRANSMIT_PIN, MAN_600);  
  digitalWrite(LED_PIN, LOW); 
}

int counter = 1;
int T_delay = 1000;
void loop() {
  
  digitalWrite(LED_PIN, HIGH);    
  dataPack.temp    = 20.0;
  dataPack.hum     = 30.0;
  dataPack.dht_chk = 0;  
  dataPack.counter = counter++; 
  memcpy(DATA_PACK_BUFFER, &dataPack, DATA_PACK_SIZE);
  man.transmitArray(DATA_PACK_SIZE, DATA_PACK_BUFFER);
  //man.transmit((uint16_t)123);
  
  digitalWrite(LED_PIN, LOW);
  blinkMulti(LED_PIN,5, 100, 100);
  delay(T_delay);
}

void blinkMulti(int pin, int N, int d1, int d2){
  for(int i = 0; i < N; i++)
    blink(pin, d1, d2);
}

void blink(int pin, int d1, int d2){  
  digitalWrite(LED_PIN, HIGH);
  delay(d1);  
  digitalWrite(LED_PIN, LOW);
  delay(d2);
}
