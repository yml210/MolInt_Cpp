#ifndef MYDIALOG_H
#define MYDIALOG_H

#define QT3_SUPPORT

#include <QtGui/qdialog.h>
#include <QtGui/qlabel.h>
#include <QtGui/qlayout.h>
#include <QtGui/qpushbutton.h> 
#include <QtGui/qlayout.h>

class MyDialog:public QDialog
{
  Q_OBJECT
public:
  MyDialog(QWidget*,QString,int r);

  void ok();
  void addWidget(QWidget *,int row,int col);

  void addLayout(QLayout *,int row,int col);
public slots:
  virtual void applied();

private:
  QGridLayout *grid; 

};
#endif  //MYDIALOG_H   

