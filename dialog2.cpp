//dialog2.cpp

#include "dialog2.h"

	Dialog2::Dialog2(QWidget *parent=0, QString name=0,Canvas* c=0)
		:MyDialog(parent,name,2)
{
    canvas=c;
    view=canvas->getClusterView();
    index1=0;
    list1=new vector<int>;
    currentAtom1=view->getAtom(0);
    index2=1;
    list2=new vector<int>;
    currentAtom2=view->getAtom(1);

    QLabel *label1,*label2,*label3;
    label1=new QLabel(this,"label1");
    label1->setText(QString("Atom:"));
    label1->setFont(QFont("times",12,QFont::Bold));

    label2=new QLabel(this,"label2");
    label2->setText(QString("To Atom:"));
    label2->setFont(QFont("times",12,QFont::Bold));

    label3=new QLabel(this,"label");
    label3->setText(QString("Bond Length:"));
    label3->setFont(QFont("times",12,QFont::Bold));

    length=new QLineEdit(this);

    atomSelect1=new QComboBox(FALSE,this);
    setupComboBox(atomSelect1,1);
    atomSelect2=new QComboBox(FALSE,this);
    setupComboBox(atomSelect2,2);
    
    QGridLayout* grid1=new QGridLayout(0,1,7);
    grid1->setMargin(10);
//    grid1->setColStretch(5,3);

    QGridLayout* grid2=new QGridLayout(0,1,5);
//    grid2->setColStretch(4,3);
    grid2->setMargin(10);
    grid2->setSpacing(5);

    grid1->addWidget(label1,0,1);
    grid1->addWidget(atomSelect1,0,2);

    grid1->addWidget(label2,0,4);
    grid1->addWidget(atomSelect2,0,5);
    
    grid2->addWidget(label3,0,2);
    grid2->addWidget(length,0,4);

    addLayout(grid1,0,0);
    addLayout(grid2,1,0);
}

void Dialog2::applied()
{
  updateAtom();
  canvas->updateGL();
}        

void Dialog2::changeAtom1(int index)
{
   if((*list1)[index]!=index1){
   index1=(*list1)[index];
   currentAtom1=view->getAtom(index1);
//   makeComboList(atomSelect1,1);
//   atomSelect1->setCurrentItem(index);
   
   makeComboList(atomSelect2,2);
   index=find(*list2,index2);
   atomSelect2->setCurrentItem(index);
   updateLength();
   }
}

int Dialog2::find(vecint &lst,int value)
{
   for(int i=0;i<lst.size();i++){
     if(lst[i]==value){
       return i;
     }
   }
}

void Dialog2::changeAtom2(int index)
{
   if((*list2)[index]!=index2){
   index2=(*list2)[index];
   currentAtom2=view->getAtom(index2);

   makeComboList(atomSelect1,1);
   index=find(*list1,index1);
   atomSelect1->setCurrentItem(index);
   updateLength();
   }
//   emit atomChanged();
}

void Dialog2::makeComboList(QComboBox *box,int which){
  int index;
  char sym[6];
  vecint *list;
  int size=view->listSize();
  switch(which){
    case 1:
      list=list1;
      index=index2;
      break;
    case 2:
      list=list2;
      index=index1;
      break;
  }

  box->clear();
  list->clear();
  int count=0;
  for(int i=0;i<size;i++){
    if(i!=index){  
      Atom* at=view->getAtom(i);
      at->getSymbol(sym); 
      box->insertItem(sym,count);
      list->push_back(i);
      count++;
    }
  }
}

void Dialog2::setupComboBox(QComboBox *box,int which)
{
  makeComboList(box,which);

  switch(which){
    case 1:
      connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom1(int))); 
      break;
    case 2:
      updateLength();
      connect(box,SIGNAL(activated(int)),this,SLOT(changeAtom2(int))); 
      break;
   }
}

void Dialog2::updateLength()
{
    double r=currentAtom1->distance(currentAtom2);
    length->setText(QString::number(r,'g',6));
}

void Dialog2::updateAtom()
{
  double r,x[3];
  bool ok;
  QString tmp;
    tmp=length->text(); 
    r=tmp.toDouble(&ok);
    if(!(&ok)){
      QMessageBox::information(this,"Ooops!",
	"Bond length should be double type.");
    }else{
      currentAtom1->changeDistance(currentAtom2,r);
    }
}

    
