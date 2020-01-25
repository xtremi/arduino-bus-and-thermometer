#include "Graph.h"

Graph::Graph(Axes* _axes){
  axes = _axes;    
  prevPoint = axes->origin();
}

void Graph::resetGraph()
{
  axes->drawAll();
  prevPoint.x = axes->getOriginX() + (int)((0.0 - axes->minX()) * axes->xStep());
}

Pos Graph::getScreenCoords(const VecF& p)
{
  Pos screenCoord;

  screenCoord.x = axes->getOriginX() + (int)((p.x - axes->minX()) * axes->xStep()); 
  screenCoord.y = axes->getOriginY() - (int)((p.y - axes->minY()) * axes->yStep()); 

  return screenCoord;
}

void Graph::addDataPoint(const VecF& p)
{ 
    Pos newPoint = getScreenCoords(p);
    drawLine(prevPoint, newPoint, WHITE);
    prevPoint = newPoint;
}
