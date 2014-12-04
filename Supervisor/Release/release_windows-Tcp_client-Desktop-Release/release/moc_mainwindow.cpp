/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Sources/Tcp_client/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      29,   11,   11,   11, 0x0a,
      46,   11,   11,   11, 0x0a,
      65,   11,   11,   11, 0x0a,
      81,   11,   11,   11, 0x0a,
      96,   11,   11,   11, 0x0a,
     112,   11,   11,   11, 0x0a,
     127,   11,   11,   11, 0x0a,
     142,   11,   11,   11, 0x0a,
     154,   11,   11,   11, 0x0a,
     169,   11,   11,   11, 0x0a,
     184,   11,   11,   11, 0x0a,
     199,   11,   11,   11, 0x0a,
     214,   11,   11,   11, 0x0a,
     229,   11,   11,   11, 0x0a,
     244,   11,   11,   11, 0x0a,
     259,   11,   11,   11, 0x0a,
     274,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0open_connexion()\0"
    "mark_connexion()\0unmark_connexion()\0"
    "start_mission()\0stop_mission()\0"
    "pause_mission()\0send_takeoff()\0"
    "send_landing()\0send_exit()\0send_M_Bl_Re()\0"
    "send_M_Bl_Tr()\0send_M_Bl_Ci()\0"
    "send_M_Ro_Re()\0send_M_Ro_Tr()\0"
    "send_M_Ro_Ci()\0send_M_Gr_Re()\0"
    "send_M_Gr_Tr()\0send_M_Gr_Ci()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->open_connexion(); break;
        case 1: _t->mark_connexion(); break;
        case 2: _t->unmark_connexion(); break;
        case 3: _t->start_mission(); break;
        case 4: _t->stop_mission(); break;
        case 5: _t->pause_mission(); break;
        case 6: _t->send_takeoff(); break;
        case 7: _t->send_landing(); break;
        case 8: _t->send_exit(); break;
        case 9: _t->send_M_Bl_Re(); break;
        case 10: _t->send_M_Bl_Tr(); break;
        case 11: _t->send_M_Bl_Ci(); break;
        case 12: _t->send_M_Ro_Re(); break;
        case 13: _t->send_M_Ro_Tr(); break;
        case 14: _t->send_M_Ro_Ci(); break;
        case 15: _t->send_M_Gr_Re(); break;
        case 16: _t->send_M_Gr_Tr(); break;
        case 17: _t->send_M_Gr_Ci(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
