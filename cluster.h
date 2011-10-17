//cluster.h

#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include "atom.h"

typedef vector<Atom*> VAtoms;

typedef VAtoms* Atoms;
class Cluster
{
  public:
    
    Cluster();

    double getMass();
    void getInertia(double inert[3]);
    void getCoordinate(double r[3]);
    void getOreintation(double ore[3][3]);
    Atoms getAtomsList();
    Atom* getAtom(int i);
    void getAtomCoord(int i,double x[3]);
    int listSize();
    double  maxCharaLength();
    double  minCharaLength();

    void changeCOM(double x,double y,double z);
    void moveCOMTo(double v[3]);
    void move(double v[3]);
    void rotate(double angle[3]);
    void rotate(double rotMatrix[3][3]);

    void frameTranslate(double v[3]);
    void frameRotate(double angle[3]);        
    
    void setAtomScale(double s);
    void setScale(double s);
    void addAtoms(Atoms ats);
    void removeAtoms(Atoms ats);
    void addBond(Atom*,Atom*);
    void addBond(int index1,int index2);
    void removeBond(Atom*,Atom*);
    void removeBond(int index1,int index2);
    int findAtom(Atom*);


  private:
    double* principleFrame();
    void Imatrix(double im[3][3]);
    void setOreintation();
    void setOreintation(double rotMatrix[3][3]);
    void setCenterOfMass();
    void removeAtom(int i);
    void removeBond(int index);
  private:

    double mass;
    double inertiaOfMomentum[3];
    double coordinate[3];
    double oreintation[3][3];
    Atoms atoms;
    double maxCharactorLength;
    double minCharactorLength;
    double atomScale;
    double scale;    
};

#endif //CLUSTER_H































