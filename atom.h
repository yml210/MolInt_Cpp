//atom.h
#ifndef ATOM_H
#define ATOM_H
#include <vector>
using namespace std;

typedef vector<int> BondList;
class Atom
{
  private:
    char atomSym[6];
    int atomNum;
    double mass;
    double coord[3];
    BondList blist;
  public:
    Atom();
    Atom(char* sym);
    Atom(char* sym,int aNum,double m);
    
    int atomicNumber();
    double atomMass();
    void coordinate(double x[3]);
    void getSymbol(char* sym); 
    BondList getBondList();
    
    void setMass(double m);        
    void moveTo(double x,double y,double z);
    void moveTo(double v[3]);
    void move(double v[3]);
    void rotate(double rotationMatrix[3][3]);

    double distance(Atom* at);
    double angle(Atom *at1,Atom *at2);

    void changeDistance(Atom* at, double r);
    void changeAngle(Atom* at1,Atom* at2,double alpha);

    void addBond(int index);
    void removeBond(int index);
};

#endif //ATOM_H

/*
class Cluster
{
  private:
    int numOfAtoms;
    list<Atom*> atoms;
    double mass;
    double CenterOfMass[3];
  public:
    Cluster(Atom** atoms,int num);
    void addAtom(Atom* atom);
    void removeAtom(Atom* atom);
}
*/
    
  



