//atom.cpp
#include "atom.h"
#include "utility.h"
#include <math.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>

Atom::Atom()
{
  atomSym[0]='\0';
  int atomNum=0;
  mass=0.0;
  coord[0]=0.0;
  coord[1]=0.0;
  coord[2]=0.0;
}

Atom::Atom(char* sym)
{
  Atom();
  strcpy(atomSym,sym);
}

Atom::Atom(char* sym,int aNum,double m)
{
  strcpy(atomSym,sym);
  atomNum=aNum;
  mass=m;
}

int Atom::atomicNumber()
{
  return atomNum;
}

double Atom::atomMass()
{
  return mass;
}

void Atom::getSymbol(char* sym)
{
  strcpy(sym,atomSym);
}
BondList Atom::getBondList()
{
   return blist;
}
void Atom::setMass(double m)
{
   mass=m;
}

void Atom::coordinate(double x[3])
{
	for(int i=0;i<3;++i){
	  x[i]=coord[i];
	}
// util::vcopy(coord,x,3); 
}

void Atom::moveTo(double x,double y,double z)
{
  coord[0]=x;
  coord[1]=y;
  coord[2]=z;
}

void Atom::moveTo(double v[3])
{
    for(int i=0;i<3;i++){
        coord[i]=v[i];
    }
}

void Atom::move(double v[3])
{
    for(int i=0;i<3;i++){
        coord[i]+=v[i];
    }
}

void Atom::rotate(double rotationMatrix[3][3])
{
    util::rotate(coord,rotationMatrix);
}

double Atom::distance(Atom* at)
{
    double tmp[3];
    at->coordinate(tmp);
    return util::distance(tmp,coord,3);
}

double Atom::angle(Atom *at1,Atom *at2)
{
    double d1,d2,d3,tmp;
    d1=this->distance(at1);
    d2=at1->distance(at2);
    d3=at2->distance(this);
    if((d1==0)||(d2==0)){
	cerr<< "Atom::angle:"<<endl
	    <<"d1= "<<d1<<endl
	    <<"d2= "<<d2<<endl;
	return -1.0;
    }

    tmp=acos((d1*d1+d2*d2-d3*d3)/(2.0*d1*d2));
    return util::toDegree(tmp);
}
    
void Atom::changeDistance(Atom* at, double r)
{
    double r1[3],r2[3],tmp[3],m;
    this->coordinate(r1);
    at->coordinate(r2);
    m=this->distance(at);
    if(m==0.0){
      cerr<<"Atom::changeDistance: distance="<<m<<endl;
      return;
    }
    for(int i=0;i<3;i++){
      tmp[i]=(r1[i]-r2[i])*(r-m)/m;
    }
   
    this->move(tmp);
}
    	
void Atom::changeAngle(Atom *at1,Atom *at2,double angle)
{
  double r1[3],r2[3],r[3],a[3],b[3];
  this->coordinate(r);
  at1->coordinate(r1);
  at2->coordinate(r2);
  angle=util::toArc(angle);

  util::vminusv(r1,r,a);
  util::vminusv(r1,r2,b);

  util::changeAngle1(a,b,angle,r);

  util::vplusv(r1,r,b);
  this->moveTo(b);
} 
  
void Atom::addBond(int index)
{
  bool found_it=binary_search(blist.begin(),blist.end(),index);       
  if(!found_it){
    blist.push_back(index);
    sort(blist.begin(),blist.end());
  }
}

void Atom::removeBond(int index)
{
  vector<int>::iterator p=
	find(blist.begin(),blist.end(),index);
  if(p!=blist.end()){
    blist.erase(p);
  }
}








