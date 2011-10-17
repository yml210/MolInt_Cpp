/****************************************************************************
** Meta object code from reading C++ file 'canvas.h'
**
** Created: Sat Oct 15 23:42:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Canvas[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,    7,    7,    7, 0x0a,
      38,    7,    7,    7, 0x0a,
      48,    7,    7,    7, 0x0a,
      64,   58,    7,    7, 0x0a,
      87,   58,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Canvas[] = {
    "Canvas\0\0objectSelected(int)\0xRotate()\0"
    "yRotate()\0zRotate()\0angle\0"
    "setFixAngle(double[3])\0setEularAngle(double[3])\0"
};

const QMetaObject Canvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_Canvas,
      qt_meta_data_Canvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Canvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Canvas))
        return static_cast<void*>(const_cast< Canvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: objectSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: xRotate(); break;
        case 2: yRotate(); break;
        case 3: zRotate(); break;
        case 4: setFixAngle((*reinterpret_cast< double(*)[3]>(_a[1]))); break;
        case 5: setEularAngle((*reinterpret_cast< double(*)[3]>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Canvas::objectSelected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
