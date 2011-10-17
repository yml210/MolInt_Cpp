//mydialog.cpp

#include "dialog1.h"

	Dialog1::Dialog1(QWidget *parent=0, QString name=0,Canvas* c=0)
		:MyDialog(parent,name,2)
{
    canvas=c;
    view=canvas->getClusterView();
    currentAtom=view->getAtom(0);

    QLabel *label,*label1,*label2,*label3;
    label=new QLabel(this,"label");
    label->setText(QString("Atom:"));
    label->setFont(QFont("times",12,QFont::Bold));

    label1=new QLabel(this,"label");
    label1->setText(QString("X:"));

    label2=new QLabel(this,"label");
    label2->setText(QString("Y:"));

    label3=new QLabel(this,"label");
    label3->setText(QString("Z:"));

    for(int i=0;i<3;i++){
      coord[i]=new QLineEdit(this);
    }

    atomSelect=new QComboBox(FALSE,this);
    setupComboBox(atomSelect);
    updateXYZ();

    QGridLayout* grid1=new QGridLayout(0,1,6);
    grid1->setMargin(10);
    grid1->setColStretch(5,3);

    QGridLayout* grid2=new QGridLayout(0,3,5);
    grid2->setColStretch(4,3);
    grid2->setMargin(10);
    grid2->setSpacing(5);

    grid1->addWidget(label,0,1);
    grid1->addWidget(atomSelect,0,2);

    grid2->addWidget(label1,0,2);
    grid2->addWidget(coord[0],0,4);
    
    grid2->addWidget(label2,1,2);
    grid2->addWidget(coord[1],1,4);

    grid2->addWidget(label3,2,2);
    grid2->addWidget(coord[2],2,4);

    addLayout(grid1,0,0);
    addLayout(grid2,1,0);
/*
    QHBoxLayout* box=new QHBoxLayout;
    box->setMargin(100);
    QHBoxLayout* box1=new QHBoxLayout;
    box1->setMargin(25);
    box1->setSpacing(5);
    QHBoxLayout* box2=new QHBoxLayout;
    box2->setMargin(25);
    box2->setSpacing(5);
    QHBoxLayout* box3=new QHBoxLayout;
    box3->setMargin(25);
    box3->setSpacing(5);

    box->addWidget(label);
    box->addWidget(atomSelect);
    box1->addWidget(label1); 
    box1->addWidget(coord[0]); 
    box2->addWidget(label2); 
    box2->addWidget(coord[1]); 
    box3->addWidget(label3); 
    box3->addWidget(coord[2]); 
    addLayout(box,0,0);
    addLayout(box1,1,0);
    addLayout(box2,2,0);
    addLayout(box3,3,0);
*/
}

void Dialog1::applied()
{
  updateAtom();
  canvas->updateGL();
}        

void Dialog1::changeAtom(int index)
{
   currentAtom=view->getAtom(index);
   updateXYZ();
//   emit atomChanged();
}

void Dialog1::setupComboBox(QComboBox *box)
{
  int size=view->listSize();
  char sym[6];
  for(int i=0;i<size;i++){
    Atom* at=view->getAtom(i);
    at->getSymbol(sym); 
    box->insertItem(sym);
  }
  connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom(int))); 
}

void Dialog1::updateXYZ()
{
  double r[3];
  for(int i=0;i<3;i++){
    currentAtom->coordinate(r);
    coord[i]->setText(QString::number(r[i],'g',3));
  }
}

void Dialog1::updateAtom()
{
  double r[3];
  bool ok;
  QString tmp;
  for(int i=0;i<3;i++){
    tmp=coord[i]->text(); 
    r[i]=tmp.toDouble(&ok);
    if(!(&ok)){
      QMessageBox::information(this,"Ooops!",
	"Atom coordinates should be double type.");
    }
  }
  currentAtom->moveTo(r);
}

    
