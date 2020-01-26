#include "Axes.h"

Axis::Axis(int _W, int _H, const Pos& _pos, const Color& _col, int _length)
{
	sW			= _W; 
	sH			= _H;
	origin		= _pos;
	color		= _col;
	axisLength	= _length;

	dpos  = axisLength / 10;
	ddpos = dpos / 2;
}

YAxis::YAxis(int _W, int _H, const Pos& _pos, const Color& _col, int _length)
	: Axis(_W, _H, _pos, _col, _length) 
{
	axisStart = Pos(origin.x, sH - dpos + ddpos);
	axisEnd = Pos(origin.x, dpos);

	txt_dx = 10;
	txt_dy = 10;
}
XAxis::XAxis(int _W, int _H, const Pos& _pos, const Color& _col, int _length)
	: Axis(_W, _H, _pos, _col, _length) 
{
	axisStart = Pos(origin.x - ddpos, origin.y);
	axisEnd = Pos(origin.x + axisLength, origin.y);

	txt_dx = 30;
	txt_dy = 4;
}


void Axis::draw()
{
	drawAxisLine();
	drawTicks();
}

void Axis::setTicks(int _nTicks, float _minVal, float _maxVal)
{
	nTicks   = _nTicks;	
	minValue = _minVal;
	maxValue = _maxVal;

	step = axisLength / (maxValue - minValue);
	dl   = axisLength / nTicks;	
	dVal = (maxValue - minValue) / nTicks;	
}

void Axis::drawAxisLine()
{
	drawLine(axisStart, axisEnd, color);
}

void YAxis::drawTicks()
{
	int tickX_posY0 = origin.y + ddpos / 4;
	int tickX_posY1 = origin.y - ddpos / 4;

	int   xpos = origin.x;
	float xVal = minValue;

	for (int i = 0; i < nTicks; i++) {
		xpos += dl;
		xVal += dVal;
		drawLine(Pos(xpos, tickX_posY0), Pos(xpos, tickX_posY1), WHITE);
		drawFloat(xVal, Pos(xpos - txt_dx, tickX_posY0 + txt_dy), 0, WHITE, BLACK);
	}
}

void XAxis::drawTicks()
{
	int tickY_posX0 = origin.x - ddpos / 4;
	int tickY_posX1 = origin.x + ddpos / 4;

	int   ypos = origin.y;
	float yVal = minValue;

	for (int i = 0; i < nTicks; i++) {
		ypos -= dl;
		yVal += dVal;
		drawLine(Pos(tickY_posX0, ypos), Pos(tickY_posX1, ypos), WHITE);
		drawFloat(yVal, Pos(tickY_posX0 - txt_dx, ypos - txt_dy), 1, WHITE, BLACK);
	}
}


/*
_W				- screen width
_H				- screen height
_pos			- origin position (screen coords)
_col			- axes color
_xAxisLengths   - length of xaxis
_yAxisLengths   - length of yaxis
*/
Axes::Axes(int _W, int _H, const Pos& _pos, const Color& _col, int _xAxisLength, int _yAxisLength)
{ 
  sW           = _W;
  sH           = _H;
  col         = _col;
  xAxisLength = _xAxisLength;
  yAxisLength = _yAxisLength;

  dpos  = xAxisLength/10;
  ddpos = dpos/2;
 
  _origin    = _pos;
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

  dx = xAxisLength / nTicksX;
  dy = yAxisLength / nTicksY;

  dxVal = (_maxX - _minX) / nTicksX;
  dyVal = (_maxY - _minY) / nTicksY;
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

void Axes::drawXticks()
{
	int tickY_posX0 = _origin.x - ddpos / 4;
	int tickY_posX1 = _origin.x + ddpos / 4;

	int   ypos = _origin.y;
	float yVal = _minY;

	const int txt_dx = 30;
	const int txt_dy = 4;

	for (int i = 0; i < nTicksY; i++) {
		ypos -= dy;
		yVal += dyVal;
		drawLine(Pos(tickY_posX0, ypos), Pos(tickY_posX1, ypos), WHITE);
		drawFloat(yVal, Pos(tickY_posX0 - txt_dx, ypos - txt_dy), 1, WHITE, BLACK);
	}
}

void Axes::drawYticks()
{
	int tickY_posX0 = _origin.x - ddpos / 4;
	int tickY_posX1 = _origin.x + ddpos / 4;

	int   ypos = _origin.y;
	float yVal = _minY;

	const int txt_dx = 30;
	const int txt_dy = 4;

	for (int i = 0; i < nTicksY; i++) {
		ypos -= dy;
		yVal += dyVal;
		drawLine(Pos(tickY_posX0, ypos), Pos(tickY_posX1, ypos), WHITE);
		drawFloat(yVal, Pos(tickY_posX0 - txt_dx, ypos - txt_dy), 1, WHITE, BLACK);
	}
}

void Axes::drawTicks()
{
  myGLCD.setTextSize(1);      
  drawYticks();
  drawXticks();
}
