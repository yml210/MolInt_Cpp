//dialog3.cpp

#include "dialog3.h"
#include "string.h"

Dialog3::Dialog3(QWidget *parent=0, QString name=0,Canvas* c=0)
		:MyDialog(parent,name,4)
{
    canvas=c;
    view=canvas->getClusterView();

    angle=new QLineEdit(this);

    for(int i=0;i<3;i++){
      index[i]=i;
    }

    char *rot[3]={"&Xrot","&Yrot","Zrot"};
    for(int i=0;i<3;i++){
      list[i]=new vector<int>;
      currentAtom[i]=view->getAtom(i);
      atomSelect[i]=new QComboBox(FALSE,this);
      atomSelect[i]->setFocusPolicy(Qt::StrongFocus);
      setupComboBox(atomSelect[i],i);
      rotate[i]=new QPushButton(this,rot[i]);
      rotate[i]->setFont(QFont("times",12,QFont::Bold));
    }
    
    connect(rotate[0],SIGNAL(clicked()),canvas, SLOT(xRotate()));
    connect(rotate[1],SIGNAL(clicked()),canvas, SLOT(yRotate()));
    connect(rotate[2],SIGNAL(clicked()),canvas, SLOT(zRotate()));
    drawBond=new QCheckBox(this,"DrawBond");
    drawBond->setText(QString("Draw Bonds"));
    setupDrawBond();
 
    QLabel *label[4];
    for(int i=0;i<4;i++){
      label[i]=new QLabel(this);
      label[i]->setFont(QFont("times",12,QFont::Bold));
    }
    label[0]->setText(QString("Atom1:"));
    label[1]->setText(QString("Atom2:"));
    label[2]->setText(QString("Atom3:"));
    label[3]->setText(QString("Angle123:"));




    QGridLayout* grid1=new QGridLayout(0,1,8);
    grid1->setMargin(10);

    QGridLayout* grid2=new QGridLayout(0,1,5);
    grid2->setMargin(10);
    grid2->setSpacing(5);
  
    QGridLayout* grid3=new QGridLayout(0,1,2);
    grid3->setMargin(10);

    for(int i=0;i<3;i++){
      int col=i*3;
      grid1->addWidget(label[i],0,col);
      grid1->addWidget(atomSelect[i],0,col+1);
    }

    grid2->addWidget(label[3],0,2);
    grid2->addWidget(angle,0,4);

    grid3->addWidget(drawBond,0,1);
 
    QHBoxLayout *hbox1=new QHBoxLayout;
    for(int i=0;i<3;i++){
      hbox1->addWidget(rotate[i]);
    }
      
    addLayout(grid1,0,0);
    addLayout(grid3,1,0);
    addLayout(grid2,2,0);
    addLayout(hbox1,3,0);
}

void Dialog3::applied()
{
  updateAtom();
  canvas->updateGL();
}        


void Dialog3::changeAtom1(int index)
{
  changeAtom(index, 0);
}

void Dialog3::changeAtom2(int index)
{
  changeAtom(index, 1);
}

void Dialog3::changeAtom3(int index)
{
  changeAtom(index, 2);
}

void Dialog3::changeAtom(int ind,int which)
{
   vecint l=*(list[which]);
   if(l[ind]!=index[which]){
     index[which]=l[ind];
     currentAtom[which]=view->getAtom(index[which]);
   
     for(int i=0;i<3;i++){
       if(i!=which){
         makeComboList(atomSelect[i],i);
         ind=find(*(list[i]),index[i]);
         atomSelect[i]->setCurrentItem(ind);
       }
     }
     updateAngle();
     updateBonds();
   }
}

int Dialog3::find(vecint &lst,int value)
{
   for(int i=0;i<lst.size();i++){
     if(lst[i]==value){
       return i;
     }
   }
}

void Dialog3::makeComboList(QComboBox *box,int which){
  int ind1,ind2;
  char sym[6];
  vecint *l;
  int size=view->listSize();
  switch(which){
    case 0:
      l=list[0];
      ind1=index[1];
      ind2=index[2];
      break;
    case 1:
      l=list[1];
      ind1=index[0];
      ind2=index[2];
      break;
    case 2:
      l=list[2];
      ind1=index[0];
      ind2=index[1];
      break;
  }

  box->clear();
  l->clear();
  int count=0;
  for(int i=0;i<size;i++){
    if((i!=ind1)&&(i!=ind2)){  
      Atom* at=view->getAtom(i);
      at->getSymbol(sym); 
      box->insertItem(sym,count);
      l->push_back(i);
      count++;
    }
  }
}

void Dialog3::setupDrawBond()
{
  bool on=view->bDrawBond();
  drawBond->setChecked(on);
  connect(drawBond,SIGNAL(toggled(bool)),this,SLOT(showBond(bool)));
  showBond(on);
}

void Dialog3::updateBonds()
{
  if(view->bDrawBond()){
    view->addBond(index[0],index[1]);
    view->addBond(index[1],index[2]);
    canvas->updateGL();
  }
}
  
void Dialog3::showBond(bool on)
{
  if(on){
    view->addBond(index[0],index[1]);
    view->addBond(index[1],index[2]);

  }else{
    view->removeBond(index[0],index[1]);
    view->removeBond(index[1],index[2]);
  }
  view->setDrawBond(on);
  canvas->updateGL();
}
  
void Dialog3::setupComboBox(QComboBox *box,int which)
{
  makeComboList(box,which);

  switch(which){
    case 0:
      connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom1(int))); 
      break;
    case 1:
      connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom2(int))); 
      break;
    case 2:
      connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom3(int))); 
      updateAngle();
      break;

   }
}

void Dialog3::updateAngle()
{
    double r=currentAtom[0]->angle(currentAtom[1],currentAtom[2]);
    angle->setText(QString::number(r,'g',6));
}

void Dialog3::updateAtom()
{
  double alpha;
  bool ok;
  QString tmp;
    tmp=angle->text(); 
    alpha=tmp.toDouble(&ok);
    if(!(&ok)){
      QMessageBox::information(this,"Ooops!",
	"angle should be double type.");
    }else{
      currentAtom[0]->changeAngle(currentAtom[1],currentAtom[2],alpha);
    }
}

void Dialog3::mouseSelect(int index)
{
  int which=findTheComboHasFocus();
  int ind=find(*(list[which]),index);
  atomSelect[which]->setCurrentItem(ind);
  changeAtom(ind,which);
}

int Dialog3::findTheComboHasFocus()
{
  for(int i=0;i<3;i++){
    if(atomSelect[i]->hasFocus())
      return i;
  } 
  return 0;
}

void Dialog3::mousePressEvent(QMouseEvent *e)
{
  cout<<findTheComboHasFocus()<<endl;
}

