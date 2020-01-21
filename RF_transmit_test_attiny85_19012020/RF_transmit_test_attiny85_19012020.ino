#include <Manchester.h>
#define LED_PIN 1
#define TRANSMIT_PIN 3

void blinkMulti(int pin, int N, int d1 = 200, int d2 = 200);
void blink(int pin, int d1 = 200, int d2 = 200);

void setup() {  
  delay(500);  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); 
  man.workAround1MhzTinyCore();
  man.setupTransmit(TRANSMIT_PIN, MAN_1200);  
  digitalWrite(LED_PIN, LOW); 
}

struct DataPack{
  float temp  = 0.0f;
  float hum   = 0.0f;
  int counter = 0;
  int dht_chk = 0;
};

DataPack dataPack;
int counter = 1;
int T_delay = 1000;
void loop() {
  
  digitalWrite(LED_PIN, HIGH);    
  dataPack.temp    = 20.0;
  dataPack.hum     = 30.0;
  dataPack.dht_chk = 0;  
  dataPack.counter = counter++; 
  //man.transmitArray(sizeof(DataPack), (uint8_t*)&dataPack);
  man.transmit(123);
  
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
