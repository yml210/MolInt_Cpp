//canvas.h

#ifndef CANVAS_H
#define CANVAS_H
#define QT3_SUPPORT

#include <Qt/qgl.h>
#include "clusterView.h"

#define BUFSIZE 512

typedef void (*DRAW)(void);

class Canvas:public QGLWidget
{
  Q_OBJECT
    
  public:
  	Canvas(QWidget* parent, char* name);
  	~Canvas();

	enum ObjectType{CLUSTER};
	void setObject(ClusterView* c,ObjectType t);
        bool isEmpty(ObjectType);
        ObjectType currentViewType();
	void setCurrentViewType(ObjectType);
        ClusterView* getClusterView();
        void* getView(ObjectType);
  public slots:
    void xRotate();
    void yRotate();
    void zRotate();
    void setFixAngle(double angle[3]);
    void setEularAngle(double angle[3]);
  signals:
    void objectSelected(int);
	
  protected:
  	void initializeGL();
  	void paintGL();
  	void resizeGL(int w,int h);
        void mouseMoveEvent(QMouseEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseDoubleClickEvent(QMouseEvent *);
 private:
       void increaseFixAngle(int i);
       void changeFixAngle(double beta,int i);
       void rotateEular(double angle[3]);
       void rotate(double angle[3]);
       void processHits(GLint,GLuint *);
       int findNearestObject(GLint,GLuint*);

 private:
       ClusterView* cluster;
       ObjectType type;
       double fixAngle[3];
       double eularAngle[3];
       QPoint mousePos;
};  
#endif //CANVAS_H  














