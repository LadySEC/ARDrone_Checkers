/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Sources/Tcp_client/client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_client[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      27,    7,    7,    7, 0x05,
      60,   49,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      98,   90,    7,    7, 0x0a,
     123,    7,    7,    7, 0x0a,
     140,    7,    7,    7, 0x08,
     155,    7,    7,    7, 0x08,
     175,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_client[] = {
    "client\0\0socket_connected()\0"
    "socket_disconnected()\0mnemo,data\0"
    "data_to_IHM(QChar,QByteArray)\0message\0"
    "recoit_texte(QByteArray)\0connect_server()\0"
    "connexion_OK()\0connexion_stopped()\0"
    "lecture()\0"
};

void client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        client *_t = static_cast<client *>(_o);
        switch (_id) {
        case 0: _t->socket_connected(); break;
        case 1: _t->socket_disconnected(); break;
        case 2: _t->data_to_IHM((*reinterpret_cast< QChar(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 3: _t->recoit_texte((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->connect_server(); break;
        case 5: _t->connexion_OK(); break;
        case 6: _t->connexion_stopped(); break;
        case 7: _t->lecture(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData client::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_client,
      qt_meta_data_client, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_client))
        return static_cast<void*>(const_cast< client*>(this));
    return QObject::qt_metacast(_clname);
}

int client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void client::socket_connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void client::socket_disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void client::data_to_IHM(QChar _t1, QByteArray _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
