#include "mydialog.h"
#include "canvas.h"
#include <QtGui/qcombobox.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qmessagebox.h>


class Dialog1:public MyDialog
{
  Q_OBJECT
public:
  Dialog1(QWidget* parent,QString name,Canvas* c);

  void setupComboBox(QComboBox*);
public slots:
  void changeAtom(int);
  void applied();
//signals:
private:
  void updateXYZ(); 
  void updateAtom();
private:
  Canvas* canvas;
  ClusterView* view;
  QLineEdit* coord[3];
  Atom* currentAtom;
  QComboBox* atomSelect;
};
   

