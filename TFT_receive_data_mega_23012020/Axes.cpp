#include "Axes.h"

Axes::Axes(int _W, int _H, const Color& _col, int _xAxisLength)
{ 
  sW           = _W;
  sH           = _H;
  col         = _col;
  xAxisLength = _xAxisLength;

  dpos  = 0.1*sW;
  ddpos = dpos/2;
  yAxisLength = sH - 2*dpos;

  _origin     = Pos(dpos, sH - dpos);
  xaxisStart = Pos(_origin.x - ddpos,     _origin.y);
  xaxisEnd   = Pos(_origin.x + xAxisLength, _origin.y);
  yaxisStart = Pos(_origin.x, sH - dpos + ddpos);
  yaxisEnd   = Pos(_origin.x, dpos);  
}
void Axes::setTicks(int _nTicksX, int _nTicksY, float minX, float maxX, float minY, float maxY)
{
  nTicksX = _nTicksX;
  nTicksY = _nTicksY;  
  _minX = minX;      _maxX = maxX;
  _minY = minY;      _maxY = maxY;

  _xstep = xAxisLength / (_maxX - _minX);
  _ystep = yAxisLength / (_maxY - _minY);
}


void Axes::drawAll()
{   
  drawAxesLines();
  drawTicks();
}

void Axes::drawAxesLines()
{
  drawLine(xaxisStart, xaxisEnd, YELLOW);
  drawLine(yaxisStart, yaxisEnd, YELLOW);
}

void Axes::drawTicks()
{
  myGLCD.setTextSize(1);  
    
  int tickX_posX0 = _origin.x - ddpos/4;
  int tickX_posX1 = _origin.x + ddpos/4;

  int ypos = _origin.y;
  int dy = yAxisLength / nTicksY;
  
  float yVal  = _minY;
  float dyVal = (_maxY - _minY) / nTicksY;

  int txt_dx = 30;
  int txt_dy = 4;
  
  for(int i = 0; i < nTicksY; i++){
    ypos -= dy;
    yVal += dyVal;
    drawLine(Pos(tickX_posX0, ypos), Pos(tickX_posX1, ypos), WHITE);    
    drawFloat(yVal, Pos(tickX_posX0 - txt_dx, ypos - txt_dy), 1, WHITE, BLACK);
  }

  int tickY_posY0 = _origin.y + ddpos/4;
  int tickY_posY1 = _origin.y - ddpos/4;

  int xpos = _origin.x;
  int dx = xAxisLength / nTicksX;

  float xVal  = _minX;
  float dxVal = (_maxX - _minX) / nTicksX;

  txt_dx = 10;
  txt_dy = 10;
  
  for(int i = 0; i < nTicksX; i++){
    xpos += dx;
    xVal += dxVal;
    drawLine(Pos(xpos, tickY_posY0), Pos(xpos, tickY_posY1), WHITE);   
    drawFloat(xVal, Pos(xpos - txt_dx, tickY_posY0 + txt_dy), 0, WHITE, BLACK);
  }
}
