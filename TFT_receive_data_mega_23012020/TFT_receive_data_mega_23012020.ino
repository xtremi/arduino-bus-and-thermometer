#include <Manchester.h>
#include "Graph.h"

#define RECEIVER_PIN 31
#define MIN_TIME_BETWEEN_GRAPH_PLOT_1 2000
#define MIN_TIME_BETWEEN_GRAPH_PLOT_2 60000
#define TIME_BETWEEN_GRAPH_RESET_1 60000
#define TIME_BETWEEN_GRAPH_RESET_2 360000
#define LOOP_ITERATIONS_BETWEEN_TIME_DISPLAY_UPDATE 100

#if !defined(SmallFont)
extern uint8_t SmallFont[];    //.kbv GLUE defines as GFXFont ref
#endif

Axes axes(W, H, YELLOW, 300);
Graph graph(&axes);

struct timer_info
{
  int      dt						= 0;
  long int currentTime				= 0;
  long int previousTime				= 0;
  
  long int timeSinceLastReceived	= 0;
  long int timeReceived				= 0;

  long int localShortTime			= 0;
  long int localLongTime			= 0;
};
struct RF_data
{
  uint8_t data_size;
  float temp  = 0.0f;
  float hum   = 0.0f;
  uint16_t counter = 0;
  uint16_t dht_chk = 0;
};

timer_info timerInfo;
RF_data rfDataPack;

const char* DHT_CHK_STR[4] = { "DHTLIB_OK", "DHTLIB_ERROR_CHECKSUM", "DHTLIB_ERROR_TIMEOUT", "INVALID_DHT_CODE" };
const int RF_DATA_PACK_SIZE = sizeof(rfDataPack);
uint8_t RF_DATA_PACK_BUFFER[RF_DATA_PACK_SIZE];


struct esp8266_test_struct {
	int   i[4];
	float f[2];
	char  c[128];
};
esp8266_test_struct esp8266data;


/************************************/
void initArduino();
void initGraph();
void initScreen();
void initESP8266();
void initRF();
/************************************/

/************************************/
void loopTime();
void loopScreen();
void loopESP8266();
void loopRF();
/************************************/

/************************************/
bool RFdataIsOk(RF_data* dp);
char* getDHTCHKstr(int chk);
void processNewRFdata(RF_data* rfdata);
void displayInvalidRFdata(RF_data* rfdata);
void displayValidRFdata(RF_data* rfdata);
void updateTimeDisplay();
/************************************/

/************************************/
void setup()
/************************************/
{   
  initArduino(); delay(200);
  initESP8266(); delay(200);
  initScreen();  delay(200);  
  initRF();      delay(200);
}

int  loopCounter				= 0;
bool receivedNewRFdata			= false;
bool shortTimePassed			= false;
bool longTimePassed				= false;
bool loopCounterIntervalPassed	= false;

/************************************/
void loop()
/************************************/
{   
	loopTime();
	loopESP8266();	
	loopRF();
	loopScreen();
 
	loopCounter++;  
}

void loopTime()
{
	timerInfo.currentTime = millis();
	timerInfo.dt = (int)(timerInfo.currentTime - timerInfo.previousTime);
	timerInfo.previousTime = timerInfo.currentTime;

	timerInfo.localShortTime += timerInfo.dt;
	timerInfo.localLongTime += timerInfo.dt;


	if (timerInfo.localShortTime > TIME_BETWEEN_GRAPH_RESET_1) {
		timerInfo.localShortTime = 0;
		shortTimePassed = true;
	}
	if (timerInfo.localLongTime > TIME_BETWEEN_GRAPH_RESET_2) {
		timerInfo.localLongTime = 0;
		longTimePassed = true;
	}

	if (loopCounter == LOOP_ITERATIONS_BETWEEN_TIME_DISPLAY_UPDATE) {
		loopCounterIntervalPassed = true;
	}

}


void loopScreen()
{
	if (shortTimePassed) {
		fillScreen(BLACK);
		graph.resetGraph();
		shortTimePassed = false;
	}

	if (longTimePassed) {
		longTimePassed = false;
	}

	if (receivedNewRFdata) {
		receivedNewRFdata = false;
		processNewRFdata(&rfDataPack);
	}

	if (loopCounterIntervalPassed) {
		loopCounterIntervalPassed = false;
		updateTimeDisplay();
		loopCounter = 0;
	}
}

