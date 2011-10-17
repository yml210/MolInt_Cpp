#include <GL/glut.h>
#include <algorithm>
#include "molCanvas.h"
#include <iostream>

MolCanvas::MolCanvas(QWidget* parent,char* name)
         :QGLWidget(parent,name)
{
  atoms=new vector<Atom*>;
  xRot=0.0;
  yRot=0.0;
  zRot=0.0;
  scale=1.0;
}

MolCanvas::~MolCanvas()
{
  delete atoms;
}

void MolCanvas::addAtom()
{
    Atom* at=new Atom();
    atoms->push_back(at);
}

void MolCanvas::addAtom(Atom* at)
{
    atoms->push_back(at);
}

void MolCanvas::removeAtom(Atom* at)
{
    vector<Atom*>::iterator it=std::find(atoms->begin(),atoms->end(),at);
    atoms->erase(it);
}

void MolCanvas::setRotAngle(double angleX,double angleY,double angleZ)
{
    xRot=(GLfloat) angleX;
    yRot=(GLfloat) angleY;
    zRot=(GLfloat) angleZ;
}

void MolCanvas::increaseXRot()
{
  xRot+=10.0;
  if(xRot>360.0)
    xRot-=360.0;
  updateGL();
}

void MolCanvas::increaseYRot()
{
  yRot+=10.0;
  if(yRot>360.0)
    yRot-=360.0;
  updateGL();
}

void MolCanvas::increaseZRot()
{
  zRot+=10.0;
  if(zRot>360.0)
    zRot-=360.0;
  updateGL();
}
void MolCanvas::setScale(double s)
{
    scale=(GLfloat) s;
}

void MolCanvas::initializeGL()
{
    qglClearColor(black);
    glShadeModel(GL_SMOOTH);
    
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    
    glEnable(GL_LIGHTING);
    
    GLfloat ambientLight[]={0.2,0.2,0.2,1.0};
    GLfloat diffuseLight[]={0.7,0.7,0.7,1.0};
    GLfloat specular[]={7.0,7.0,0.7,1.0};

    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    
    GLfloat lightPos[]={-8.0,10.0,100,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    
    glEnable(GL_LIGHT0);
}

void MolCanvas::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,5.0,15.0);
    glMatrixMode(GL_MODELVIEW);
}

void MolCanvas::paintGL()
{    
    GLfloat specref[]={0.5,0.5,0.5,1.0};
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,60);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.0);
   
    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);
    glRotatef(zRot,0.0,0.0,1.0);
    
    glColor3f(0.3,0.7,0.2);
    glutSolidCube(1.0);

    glColor3f(0.5,0.6,0.2);
    //   glScalef(scale,scale,scale);     

    for(int i=0;i<atoms->size();i++)
    {
        glPushMatrix();
        double* xyz=(*atoms)[i]->coordinate();
        GLfloat x= (GLfloat) xyz[0];
        GLfloat y= (GLfloat) xyz[1];
        GLfloat z= (GLfloat) xyz[2];
        glTranslatef(x/10.0,y/10.0,z/10.0);
        glutSolidSphere(0.1,20,20);
	glPopMatrix();
    }
     
}


    


  

