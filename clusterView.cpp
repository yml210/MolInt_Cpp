//clusterView.cpp

#include <GL/glut.h>
#include <vector>
#include "clusterView.h"
#include "utility.h"

ClusterView::ClusterView()
{
  cluster=0;
  scale=10.0;
  drawBondOrNot=true;
  qobj=gluNewQuadric();
}

ClusterView::ClusterView(Cluster *c)
{
  cluster=c;
  scale=10.0;
  drawBondOrNot=true;
  qobj=gluNewQuadric();
}

ClusterView::~ClusterView()
{
  gluDeleteQuadric(qobj);
}

void ClusterView::setCluster(Cluster* c)
{
  cluster=c;
  emit clusterChanged(cluster);
}

void ClusterView::setScale(double s)
{
  scale=s;
  emit scaleChanged(s);
}

double ClusterView::getScale()
{
  return scale;
}


void ClusterView::move(double r[3])
{
  for(int i=0;i<3;i++){
    r[i]=-r[i];
  }
  cluster->frameTranslate(r);
}

void ClusterView::rotate(double angle[3])
{
  cluster->rotate(angle);
}

void ClusterView::draw(GLenum mode)
{
  double xx[3], R[3];
  
  cluster->getCoordinate(R);
  int size=cluster->listSize();
    
  setupQuadObj(qobj);

  GLfloat specref[]={0.7,0.7,0.7,1.0};
  glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
  glMateriali(GL_FRONT,GL_SHININESS,80);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
//  glPopMatrix();
//  glColor3f(0.5,0.6,0.2);
//  glutSolidSphere(0.1,20,30);

  for(int i=0;i<size;i++){
    cluster->getAtomCoord(i,xx);
    GLfloat x=(GLfloat) xx[0]/scale;
    GLfloat y=(GLfloat) xx[1]/scale;
    GLfloat z=(GLfloat) xx[2]/scale;
    glPushMatrix();
    glColor3f(0.5,0.6,0.2);
    glTranslatef(x,y,z);
    if(mode==GL_SELECT)
             glLoadName(i+1);
    glutSolidSphere(0.08,20,30);
    if(drawBondOrNot){
      Atom* at=cluster->getAtom(i);
      drawBond(at);
   } 
    glPopMatrix();
  }

}

void ClusterView::setupQuadObj(GLUquadricObj *obj)
{
  gluQuadricDrawStyle(obj,GLU_FILL);
  gluQuadricNormals(obj,GLU_SMOOTH);
}

void ClusterView::drawBond(Atom* at)
{
  double n1[]={0.0,0.0,0.0};
  double n2[]={0.0,0.0,1.0};
  double angle[3],r[3],r1[3],n[3],height;
  BondList bonds=at->getBondList();
  at->coordinate(r);
  glColor3f(0.2,0.6,0.5);
  for(int i=0;i<bonds.size();++i){
    glPushMatrix();
    Atom* at1=cluster->getAtom(bonds[i]);
    at1->coordinate(r1);
    util::vminusv(r,r1,n);
    GLfloat height=(GLfloat) util::mode(n,3)/scale;
    util::normalize(n);
    if((n[0]!=0.0)||(n[1]!=0.0)){
      util::vecProd(n,n2,n1);
      util::normalize(n1);
      util::vecProd(n,n1,n2);
      util::eularAngles(n1,n2,n,angle);
     }else{
       for(int j=0;j<3;++j) angle[j]=n1[j];
     }

    GLfloat phi=(GLfloat) util::toDegree(angle[0]);
    GLfloat theta=(GLfloat) util::toDegree(angle[1]);

    glRotatef(phi,0.0,0.0,1.0);
    glRotatef(theta,0.0,1.0,0.0); 
    gluCylinder(qobj,0.06,0.03,height,60,40);
    glPopMatrix();
  }
}
    
  
int ClusterView::listSize()
{
  return cluster->listSize();
}

Atom* ClusterView::getAtom(int i)
{
  return cluster->getAtom(i);
}

bool ClusterView::bDrawBond()
{
  return drawBondOrNot;
}

void ClusterView::setDrawBond(bool b)
{
  if(b){
    drawBondOrNot=true;
  }else{
    drawBondOrNot=false;
  }
}
void ClusterView::close()
{};    
  
void ClusterView::addBond(int index1,int index2)
{
  cluster->addBond(index1,index2);
}

void ClusterView::removeBond(int index1,int index2)
{
  cluster->removeBond(index1,index2);
}




