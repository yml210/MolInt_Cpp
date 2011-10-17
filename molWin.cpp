#include <qapplication.h>
#include <qpushbutton.h>
#include <qlayout.h>

#include "molWin.h"

MolWin::MolWin(QWidget* parent,char* name)
        :QWidget(parent,name)
{
    QPushButton* quit=new QPushButton("&Quit",this,"quit");
    quit->setFont(QFont("Times",18,QFont::Bold));
    connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));

    QPushButton* incrXRot=new QPushButton("XRot",this,"xrot");
    incrXRot->setFont(QFont("Times",18,QFont::Bold));

    QPushButton* incrYRot=new QPushButton("YRot",this,"xrot");
    incrYRot->setFont(QFont("Times",18,QFont::Bold));

    QPushButton* incrZRot=new QPushButton("ZRot",this,"zrot");
    incrZRot->setFont(QFont("Times",18,QFont::Bold));

    canvas=new MolCanvas(this, "canvas");
    connect(incrXRot,SIGNAL(clicked()),canvas,SLOT(increaseXRot()));
    connect(incrYRot,SIGNAL(clicked()),canvas,SLOT(increaseYRot()));
    connect(incrZRot,SIGNAL(clicked()),canvas,SLOT(increaseZRot()));

    Coordinate v[8];
    getCoordinate(v,8);
    for(int i=1;i<8;i++)
      {	
	Atom* a= new Atom("H",1,1823.0);    
	a->setCoordinate(v[i].x,v[i].y,v[i].z);
	canvas->addAtom(a);
      }

    canvas->setScale(0.2);

    QGridLayout* grid=new QGridLayout(this,2,2,10);

    grid->addWidget(quit,0,0);
    grid->addWidget(canvas,1,1);
    grid->setColStretch(1,10);

    QHBoxLayout* box=new QHBoxLayout;
    box->addWidget(incrXRot);
    box->addWidget(incrYRot);
    box->addWidget(incrZRot);

    grid->addLayout(box,0,1);
    
}

void MolWin::getCoordinate(Coordinate* v,int natom)
{
    double a,b,c;
    a=1.0;
    b=1.0;
    c=1.0;
    int index=0;
    for(int i=-1;i<2;i+=2){
      for(int j=-1;j<2;j+=2){
	for(int k=-1;k<2;k+=2){
	  v[index].x=a*i;
	  v[index].y=b*j;
	  v[index].z=c*k;
	  index++;
	}
      }
    }
}
      


int main(int argc,char** argv)
{
    
    QApplication a(argc,argv);

    MolWin w;
    w.setGeometry(100,100,500,500);
    a.setMainWidget(&w);

    w.show();
    return a.exec();
    
}


    

    

