//mydialog.cpp
#include "mydialog.h"


MyDialog::MyDialog(QWidget *parent=0, QString name=0,int r=1)
		:QDialog(parent,name,FALSE)
{

    QPushButton *ok, *cancel,*apply;

    ok=new QPushButton("  OK  ",this);
    connect(ok,SIGNAL(clicked()),SLOT(accept()));
    
    cancel=new QPushButton("Cancel",this);
    connect(cancel,SIGNAL(clicked()),SLOT(reject()));

    apply=new QPushButton("Apply ",this);
    connect(apply,SIGNAL(clicked()),SLOT(applied()));

    grid= new QGridLayout(this,r+1,1);
    
    QHBoxLayout *buttons=new QHBoxLayout;
    buttons->addWidget(ok);
    buttons->addWidget(apply);
    buttons->addWidget(cancel);
    buttons->setMargin(5);
    buttons->setSpacing(5);

    grid->addLayout(buttons,r,0); 

}

void MyDialog::ok()
{
  applied();
  accept();
}

void MyDialog::applied()
{
}        

void MyDialog::addWidget(QWidget *w,int row,int col)
{
  grid->addWidget(w,row,col);
}

void MyDialog::addLayout(QLayout *layout,int row,int col)
{
  grid->addLayout(layout,row,col);
}
