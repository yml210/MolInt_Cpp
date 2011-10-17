//clusterView.h

#ifndef CLUSTERVIEW_H
#define CLUSTERVIEW_H

#include <QtOpenGL/qgl.h>
#include "cluster.h"
#include <GL/glu.h>

class ClusterView:public QObject
{
    Q_OBJECT
public:
  ClusterView();
  ClusterView(Cluster *c);
  ~ClusterView();

  void draw(GLenum mode=GL_RENDER);
  int listSize();
  Atom* getAtom(int i);
  void addBond(int index1,int index2);
  void removeBond(int index1,int index2);
public slots:
  void move(double r[3]);
  void rotate(double angle[3]);
  void setCluster(Cluster *c);
  void setScale(double s);
  double getScale();
//?  void cache();
  
  bool bDrawBond();
  void setDrawBond(bool);
  void close();

signals:
  void scaleChanged(double);
  void clusterChanged(Cluster*);

private:
  void drawBond(Atom*);
  void setupQuadObj(GLUquadricObj *obj);
private:
  
  GLUquadricObj *qobj;
  Cluster* cluster;
  double scale;
  bool drawBondOrNot;
};   
 
#endif //clusterView.h



































































