#ifndef DIALOG2_H
#define DIALOG2_H

#include "mydialog.h"
#include "canvas.h"
#include <QtGui/qcombobox.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qmessagebox.h>

#include <vector>
using namespace std;

typedef vector<int> vecint;

class Dialog2:public MyDialog
{
  Q_OBJECT
public:
  Dialog2(QWidget* parent,QString name,Canvas* c);

  void setupComboBox(QComboBox*,int);
public slots:
  void changeAtom1(int);
  void changeAtom2(int);
  void applied();
//signals:
private:
  void updateLength(); 
  void updateAtom();
  void makeComboList(QComboBox *,int);
  int find(vecint&,int);
private:
  Canvas* canvas;
  ClusterView* view;
  QLineEdit* length;
  int index1;
  int index2;
  vecint *list1;
  vecint *list2;
  Atom* currentAtom1;
  Atom* currentAtom2;
  QComboBox* atomSelect1;
  QComboBox* atomSelect2;
};
   
#endif //DIALOG2_H
