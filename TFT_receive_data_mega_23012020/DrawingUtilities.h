#pragma once
#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>

extern UTFTGLUE myGLCD;

#define W 479
#define H 319

struct Color{
  Color(int _r = 0, int _g = 0, int _b = 0){
    r = _r; g = _g; b = _b;
  }
  int r = 0, g = 0, b = 0;
};
struct Pos{
  Pos(int _x = 0, int _y = 0){
    x = _x; y = _y;
  }
  int x = 0, y = 0;
};

struct VecF{
  VecF(float _x = 0.0f, float _y = 0.0f){
    x = _x; y = _y;
  }
  float x = 0.0f, y = 0.0f;
};


const Color RED    = Color(255,  0,  0);
const Color GREEN  = Color(  0,255,  0);
const Color BLUE   = Color(  0,  0,255);
const Color WHITE  = Color(255,255,255);
const Color BLACK  = Color(0,0,0);
const Color YELLOW = Color(255,255,0);

void setColor(const Color& col);
void setBackgroundColor(const Color& col);
void fillScreen(const Color& col);
void drawLine(const Pos& pstart, const Pos& pend, const Color& col);
void drawRecCentered(int w, int h, const Color& col);
void drawText(char* str, const Pos& pos, const Color& col, const Color& backCol);
void drawInt(int number, const Pos& pos, const Color& col, const Color& backCol);
void drawFloat(float number, const Pos& pos, int dec, const Color& col, const Color& backCol);

//temp
void drawCurve();
