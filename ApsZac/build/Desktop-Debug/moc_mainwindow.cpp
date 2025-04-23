/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_MainWindow_t {
    uint offsetsAndSizes[40];
    char stringdata0[11];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[20];
    char stringdata6[21];
    char stringdata7[29];
    char stringdata8[6];
    char stringdata9[21];
    char stringdata10[29];
    char stringdata11[6];
    char stringdata12[11];
    char stringdata13[9];
    char stringdata14[22];
    char stringdata15[19];
    char stringdata16[22];
    char stringdata17[13];
    char stringdata18[12];
    char stringdata19[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 10),  // "on_request"
        QT_MOC_LITERAL(22, 0),  // ""
        QT_MOC_LITERAL(23, 12),  // "Request_Type"
        QT_MOC_LITERAL(36, 16),  // "device_connected"
        QT_MOC_LITERAL(53, 19),  // "device_disconnected"
        QT_MOC_LITERAL(73, 20),  // "device_state_changed"
        QT_MOC_LITERAL(94, 28),  // "QAbstractSocket::SocketState"
        QT_MOC_LITERAL(123, 5),  // "state"
        QT_MOC_LITERAL(129, 20),  // "device_error_occured"
        QT_MOC_LITERAL(150, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(179, 5),  // "error"
        QT_MOC_LITERAL(185, 10),  // "kaReceived"
        QT_MOC_LITERAL(196, 8),  // "kaNumber"
        QT_MOC_LITERAL(205, 21),  // "on_btnConnect_clicked"
        QT_MOC_LITERAL(227, 18),  // "on_btnSend_clicked"
        QT_MOC_LITERAL(246, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(268, 12),  // "onKaSelected"
        QT_MOC_LITERAL(281, 11),  // "QModelIndex"
        QT_MOC_LITERAL(293, 13)   // "onDataUpdated"
    },
    "MainWindow",
    "on_request",
    "",
    "Request_Type",
    "device_connected",
    "device_disconnected",
    "device_state_changed",
    "QAbstractSocket::SocketState",
    "state",
    "device_error_occured",
    "QAbstractSocket::SocketError",
    "error",
    "kaReceived",
    "kaNumber",
    "on_btnConnect_clicked",
    "on_btnSend_clicked",
    "on_pushButton_clicked",
    "onKaSelected",
    "QModelIndex",
    "onDataUpdated"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   83,    2, 0x08,    3 /* Private */,
       5,    0,   84,    2, 0x08,    4 /* Private */,
       6,    1,   85,    2, 0x08,    5 /* Private */,
       9,    1,   88,    2, 0x08,    7 /* Private */,
      12,    1,   91,    2, 0x08,    9 /* Private */,
      14,    0,   94,    2, 0x08,   11 /* Private */,
      15,    0,   95,    2, 0x08,   12 /* Private */,
      16,    0,   96,    2, 0x08,   13 /* Private */,
      17,    1,   97,    2, 0x08,   14 /* Private */,
      19,    1,  100,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSizes,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_request'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Request_Type, std::false_type>,
        // method 'device_connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'device_disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'device_state_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketState, std::false_type>,
        // method 'device_error_occured'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'kaReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnConnect_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSend_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onKaSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex, std::false_type>,
        // method 'onDataUpdated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_request((*reinterpret_cast< std::add_pointer_t<Request_Type>>(_a[1]))); break;
        case 1: _t->device_connected(); break;
        case 2: _t->device_disconnected(); break;
        case 3: _t->device_state_changed((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 4: _t->device_error_occured((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 5: _t->kaReceived((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_btnConnect_clicked(); break;
        case 7: _t->on_btnSend_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->onKaSelected((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 10: _t->onDataUpdated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(Request_Type );
            if (_t _q_method = &MainWindow::on_request; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::on_request(Request_Type _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
