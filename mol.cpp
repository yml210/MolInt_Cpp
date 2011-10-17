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

void MolCanvas::setScale(double s)
{
    scale=(GLfloat) s;
}

void MolCanvas::initializeGL()
{
    qglClearColor(black);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    GLfloat ambientLight[]={1.0,1.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);

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
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.0);
    glScalef(scale,scale,scale);

    glRotatef(xRot,1.0,0.0,0.0);
    glRotatef(yRot,0.0,1.0,0.0);
    glRotatef(zRot,0.0,0.0,1.0);

    GLfloat color[]={0.0,0.0,1.0};
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
    glutSolidCube(0.5);

    for(int i=0;i<atoms->size();i++)
    {
	cerr<<i<<endl;
//	glPushMatrix(GL_MODELVIEW_MATRIX);
        double* xyz=(*atoms)[i]->coordinate();
        GLfloat x= (GLfloat) xyz[0];
        GLfloat y= (GLfloat) xyz[1];
        GLfloat z= (GLfloat) xyz[2];
	cerr<<x<<y<<z<<endl;
        glTranslatef(x/5.0,y/5.0,z/5.0);
        glutSolidSphere(0.2,20,2);
/*
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0,0.5,0.4);
	glVertex3f(1.0,-0.5,0.4);
	glVertex3f(-1.0,-0.5,0.4);
	glVertex3f(-1.0,0.5,0.4);
	glEnd();
*/	
//	glPopMatrix(GL_MODELVIEW_MATRIX);
    }
    
    
}


    


  