void processNewRFdata(RF_data* rfdata)
{
	if (!RFdataIsOk(rfdata)) {
		displayInvalidRFdata(rfdata);
	}
	else {
		displayValidRFdata(rfdata);
		if (timerInfo.timeSinceLastReceived >= MIN_TIME_BETWEEN_GRAPH_PLOT_1)
		{
			VecF dataPoint((float)timerInfo.localShortTime / 1000.0, rfdata->temp);
			graph.addDataPoint(dataPoint);
		}
	}
}

const int posx = W / 2 + 180;
const int dx = 55;
void displayInvalidRFdata(RF_data* rfdata)
{
	myGLCD.setTextSize(1);
	drawText("status:", Pos(posx - dx, 80), RED, BLACK);
	drawText("invalid", Pos(posx, 80), RED, BLACK);
}
void displayValidRFdata(RF_data* rfdata)
{
	myGLCD.setTextSize(2);
	drawText("temp:", Pos(posx - dx - 2, 40), RED, BLACK);
	drawFloat(rfDataPack.temp, Pos(posx, 40), 1, GREEN, BLACK);

	myGLCD.setTextSize(1);
	drawText("hum   :", Pos(posx - dx, 60), RED, BLACK);
	drawFloat(rfDataPack.hum, Pos(posx, 60), 1, GREEN, BLACK);

	drawText("count :", Pos(posx - dx, 70), RED, BLACK);
	drawInt(rfDataPack.counter, Pos(posx, 70), WHITE, BLACK);

	drawText("status:", Pos(posx - dx, 80), RED, BLACK);
	drawText(getDHTCHKstr(rfDataPack.dht_chk), Pos(posx, 80), WHITE, BLACK);
}
void updateTimeDisplay()
{
	myGLCD.setTextSize(1);
	drawFloat((float)timerInfo.timeSinceLastReceived / 1000, Pos(0, 0), 1, BLACK, WHITE);
	drawInt((int)(timerInfo.currentTime / 1000), Pos(W / 2, 0), GREEN, BLUE);

	myGLCD.setTextSize(2);
	drawFloat((float)timerInfo.localShortTime / 1000.0, Pos(W - 80, 0), 1, YELLOW, BLACK);
	drawFloat((float)timerInfo.localLongTime / 1000.0, Pos(W - 80, 20), 1, YELLOW, BLACK);
}


void loopESP8266()
{
	if (Serial1.available() >= sizeof(esp8266_test_struct)) {
		Serial1.readBytes((char*)&esp8266data, sizeof(esp8266_test_struct));

		Serial.print("i: "); Serial.print(esp8266data.i[0]); Serial.println(esp8266data.i[1]);
		Serial.print("f: "); Serial.print(esp8266data.f[0]); Serial.println(esp8266data.f[1]);
		Serial.print("c: "); Serial.println(esp8266data.c);
	}
}
void loopRF()
{
	if (man.receiveComplete())
	{
		timerInfo.timeReceived = timerInfo.currentTime;
		memcpy(&rfDataPack, RF_DATA_PACK_BUFFER, RF_DATA_PACK_SIZE);

		receivedNewRFdata = true;

		man.beginReceiveArray(RF_DATA_PACK_SIZE, RF_DATA_PACK_BUFFER);
		timerInfo.timeSinceLastReceived = timerInfo.currentTime - timerInfo.timeReceived;
	}
}



bool RFdataIsOk(RF_data* dp){
  return !(isnan(dp->temp));
  //return true;
  //return dp->status[0] == 'o' && dp->status[1] == 'k';
}

char* getDHTCHKstr(int chk) {
	chk = -chk;
	if (chk < 0 || chk > 2)
		chk = 3;
	return DHT_CHK_STR[chk];
}








void initArduino()
{
  Serial.begin(9600);
}

void initGraph()
{
  axes.setTicks(12, 4, 0, 60, -10, 30);
  axes.drawAll();
}
void initScreen()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);  
  myGLCD.clrScr();
  myGLCD.setTextSize(1);
  fillScreen(BLACK);  
  initGraph();
  myGLCD.setTextSize(2);  
  drawText("Lanza", Pos(W/2 - 60, 20),  GREEN, BLACK);
}
void initESP8266()
{
  Serial1.begin(9600);
}
void initRF()
{
  man.setupReceive(RECEIVER_PIN, MAN_600);
  man.beginReceiveArray(RF_DATA_PACK_SIZE, RF_DATA_PACK_BUFFER);
}
