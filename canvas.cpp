#include <GL/glut.h>
#include "canvas.h"
#include "utility.h"
#include <iostream>

Canvas::Canvas(QWidget* parent,char* name)
         :QGLWidget(parent,name)
{
	cluster=0;
	type=CLUSTER;
 	double tmp[3]={0.0,0.0,0.0};
        for(int i=0;i<3;++i){
        fixAngle[i]=tmp[i];
        eularAngle[i]=tmp[i]; 
	}
}

Canvas::~Canvas()
{
}

void Canvas::initializeGL()
{
    qglClearColor(Qt::blue);
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    
    glEnable(GL_LIGHTING);
    
    GLfloat ambientLight[]={0.5,0.5,0.5,1.0};
    GLfloat diffuseLight[]={0.8,0.8,0.8,1.0};
    GLfloat specular[]={0.8,0.8,0.8,1.0};

    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    
    GLfloat lightPos[]={1.0,0.0,1.0,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.0);

}

void Canvas::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,5.0,15.0);
    glMatrixMode(GL_MODELVIEW);
}

void Canvas::paintGL()
{
  if(cluster!=0){
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   rotate(fixAngle);
   rotateEular(eularAngle);
   cluster->draw();
   glPopMatrix();
  }
}

void Canvas::setObject(ClusterView* c,ObjectType t)
{
  cluster= c;
  updateGL();
}

bool Canvas::isEmpty(ObjectType t)
{
  switch(t){
    case CLUSTER:
      if(cluster==0){
	 return true;  
      }
      break;
/*
    case SYSTEM:
      if(system==0){
         return true;
      }
      break;
*/
    default:
      break;
  }
  return false;
}

Canvas::ObjectType Canvas::currentViewType()
{
  return type;
}
void Canvas::setCurrentViewType(ObjectType t)
{
  type=t;
}

ClusterView* Canvas::getClusterView()
{
  return cluster;
}

void* Canvas::getView(ObjectType t)
{
  switch(t){
  case CLUSTER:
    return cluster;
/*
  case SYSTEM:
    return sytem;
*/
  default:
    return 0;
  }
}

void Canvas::increaseFixAngle(int i)
{
  changeFixAngle(10.0,i);
}

void Canvas::changeFixAngle(double delta,int i)
{
   switch(i){
     case 0:
       fixAngle[0]+=delta;
       break;
     case 1:
       fixAngle[1]+=delta;
       break;
     case 2:
       fixAngle[2]+=delta;
       break;
   }
   updateGL();
}

void Canvas::setFixAngle(double angle[3])
{
   util::vcopy(angle,fixAngle,3);
   updateGL();
}

void Canvas::setEularAngle(double angle[3])
{
   util::vcopy(angle,eularAngle,3);
   updateGL();
}

void Canvas::rotateEular(double angle[3])
{
  GLfloat alpha=(GLfloat) angle[0];
  GLfloat belta=(GLfloat) angle[1];
  GLfloat theta=(GLfloat) angle[2];

  glRotatef(alpha,1.0,0.0,0.0);
  glRotatef(belta,0.0,1.0,0.0);
  glRotatef(theta,0.0,0.0,1.0);
}

void Canvas::rotate(double angle[3])
{
  GLfloat alpha=(GLfloat) angle[0];
  GLfloat belta=(GLfloat) angle[1];
  GLfloat theta=(GLfloat) angle[2];

  glRotatef(alpha,1.0,0.0,0.0);
  glRotatef(belta,0.0,1.0,0.0);
  glRotatef(theta,0.0,0.0,1.0);
//  glPushMatrix();
}

void Canvas::xRotate()
{
   increaseFixAngle(0);
}

void Canvas::yRotate()
{
   increaseFixAngle(1);
}

void Canvas::zRotate()
{
   increaseFixAngle(2);
}

void Canvas::mouseMoveEvent(QMouseEvent *e)
{
  if(cluster==0) return;
  double x1=e->x();
  double y1=e->y();
  double dx=x1-mousePos.x();
  double dy=y1-mousePos.y();

  mousePos.setX(x1);
  mousePos.setY(y1);
  
  changeFixAngle(dx/5.0,1);
  changeFixAngle(dy/5.0,0);
  
}

void Canvas::mousePressEvent(QMouseEvent *e)
{
   mousePos=e->pos();
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *e)
{
   if(cluster==0) return;
   GLuint selectBuf[BUFSIZE];
   GLint viewport[4];
   GLfloat x=(GLfloat) e->x();
   GLfloat y=(GLfloat) e->y();

   glGetIntegerv(GL_VIEWPORT,viewport);
   glSelectBuffer(BUFSIZE, selectBuf);
   (void) glRenderMode(GL_SELECT);

   glInitNames();
   glPushName(0);


   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   gluPickMatrix(x,viewport[3]-y,5.0,5.0,viewport);
   glFrustum(-1.0,1.0,-1.0,1.0,5.0,15.0);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   rotate(fixAngle);
   cluster->draw(GL_SELECT);
   glPopMatrix();

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glFlush();

   GLint hits=glRenderMode(GL_RENDER);
   processHits(hits,selectBuf);
}
   
void Canvas::processHits(GLint hits, GLuint buffer[])
{
   int index=findNearestObject(hits,buffer);
   if(index==-1) return;
   emit objectSelected(index);
}


int Canvas::findNearestObject(GLint hits,GLuint buffer[])
{
  unsigned int i,j;

  GLuint names,*ptr;
  float minDepth=100.0;
  GLint nearest=0;

  ptr=(GLuint *) buffer;
    cout<<"hits= "<<hits<<endl;
  for(i=0;i<hits;i++){
    names=*ptr;
    cout<<"number of names for hit= "<<names<<endl;
    ptr++;
    float z1=(float) *ptr/0x7fffffff;
    cout<<"z1 is "<<z1<<endl;
    if(z1<minDepth){
      minDepth=z1;
      nearest=*(ptr+2);
    }
    ptr++;
    cout<<"z2 is "<<(float) *ptr/0x7fffffff<<endl;
    ptr++;
    for(j=0;j<names;j++){
      cout<<*ptr<<endl;
      ptr++;
    }
    cout<<"the nearest is "<<nearest<<endl;
    cout<<endl;
  }
  return nearest-1;
}
  


