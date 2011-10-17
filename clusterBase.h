//clusterBase.h

#include <qobject.h>
#ifndef CLUSTERBASE_H
#define CLUSTERBASE_H
class ClusterBase:public QObject
{
  public:
    ClusterBase(){};
    virtual void  draw()=0;
};
#endif //CLUSTERBASE_H
