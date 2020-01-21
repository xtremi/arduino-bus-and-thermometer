#include "DrawingUtilities.h"

UTFTGLUE myGLCD(0x9488,A2,A1,A3,A4,A0);

void setColor(const Color& col){
  myGLCD.setColor(col.r, col.g, col.b);  
}
void setBackgroundColor(const Color& col){
  myGLCD.setBackColor(col.r, col.g, col.b);
}

void fillScreen(const Color& col){
  setColor(col);
  myGLCD.fillRect(0, 0, W, H);
}

void drawLine(const Pos& pstart, const Pos& pend, const Color& col){
  setColor(col);
  myGLCD.drawLine(pstart.x, pstart.y, pend.x, pend.y);
}
  

void drawRecCentered(int w, int h, const Color& col){    
  setColor(col);
  myGLCD.fillRect(W/2-w/2, H/2-h/2, W/2+w/2, H/2+h/2);
}

void drawText(char* str, const Pos& pos, const Color& col, const Color& backCol){
  setBackgroundColor(backCol);
  setColor(col);
  myGLCD.print(str, pos.x, pos.y);
}

void drawInt(int number, const Pos& pos, const Color& col, const Color& backCol){
  setBackgroundColor(backCol);
  setColor(col);
  myGLCD.printNumI(number, pos.x, pos.y);
}

void drawFloat(float number, const Pos& pos, int dec, const Color& col, const Color& backCol){
  setBackgroundColor(backCol);
  setColor(col);
  myGLCD.printNumF(number, dec, pos.x, pos.y);
}

void drawCurve(){
      myGLCD.setColor(0,29,200);
    for(int i = 0; i<479;i++){
      myGLCD.drawPixel(i, H/2 + (H/6)*( sin(20*float(i)/float(W)) )  );          
      myGLCD.drawPixel(i,159+(sin(((i*1.13)*3.14)/180)*95));
    }
}
