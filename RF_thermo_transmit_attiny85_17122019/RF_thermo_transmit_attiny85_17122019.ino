#include <VirtualWire.h>
#include "DHT.h" //both work with Arduino Micro
#include "dht11.h"

#define LED_PIN 1
#define DHT_PIN 6
#define DHT_TYPE DHT11
#define TRANSMIT_PIN 3

DHT dht(DHT_PIN, DHT_TYPE);
//dht11 DHT11;

void blinkMulti(int pin, int N, int d1 = 200, int d2 = 200);
void blink(int pin, int d1 = 200, int d2 = 200);

void setup() {  
  delay(500);  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); 
  vw_set_tx_pin(TRANSMIT_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(500);    
  digitalWrite(LED_PIN, LOW); 

  //dht.begin();
}

struct DataPack{
  float temp = 0.0f;
  float hum = 0.0f;
  int counter = 0;
  int dht_chk = 0;
};

char* DHT_CHK_STR[4] ={"DHTLIB_OK", "DHTLIB_ERROR_CHECKSUM", "DHTLIB_ERROR_TIMEOUT", "DHTLIB_ERROR_TIMEOUT"};
char* getDHTCHKstr(int chk){
  if(chk < 0 || chk > 3)
    chk = 3;
  return DHT_CHK_STR[chk];  
}

DataPack dataPack;
int counter = 1;
int T_delay = 100;
void loop() {
  digitalWrite(LED_PIN, HIGH);
    
  dataPack.temp    = 20.0; //dht.readTemperature();
  dataPack.hum     = 30.0; //dht.readHumidity();
  dataPack.dht_chk = DHTLIB_OK;
  
  /*dataPack.dht_chk = DHT11.read(DHT_PIN);
  dataPack.temp = (float)DHT11.temperature;
  dataPack.hum = (float)DHT11.humidity;*/
  
  dataPack.counter = counter++; 

  Serial.print(" T   = "); Serial.println(dataPack.temp);
  Serial.print(" H   = "); Serial.println(dataPack.hum);
  Serial.print(" chk = "); Serial.println(getDHTCHKstr(dataPack.dht_chk));    
  vw_send((uint8_t*)&dataPack, sizeof(DataPack));
  vw_wait_tx();

  
  delay(T_delay);
  digitalWrite(LED_PIN, LOW);
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
