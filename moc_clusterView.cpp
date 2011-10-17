/****************************************************************************
** Meta object code from reading C++ file 'clusterView.h'
**
** Created: Sun Oct 16 11:19:32 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clusterView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clusterView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClusterView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      34,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   59,   12,   12, 0x0a,
      83,   77,   12,   12, 0x0a,
     103,  101,   12,   12, 0x0a,
     126,  124,   12,   12, 0x0a,
     150,   12,  143,   12, 0x0a,
     166,   12,  161,   12, 0x0a,
     178,   12,   12,   12, 0x0a,
     196,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClusterView[] = {
    "ClusterView\0\0scaleChanged(double)\0"
    "clusterChanged(Cluster*)\0r\0move(double[3])\0"
    "angle\0rotate(double[3])\0c\0"
    "setCluster(Cluster*)\0s\0setScale(double)\0"
    "double\0getScale()\0bool\0bDrawBond()\0"
    "setDrawBond(bool)\0close()\0"
};

const QMetaObject ClusterView::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClusterView,
      qt_meta_data_ClusterView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClusterView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClusterView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClusterView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClusterView))
        return static_cast<void*>(const_cast< ClusterView*>(this));
    return QObject::qt_metacast(_clname);
}

int ClusterView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scaleChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: clusterChanged((*reinterpret_cast< Cluster*(*)>(_a[1]))); break;
        case 2: move((*reinterpret_cast< double(*)[3]>(_a[1]))); break;
        case 3: rotate((*reinterpret_cast< double(*)[3]>(_a[1]))); break;
        case 4: setCluster((*reinterpret_cast< Cluster*(*)>(_a[1]))); break;
        case 5: setScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: { double _r = getScale();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: { bool _r = bDrawBond();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: setDrawBond((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: close(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ClusterView::scaleChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClusterView::clusterChanged(Cluster * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
