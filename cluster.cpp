//cluster.cpp

#include <iostream>
#include "cluster.h"
#include "utility.h"


Cluster::Cluster()
{
    for(int i=0;i<3;i++){
        coordinate[i]=0.0;
	inertiaOfMomentum[i]=0.0;
        for(int j=0;j<3;j++){
            oreintation[i][j]=0.0;
        }
        oreintation[i][i]=1.0;
    }
    
    atoms=new VAtoms;
    mass=0.0;
    maxCharactorLength=0.0;
    minCharactorLength=0.0;
    scale=1.0;   

}

double Cluster::getMass()
{
    return mass;
}

void Cluster::getInertia(double inert[3])
{
    for(int i=0;i<3;++i){
        
        inert[i]=inertiaOfMomentum[i];
    }
    
}

void Cluster::getCoordinate(double r[3])
{
    for(int i=0;i<3; ++i){
        r[i]=coordinate[i];

    }
}

    

void Cluster::getOreintation(double ore[3][3])
{
  util::mcopy(oreintation,ore);
}

Atoms Cluster::getAtomsList()
{
    return atoms;
}

Atom* Cluster::getAtom(int i)
{
  if((i>-1)&&(i<atoms->size())){
    return (*atoms)[i];
  }else
  {
    cout<<"No atom found!"<<endl;
  }
}

void Cluster::getAtomCoord(int i,double x[3])
{
  Atom* at=getAtom(i);
  at->coordinate(x);
}

int Cluster::listSize()
{
  return atoms->size();
}

double Cluster::maxCharaLength()
{
    return maxCharactorLength;
}

double Cluster::minCharaLength()
{
    return minCharactorLength;
}

void Cluster::setAtomScale(double s)
{
    atomScale=s;
}

void Cluster::setScale(double s)
{
    scale=s;
}

void Cluster::addAtoms(Atoms ats)
{
    if(atoms!=0){
      int size=(int) ats->size();

      Atom* at;
        for(int i=0;i<size;i++){
	  at=(*ats)[i];
          atoms->push_back(at);
        }
        //ats->erase(ats->begin(),ats->end());
       	//delete ats;
    }
    else{
	*atoms=*ats;
    }
    setCenterOfMass();
    setOreintation();
}

void Cluster::removeAtom(int i)
{
    if((i > -1)&&(i < listSize()))
    {
        VAtoms::iterator it=atoms->begin();
        it+=i;
        Atom* tmp=*it;
        atoms->erase(it);
        delete tmp;
        removeBond(i);
    }
    else
    {
        cerr<<"Cluster::removeAtom(int i):"<<endl
            <<"i must be greater than -1 and less than size of atoms"
            <<endl;
    }       
}

void Cluster::removeBond(int index)
{
  Atom *at;
  for(int i=0;i<atoms->size();i++){
    at=(*atoms)[i];
    at->removeBond(i);
  }
}

void Cluster::removeBond(int index1,int index2)
{
  double ind1,ind2;
  if(index1>index2){
    ind1=index2;
    ind2=index1;
  }else if(index1<index2){
    ind1=index1;
    ind2=index2;
  }else{
    cerr<<"Cluster::addBond: index1=index2= "
        <<index1<<endl;
  }
  Atom* at=getAtom(ind1);
  at->removeBond(ind2);
}

void Cluster::removeBond(Atom* at1,Atom* at2)
{
  int index=findAtom(at1);
  at2->removeBond(index);
  index=findAtom(at2);
  at1->removeBond(index);
}

void Cluster::removeAtoms(Atoms ats)
{
    int count=0;
    int size=ats->size();
    vector<int> *index=new vector<int>;
    Atom *at1,*at2;

    for(int i=0;i<size;i++){
      at1=(*ats)[i];
        for(int j=0;j<listSize();j++){
	  at2=getAtom(j);
            if(at1==at2){
                index->push_back(j);
                count++;
            }
        }
    }

    for(int i=0;i<count;i++){
        int n=index->back();
        removeAtom(n);
        index->pop_back();
    }

    delete index;
    
    if(count!=size)
        cerr<<"Cluster::removeAtoms:"<<endl
            <<"count="<<count<<endl
            <<"ats->size()="<<size<<endl;
    ats->erase(ats->begin(),ats->end());
    delete ats;
    setCenterOfMass();
    setOreintation();
}

