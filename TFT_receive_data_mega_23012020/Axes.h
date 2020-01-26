#include "DrawingUtilities.h"
#define MAX_X_AXES 3

class Axis {
public:
	Axis(int _W, int _H, const Pos& _pos, const Color& _col, int _length);
	void draw();
	void setTicks(int _nTicks, float _minVal, float _maxVal);

protected:
	void drawAxisLine();
	virtual void drawTicks() = 0;

	Color color;
	Pos   origin, axisStart, axisEnd;
	
	int nTicks;

	int axisLength;
	int sW, sH;
	int dpos, ddpos;

	float minValue = 0.0f;
	float maxValue = 0.0f;
	
	float step = 0.0f;	// screen coords per value
	float dVal = 0.0f;	// step length in value
	float dl   = 0.0f;	// step length in screen coords

	int txt_dx;
	int txt_dy;
};


class YAxis : public Axis
{
public:
	YAxis(int _W, int _H, const Pos& _pos, const Color& _col, int _length);	
protected:
	void drawTicks();


};


class XAxis : public Axis
{
public:
	XAxis(int _W, int _H, const Pos& _pos, const Color& _col, int _length);
protected:
	void drawTicks();
};



class Axes{
  public:
    Axes(int _W, int _H, const Pos& _pos, const Color& _col, int _xAxisLength, int _yAxisLength);
    void drawAll();
    void setTicks(int _nTicksX, int _nTicksY, float _minX, float _maxX, float _minY, float _maxY);    
    void drawTicks();
	void drawXticks();
	void drawYticks();
    void drawAxesLines();
    
    Pos origin(){return _origin;}
    int originX(){return _origin.x;}
    int originY(){return _origin.y;}

    float xStep(){return _xstep;}
    float yStep(){return _ystep;}
    float minX(){return _minX;}
    float maxX(){return _maxX;}
    float minY(){return _minY;}
    float maxY(){return _maxY;}
    
  private:  
    Color col;
    int xAxisLength, yAxisLength;
    int sW, sH;
    int dpos, ddpos;

    float _minX = 0;
    float _maxX = 10;
    float _minY = 0;
    float _maxY = 10;
	
	float _xstep = 0.0f;	//screen coords per value
	float _ystep = 0.0f;
	float dxVal  = 0.0f;	//step length in value
	float dyVal  = 0.0f;
	float dx	 = 0.0f;	//step length in screen coords
	float dy	 = 0.0f;

  
    Pos _origin, xaxisStart, xaxisEnd, yaxisStart, yaxisEnd;

    int nTicksX, nTicksY;
};
