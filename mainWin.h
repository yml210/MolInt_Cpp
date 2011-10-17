//mainWin.h
#define QT3_SUPPORT

#include <Qt/qapplication.h>
#include <QtGui/qpushbutton.h>
//#include <QtGui/qpopupmenu.h>
#include <QtGui/qmenu.h>
#include <QtGui/qlayout.h>
#include <QtGui/qfiledialog.h>
#include <QtGui/qmessagebox.h>
#include <QtGui/qwidget.h>
#include <QtGui/qmenubar.h>
#include "canvas.h"
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"

class MainWin: public QWidget
{
   Q_OBJECT
 public:
    MainWin(QWidget* parent=0,char* name=0);
 public slots:
    void newCluster();
    void openCluster();
    void moveAtom();
    void changeBondLength();
    void changeAngle1();
 private:
   void addEditMenu();
   void addViewMenu();

   Canvas* canvas; 
   Dialog1* dialog;
   Dialog2* dialog2;
   Dialog3* dialog3;
   QMenuBar* mBar;
};

