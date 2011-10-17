/****************************************************************************
** Meta object code from reading C++ file 'dialog3.h'
**
** Created: Sat Oct 15 23:41:00 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog3.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog3[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      26,    8,    8,    8, 0x0a,
      43,    8,    8,    8, 0x0a,
      60,    8,    8,    8, 0x0a,
      77,    8,    8,    8, 0x0a,
      92,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Dialog3[] = {
    "Dialog3\0\0changeAtom1(int)\0changeAtom2(int)\0"
    "changeAtom3(int)\0mouseSelect(int)\0"
    "showBond(bool)\0applied()\0"
};

const QMetaObject Dialog3::staticMetaObject = {
    { &MyDialog::staticMetaObject, qt_meta_stringdata_Dialog3,
      qt_meta_data_Dialog3, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Dialog3::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Dialog3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Dialog3::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog3))
        return static_cast<void*>(const_cast< Dialog3*>(this));
    return MyDialog::qt_metacast(_clname);
}

int Dialog3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MyDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeAtom1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: changeAtom2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: changeAtom3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: mouseSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: showBond((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: applied(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