void Cluster::addBond(Atom* at1,Atom* at2)
{
  int index=findAtom(at2);
  at1->addBond(index);
}

void Cluster::addBond(int index1,int index2)
{
  double ind1,ind2;
  if(index1>index2){
    ind1=index2;
    ind2=index1;
  }else if(index1<index2){
    ind1=index1;
    ind2=index2;
  }else{
    cerr<<"Cluster::addBond: index1=index2= "
        <<index1<<endl;
  }

  Atom* at=getAtom(ind1);
  at->addBond(ind2);
}

int Cluster::findAtom(Atom* at2)
{
  for(int i=0;i<atoms->size();i++){
    if(at2==(*atoms)[i]){
      return i;
    }
  }
  cerr<<"Cluster::findAtom: the Atom is not found!"<<endl;
}

void Cluster::setCenterOfMass()
{
    double totleMass=0.0;
    double tmp[3]={0.0,0.0,0.0};
    double x[3];
    Atom* at;
    
    for(int i=0;i<listSize();i++){
        at=(*atoms)[i];
        at->coordinate(x);
        double m=at->atomMass();
        totleMass+=m;
        for(int j=0;j<3;j++){
            tmp[j]+=x[j]*m;
        }
    }
    if(totleMass!=0){
        mass=totleMass;
        
        changeCOM(tmp[0]/totleMass,
                  tmp[1]/totleMass,tmp[2]/totleMass);
        
    }
    else{
        cerr<<"Cluster::setCenterOfMass: totleMass=0"<<endl;
    }
}
    
void Cluster::changeCOM(double x,double y,double z)
{
    coordinate[0]=x;
    coordinate[1]=y;
    coordinate[2]=z;
}

void Cluster::move(double v[3])
{
    for(int i=0;i<3;i++){
        coordinate[i]+=v[i];
    }

    for(int i=0;i<atoms->size();i++){
        (*atoms)[i]->move(v);
    }
}

void Cluster::moveCOMTo(double v[3])
{
    for(int i=0;i<3;i++){
        v[i]-= coordinate[i];
    }

    move(v);
}

void Cluster::frameTranslate(double v[3])
{
    for(int i=0;i<3;i++){
        v[i]*=-1.0;
    }
    move(v);
}


void Cluster::rotate(double angle[3])
{
    double rotMatrix[3][3];
    util::rotationMatrix(angle,rotMatrix);
    rotate(rotMatrix);
}

void Cluster::rotate(double rotMatrix[3][3])
{
    for(int i=0;i<atoms->size();i++){
        (*atoms)[i]->rotate(rotMatrix);
    }
    setOreintation(rotMatrix);
}
/*
void Cluster::frameRotate(double rotmatrix[3][3])
{
  double inverseMatrix[3][3];
  util::inverse(rotMatrix,inverseMatrix);
  rotate(inverseMatrix);
}
*/

void Cluster::Imatrix(double im[3][3])
{
  
  double m1,rr,r1[3],r2[3];
  Atom* at;
  int size=listSize();
  getCoordinate(r2);

  for(int m=0;m<3;m++){
    for(int n=0;n<3;n++){
      im[m][n]=0.0;
    }
  }

  for(int i=0;i<size;i++){
    at=(*atoms)[i];
    at->coordinate(r1);
    m1=at->atomMass();
    rr=util::distance(r1,r2,3);
    
    for(int m=0;m<3;m++){
      for(int n=0;n<3;n++){
      	im[m][n]=im[m][n]-m1*(r1[m]-r2[m])*(r1[n]-r2[n]);
	if(m==n)
	  im[m][n]=im[m][m]+m1*rr;
      }
    }   
  }
  
}

void Cluster::setOreintation()
{
  double im[3][3],it[3][3],iv[3];
  Imatrix(im);
  util::dsyev(im,it,iv);
  util::transpose(it,oreintation);
  util::vcopy(iv,inertiaOfMomentum,3);
}

void Cluster::setOreintation(double rotMatrix[3][3])
{
  double im[3][3],tmp[3][3];
  util::inverse(rotMatrix,im);
  util::mcopy(oreintation,tmp);
  util::dgemm(tmp,im,oreintation);
}
























