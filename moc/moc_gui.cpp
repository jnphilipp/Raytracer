/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Sat Jun 16 16:20:00 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,
      16,    4,    4,    4, 0x08,
      29,    4,    4,    4, 0x08,
      42,    4,    4,    4, 0x08,
      54,    4,    4,    4, 0x08,
      66,    4,    4,    4, 0x08,
      77,    4,    4,    4, 0x08,
      85,    4,    4,    4, 0x08,
      97,    4,    4,    4, 0x08,
     106,    4,    4,    4, 0x08,
     121,    4,    4,    4, 0x08,
     130,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0\0loadFile()\0setShaders()\0setCulling()\0"
    "saveScene()\0loadScene()\0addLight()\0"
    "scale()\0translate()\0rotate()\0"
    "deleteObject()\0render()\0quit()\0"
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI *_t = static_cast<GUI *>(_o);
        switch (_id) {
        case 0: _t->loadFile(); break;
        case 1: _t->setShaders(); break;
        case 2: _t->setCulling(); break;
        case 3: _t->saveScene(); break;
        case 4: _t->loadScene(); break;
        case 5: _t->addLight(); break;
        case 6: _t->scale(); break;
        case 7: _t->translate(); break;
        case 8: _t->rotate(); break;
        case 9: _t->deleteObject(); break;
        case 10: _t->render(); break;
        case 11: _t->quit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI,
      qt_meta_data_GUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI))
        return static_cast<void*>(const_cast< GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
