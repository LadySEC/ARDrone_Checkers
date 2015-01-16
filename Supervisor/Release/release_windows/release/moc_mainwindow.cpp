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
      52,   12,   11,   11, 0x05,
      87,   12,   11,   11, 0x05,
     128,   12,   11,   11, 0x05,
     168,   12,   11,   11, 0x05,
     200,   12,   11,   11, 0x05,
     230,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     260,   11,   11,   11, 0x08,
     282,   11,   11,   11, 0x08,
     304,   11,   11,   11, 0x08,
     326,   11,   11,   11, 0x08,
     350,   11,   11,   11, 0x08,
     365,   11,   11,   11, 0x08,
     377,   11,   11,   11, 0x08,
     402,   11,   11,   11, 0x08,
     431,   11,   11,   11, 0x08,
     459,  448,   11,   11, 0x08,
     500,   11,   11,   11, 0x08,
     520,   11,   11,   11, 0x08,
     546,  540,   11,   11, 0x08,
     574,   11,   11,   11, 0x08,
     591,   11,   11,   11, 0x08,
     609,   11,   11,   11, 0x08,
     627,   11,   11,   11, 0x08,
     645,   11,   11,   11, 0x08,
     663,   11,   11,   11, 0x08,
     681,   11,   11,   11, 0x08,
     699,   11,   11,   11, 0x08,
     717,   11,   11,   11, 0x08,
     735,   11,   11,   11, 0x08,
     753,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0new_value\0"
    "sig_change_battery_value(int)\0"
    "sig_change_altitude_value(QString)\0"
    "sig_change_vertical_speed_value(QString)\0"
    "sig_change_horizon_speed_value(QString)\0"
    "sig_change_theta_value(QString)\0"
    "sig_change_phi_value(QString)\0"
    "sig_change_psi_value(QString)\0"
    "slot_begin_scenario()\0slot_open_connexion()\0"
    "slot_mark_connexion()\0slot_unmark_connexion()\0"
    "slot_takeoff()\0slot_land()\0"
    "slot_emergency_landing()\0"
    "slot_reset_after_emergency()\0"
    "slot_next_move()\0mnemo,data\0"
    "slot_update_values_IHM(QChar,QByteArray)\0"
    "slot_send_takeoff()\0slot_send_landing()\0"
    "value\0slot_send_emergency(quint8)\0"
    "slot_send_exit()\0slot_send_G_A_1()\0"
    "slot_send_G_A_2()\0slot_send_G_A_3()\0"
    "slot_send_G_B_1()\0slot_send_G_B_2()\0"
    "slot_send_G_B_3()\0slot_send_G_C_1()\0"
    "slot_send_G_C_2()\0slot_send_G_C_3()\0"
    "slot_send_date()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->sig_change_battery_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_change_altitude_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_change_vertical_speed_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sig_change_horizon_speed_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sig_change_theta_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sig_change_phi_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sig_change_psi_value((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_begin_scenario(); break;
        case 8: _t->slot_open_connexion(); break;
        case 9: _t->slot_mark_connexion(); break;
        case 10: _t->slot_unmark_connexion(); break;
        case 11: _t->slot_takeoff(); break;
        case 12: _t->slot_land(); break;
        case 13: _t->slot_emergency_landing(); break;
        case 14: _t->slot_reset_after_emergency(); break;
        case 15: _t->slot_next_move(); break;
        case 16: _t->slot_update_values_IHM((*reinterpret_cast< QChar(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 17: _t->slot_send_takeoff(); break;
        case 18: _t->slot_send_landing(); break;
        case 19: _t->slot_send_emergency((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->slot_send_exit(); break;
        case 21: _t->slot_send_G_A_1(); break;
        case 22: _t->slot_send_G_A_2(); break;
        case 23: _t->slot_send_G_A_3(); break;
        case 24: _t->slot_send_G_B_1(); break;
        case 25: _t->slot_send_G_B_2(); break;
        case 26: _t->slot_send_G_B_3(); break;
        case 27: _t->slot_send_G_C_1(); break;
        case 28: _t->slot_send_G_C_2(); break;
        case 29: _t->slot_send_G_C_3(); break;
        case 30: _t->slot_send_date(); break;
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
void MainWindow::sig_change_battery_value(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sig_change_altitude_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::sig_change_vertical_speed_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::sig_change_horizon_speed_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::sig_change_theta_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::sig_change_phi_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::sig_change_psi_value(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
