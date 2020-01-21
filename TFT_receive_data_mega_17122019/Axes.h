#include "DrawingUtilities.h"

class Axes{
  public:
    Axes(int _W, int _H, const Color& _col, int _xAxisLength);
    void drawAll();
    void setTicks(int _nTicksX, int _nTicksY, float _minX, float _maxX, float _minY, float _maxY);    
    void drawTicks();
    void drawAxesLines();
    
    Pos origin(){return _origin;}
    int getOriginX(){return _origin.x;}
    int getOriginY(){return _origin.y;}

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

    float _xstep, _ystep;

    Pos _origin, xaxisStart, xaxisEnd, yaxisStart, yaxisEnd;

    int nTicksX, nTicksY;
};
