/****************************************************************************
** MolCanvas meta object code from reading C++ file 'molCanvas.h'
**
** Created: Fri May 12 15:29:49 2000
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.1.0   edited 2000-03-24 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#define Q_MOC_MolCanvas
#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 7
#elif Q_MOC_OUTPUT_REVISION != 7
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "molCanvas.h"
#include <qmetaobject.h>
#include <qapplication.h>

#if defined(Q_SPARCWORKS_FUNCP_BUG)
#define Q_AMPERSAND
#else
#define Q_AMPERSAND &
#endif


const char *MolCanvas::className() const
{
    return "MolCanvas";
}

QMetaObject *MolCanvas::metaObj = 0;

void MolCanvas::initMetaObject()
{
    if ( metaObj )
	return;
    if ( strcmp(QGLWidget::className(), "QGLWidget") != 0 )
	badSuperclassWarning("MolCanvas","QGLWidget");
    (void) staticMetaObject();
}

QString MolCanvas::tr(const char* s)
{
    return ((QNonBaseApplication*)qApp)->translate("MolCanvas",s);
}

QMetaObject* MolCanvas::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QGLWidget::staticMetaObject();
    typedef void(MolCanvas::*m1_t0)();
    typedef void(MolCanvas::*m1_t1)(Atom*);
    typedef void(MolCanvas::*m1_t2)(Atom*);
    typedef void(MolCanvas::*m1_t3)(double,double,double);
    typedef void(MolCanvas::*m1_t4)(double);
    typedef void(MolCanvas::*m1_t5)();
    typedef void(MolCanvas::*m1_t6)();
    typedef void(MolCanvas::*m1_t7)();
    m1_t0 v1_0 = Q_AMPERSAND MolCanvas::addAtom;
    m1_t1 v1_1 = Q_AMPERSAND MolCanvas::addAtom;
    m1_t2 v1_2 = Q_AMPERSAND MolCanvas::removeAtom;
    m1_t3 v1_3 = Q_AMPERSAND MolCanvas::setRotAngle;
    m1_t4 v1_4 = Q_AMPERSAND MolCanvas::setScale;
    m1_t5 v1_5 = Q_AMPERSAND MolCanvas::increaseXRot;
    m1_t6 v1_6 = Q_AMPERSAND MolCanvas::increaseYRot;
    m1_t7 v1_7 = Q_AMPERSAND MolCanvas::increaseZRot;
    QMetaData *slot_tbl = QMetaObject::new_metadata(8);
    slot_tbl[0].name = "addAtom()";
    slot_tbl[1].name = "addAtom(Atom*)";
    slot_tbl[2].name = "removeAtom(Atom*)";
    slot_tbl[3].name = "setRotAngle(double,double,double)";
    slot_tbl[4].name = "setScale(double)";
    slot_tbl[5].name = "increaseXRot()";
    slot_tbl[6].name = "increaseYRot()";
    slot_tbl[7].name = "increaseZRot()";
    slot_tbl[0].ptr = *((QMember*)&v1_0);
    slot_tbl[1].ptr = *((QMember*)&v1_1);
    slot_tbl[2].ptr = *((QMember*)&v1_2);
    slot_tbl[3].ptr = *((QMember*)&v1_3);
    slot_tbl[4].ptr = *((QMember*)&v1_4);
    slot_tbl[5].ptr = *((QMember*)&v1_5);
    slot_tbl[6].ptr = *((QMember*)&v1_6);
    slot_tbl[7].ptr = *((QMember*)&v1_7);
    metaObj = QMetaObject::new_metaobject(
	"MolCanvas", "QGLWidget",
	slot_tbl, 8,
	0, 0,
	0, 0,
	0, 0,
	0, 0 );
    return metaObj;
}
