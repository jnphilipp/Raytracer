/****************************************************************************
** Meta object code from reading C++ file 'gui.h'
**
** Created: Tue May 1 00:00:49 2012
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
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,
      16,    4,    4,    4, 0x08,
      29,    4,    4,    4, 0x08,
      41,    4,    4,    4, 0x08,
      53,    4,    4,    4, 0x08,
      64,    4,    4,    4, 0x08,
      72,    4,    4,    4, 0x08,
      84,    4,    4,    4, 0x08,
      93,    4,    4,    4, 0x08,
     108,    4,    4,    4, 0x08,
     117,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0\0loadFile()\0setCulling()\0saveScene()\0"
    "loadScene()\0addLight()\0scale()\0"
    "translate()\0rotate()\0deleteObject()\0"
    "render()\0quit()\0"
};

void GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GUI *_t = static_cast<GUI *>(_o);
        switch (_id) {
        case 0: _t->loadFile(); break;
        case 1: _t->setCulling(); break;
        case 2: _t->saveScene(); break;
        case 3: _t->loadScene(); break;
        case 4: _t->addLight(); break;
        case 5: _t->scale(); break;
        case 6: _t->translate(); break;
        case 7: _t->rotate(); break;
        case 8: _t->deleteObject(); break;
        case 9: _t->render(); break;
        case 10: _t->quit(); break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
