/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Sources/Tcp_client/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 14),
QT_MOC_LITERAL(4, 42, 16),
QT_MOC_LITERAL(5, 59, 13),
QT_MOC_LITERAL(6, 73, 12),
QT_MOC_LITERAL(7, 86, 13),
QT_MOC_LITERAL(8, 100, 12),
QT_MOC_LITERAL(9, 113, 12),
QT_MOC_LITERAL(10, 126, 9),
QT_MOC_LITERAL(11, 136, 12),
QT_MOC_LITERAL(12, 149, 12),
QT_MOC_LITERAL(13, 162, 12),
QT_MOC_LITERAL(14, 175, 12),
QT_MOC_LITERAL(15, 188, 12),
QT_MOC_LITERAL(16, 201, 12),
QT_MOC_LITERAL(17, 214, 12),
QT_MOC_LITERAL(18, 227, 12),
QT_MOC_LITERAL(19, 240, 12)
    },
    "MainWindow\0open_connexion\0\0mark_connexion\0"
    "unmark_connexion\0start_mission\0"
    "stop_mission\0pause_mission\0send_takeoff\0"
    "send_landing\0send_exit\0send_M_Bl_Re\0"
    "send_M_Bl_Tr\0send_M_Bl_Ci\0send_M_Ro_Re\0"
    "send_M_Ro_Tr\0send_M_Ro_Ci\0send_M_Gr_Re\0"
    "send_M_Gr_Tr\0send_M_Gr_Ci\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x0a,
       3,    0,  105,    2, 0x0a,
       4,    0,  106,    2, 0x0a,
       5,    0,  107,    2, 0x0a,
       6,    0,  108,    2, 0x0a,
       7,    0,  109,    2, 0x0a,
       8,    0,  110,    2, 0x0a,
       9,    0,  111,    2, 0x0a,
      10,    0,  112,    2, 0x0a,
      11,    0,  113,    2, 0x0a,
      12,    0,  114,    2, 0x0a,
      13,    0,  115,    2, 0x0a,
      14,    0,  116,    2, 0x0a,
      15,    0,  117,    2, 0x0a,
      16,    0,  118,    2, 0x0a,
      17,    0,  119,    2, 0x0a,
      18,    0,  120,    2, 0x0a,
      19,    0,  121,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
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

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
