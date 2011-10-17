#include <qwidget.h>
#include "molCanvas.h"

struct Coordinate{
  double x;
  double y;
  double z;
};


class MolWin: public QWidget
{
  public:
    MolWin(QWidget* parent=0,char* name=0);
 private:
    void getCoordinate(Coordinate* v,int natom);
  private:
    MolCanvas* canvas;
};









