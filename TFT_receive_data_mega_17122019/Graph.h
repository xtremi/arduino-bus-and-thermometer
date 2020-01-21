#include "Axes.h"

class Graph
{
  public:
    Graph(Axes* _axes);

    void addDataPoint(const VecF& p);
    void resetGraph();
    
    private:
      Axes* axes = nullptr;
      Pos prevPoint;

      Pos getScreenCoords(const VecF& p);
      
};   
