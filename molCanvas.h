#include <qgl.h>
#include <vector>
#include "atom.h"

class MolCanvas:public QGLWidget
{
  Q_OBJECT
    
  public:
  	MolCanvas(QWidget* parent, char* name);
  	~MolCanvas();

  public slots:
  	void addAtom();
        void addAtom(Atom * at);
  	void removeAtom(Atom* at);
  	void setRotAngle(double angleX,double angleY,double angleZ);
  	void setScale(double s);
	void increaseXRot();
	void increaseYRot();
	void increaseZRot();
/*  
  signals:
        void atomAdded();
  	void atomAdded(Atom*);
  	void atomRemoved(Atom*);
*/
  protected:
  	void initializeGL();
  	void paintGL();
  	void resizeGL(int w,int h);

  private:
  	vector<Atom*>* atoms;
  	GLfloat xRot,yRot,zRot,scale;
};

  
  














