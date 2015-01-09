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
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x05,
      48,   12,   11,   11, 0x05,
      79,   12,   11,   11, 0x05,
     116,   12,   11,   11, 0x05,
     152,   12,   11,   11, 0x05,
     180,   12,   11,   11, 0x05,
     206,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     232,   11,   11,   11, 0x0a,
     244,   11,   11,   11, 0x0a,
     261,   11,   11,   11, 0x0a,
     278,   11,   11,   11, 0x0a,
     295,   11,   11,   11, 0x0a,
     314,   11,   11,   11, 0x0a,
     330,   11,   11,   11, 0x0a,
     345,   11,   11,   11, 0x0a,
     365,   11,   11,   11, 0x0a,
     389,   11,   11,   11, 0x0a,
     404,   11,   11,   11, 0x0a,
     419,   11,   11,   11, 0x0a,
     437,  431,   11,   11, 0x0a,
     471,  460,   11,   11, 0x0a,
     507,   11,   11,   11, 0x0a,
     520,   11,   11,   11, 0x0a,
     533,   11,   11,   11, 0x0a,
     546,   11,   11,   11, 0x0a,
     559,   11,   11,   11, 0x0a,
     572,   11,   11,   11, 0x0a,
     585,   11,   11,   11, 0x0a,
     598,   11,   11,   11, 0x0a,
     611,   11,   11,   11, 0x0a,
     624,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0new_value\0change_battery_value(int)\0"
    "change_altitude_value(QString)\0"
    "change_vertical_speed_value(QString)\0"
    "change_horizon_speed_value(QString)\0"
    "change_theta_value(QString)\0"
    "change_phi_value(QString)\0"
    "change_psi_value(QString)\0next_move()\0"
    "begin_scenario()\0open_connexion()\0"
    "mark_connexion()\0unmark_connexion()\0"
    "start_mission()\0stop_mission()\0"
    "emergency_landing()\0reset_after_emergency()\0"
    "send_takeoff()\0send_landing()\0send_exit()\0"
    "value\0send_emergency(quint8)\0mnemo,data\0"
    "update_values_IHM(QChar,QByteArray)\0"
    "send_G_A_1()\0send_G_A_2()\0send_G_A_3()\0"
    "send_G_B_1()\0send_G_B_2()\0send_G_B_3()\0"
    "send_G_C_1()\0send_G_C_2()\0send_G_C_3()\0"
    "send_date()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->change_battery_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->change_altitude_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->change_vertical_speed_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->change_horizon_speed_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->change_theta_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->change_phi_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->change_psi_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->next_move(); break;
        case 8: _t->begin_scenario(); break;
        case 9: _t->open_connexion(); break;
        case 10: _t->mark_connexion(); break;
        case 11: _t->unmark_connexion(); break;
        case 12: _t->start_mission(); break;
        case 13: _t->stop_mission(); break;
        case 14: _t->emergency_landing(); break;
        case 15: _t->reset_after_emergency(); break;
        case 16: _t->send_takeoff(); break;
        case 17: _t->send_landing(); break;
        case 18: _t->send_exit(); break;
        case 19: _t->send_emergency((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->update_values_IHM((*reinterpret_cast< QChar(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 21: _t->send_G_A_1(); break;
        case 22: _t->send_G_A_2(); break;
        case 23: _t->send_G_A_3(); break;
        case 24: _t->send_G_B_1(); break;
        case 25: _t->send_G_B_2(); break;
        case 26: _t->send_G_B_3(); break;
        case 27: _t->send_G_C_1(); break;
        case 28: _t->send_G_C_2(); break;
        case 29: _t->send_G_C_3(); break;
        case 30: _t->send_date(); break;
        default: ;
        }
    }
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
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::change_battery_value(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::change_altitude_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::change_vertical_speed_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::change_horizon_speed_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::change_theta_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::change_phi_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::change_psi_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
