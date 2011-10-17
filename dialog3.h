#ifndef DIALOG3_H
#define DIALOG3_H

#define QT3_SUPPORT 

#include "mydialog.h"
#include "canvas.h"
#include <QtGui/qcombobox.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qcheckbox.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qmessagebox.h>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> vecint;

class Dialog3:public MyDialog
{
  Q_OBJECT
public:
  Dialog3(QWidget* parent,QString name,Canvas* c);

  void setupComboBox(QComboBox*,int);
  void setupDrawBond();

public slots:
  void changeAtom1(int);
  void changeAtom2(int);
  void changeAtom3(int);
  void mouseSelect(int);
  void showBond(bool);
  void applied();
protected:
  void mousePressEvent(QMouseEvent *e);
//signals:
private:
  void updateAngle(); 
  void updateBonds();
  void updateAtom();
  void makeComboList(QComboBox *,int);
  void changeAtom(int index,int which);
  int find(vecint&,int);
  int findTheComboHasFocus();
private:
  Canvas* canvas;
  ClusterView* view;
  QLineEdit* angle;
  int index[3];
  vecint *list[3];
  Atom* currentAtom[3];
  QComboBox* atomSelect[3];
  QPushButton *rotate[3];
  QCheckBox* drawBond;
};
   
#endif //DIALOG3_H
