//mainWin.cpp

#include "mainWin.h"
#include "atom.h"
#include "clusterView.h"
#include "utility.h"

MainWin::MainWin(QWidget* parent,char* name)
        :QWidget(parent,name)
{
    canvas=0;
    dialog=0;
    dialog2=0;
    dialog3=0;

    mBar=new QMenuBar(this);
    QMenu* file=new QMenu(this);

    file->insertItem("&New",this,SLOT(newCluster()));
    file->insertItem("&Open",this,SLOT(openCluster()));
    file->insertSeparator();
    file->insertItem("&Quit",qApp,SLOT(quit()));

    mBar->insertItem("&File",file);

    

    canvas=new Canvas(this, "canvas");
    QVBoxLayout* grid=new QVBoxLayout(this);
    grid->addWidget(canvas);

    Cluster* cluster=new Cluster;


    Atoms ats=new VAtoms;

    double a,b,c,v[3];
    
    a=5.0;
    b=5.0;
    c=5.0;
    
    for(int i=-1;i<2;i+=2){
      for(int j=-1;j<2;j+=2){
        for(int k=-1;k<2;k+=2){
          v[0]=a*i;
          v[1]=b*j;
          v[2]=c*k;
          Atom* at=new Atom;
	  at->setMass(1.0);
          at->moveTo(v);
          ats->push_back(at);
        }
      }
    }
    Atom* att[3],*att1,*att2,*att3;
    for(int i=0;i<3;i++)
    {
      att[i]=(*ats)[i];
    }

    cout<<"distance:"<<endl;
    cout<<"1-2 "<< att[0]->distance(att[1])<<endl;
    cout<<"2-3 "<< att[1]->distance(att[2])<<endl;
    cout<<"3-1 "<< att[2]->distance(att[0])<<endl;

    cout<<"angle:"<<endl;
    cout<<"1-2-3 "<<att[0]->angle(att[1],att[2])<<endl;
    cout<<"2-3-1 "<<att[1]->angle(att[2],att[0])<<endl;
    cout<<"3-1-2 "<<att[2]->angle(att[0],att[1])<<endl;

    cout<<endl;
    cluster->addAtoms(ats);
    delete ats;
    ClusterView* view=new ClusterView(cluster);
    double xx[3];
    for(int i=0;i<cluster->listSize();i++){
    cluster->getAtomCoord(i,xx);
    util::vout(xx,3);
    }
    canvas->setObject(view,Canvas::CLUSTER);  
}
void MainWin::addEditMenu()
{
    QMenu* edit=new QMenu(this);
    edit->insertItem("&Coordinate",this,SLOT(moveAtom()));
    edit->insertItem("&Bond",this,SLOT(changeBondLength()));
    edit->insertItem("&Angle",this,SLOT(changeAngle1()));

    mBar->insertItem("&Edit",edit);
    
}
  
void MainWin::addViewMenu()
{
/*
    QMenu* viewMenu=new QMenu(this);
    edit->insertItem("&Rotate",this,SLOT(RotateView()));

    mBar->insertItem("&View",viewMenu);
*/    
}

void MainWin::newCluster()
{
   Atoms ats=new VAtoms;
    double a,b,c,v[3];

    a=5.0;
    b=5.0;
    c=5.0;
    char sym[6];
    int count=0;

    for(int i=-1;i<2;i+=2){
      for(int j=-1;j<2;j+=2){
        for(int k=-1;k<2;k+=2){
          v[0]=a*i;
          v[1]=b*j;
          v[2]=c*k;
          sprintf(sym,"%d",count);
          Atom* at=new Atom(sym);
          at->setMass(1.0);
          
	  count++;
          at->moveTo(v);
          ats->push_back(at);
        }
      }
    }

   Cluster* cluster=new Cluster;
   cluster->addAtoms(ats);
   delete ats; 
   if(canvas->isEmpty(Canvas::CLUSTER)){
     ClusterView* view=new ClusterView(cluster);
     canvas->setObject(view,Canvas::CLUSTER);
   }
   else{
     
     switch(canvas->currentViewType()){
     case Canvas::CLUSTER :
       ClusterView *tmp;
       tmp=canvas->getClusterView();
//       tmp->cache();
       tmp->setCluster(cluster);
       break;
/*   
     case Canvas::SYSTEM:
       SystemView *s=(SystemView*) canvas->getView(Canvas::SYSTEM);
       s->cache();
       s->setSystem(system);
       break;
*/
     default:
       break;
     }
    }
    canvas->setCurrentViewType(Canvas::CLUSTER);
    addEditMenu();
    addViewMenu();
}

void MainWin::openCluster()
{
  QString s(QFileDialog::getOpenFileName(QString::null,"*.dat",this));
  if(s.isEmpty())
    return;
  addEditMenu();
  addViewMenu();
}

void MainWin::changeBondLength()
{
  if(!dialog2){
    dialog2=new Dialog2(this,"Dialog2",canvas);
    dialog2->setGeometry(0,0,240,50);
  }
  dialog2->show();
//  delete dialog;
}

void MainWin::changeAngle1()
{
  if(!dialog3){
    dialog3=new Dialog3(this,"Dialog3",canvas);
    dialog3->setGeometry(0,0,240,50);
    connect(canvas,SIGNAL(objectSelected(int)),
                dialog3,SLOT(mouseSelect(int)));
  }
  
  dialog3->show();
}

void MainWin::moveAtom()
{
  if(!dialog){
    dialog=new Dialog1(this,"Dialog",canvas);
    dialog->setGeometry(0,0,240,50);
  }
  connect(canvas,SIGNAL(objectSelected(int)),dialog,SLOT(changeAtom(int)));
  dialog->show();
//  delete dialog;
}

int main(int argc,char** argv)
{
    
    QApplication a(argc,argv);

    MainWin w;
    w.setGeometry(100,100,500,500);
    a.setMainWidget(&w);

    w.show();
    return a.exec();
    
}

    

