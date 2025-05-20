/****************************************************************************
** Meta object code from reading C++ file 'messageprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../messageprocessor.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'messageprocessor.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_MessageProcessor_t {
    uint offsetsAndSizes[20];
    char stringdata0[17];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[18];
    char stringdata5[7];
    char stringdata6[12];
    char stringdata7[13];
    char stringdata8[8];
    char stringdata9[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MessageProcessor_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_MessageProcessor_t qt_meta_stringdata_MessageProcessor = {
    {
        QT_MOC_LITERAL(0, 16),  // "MessageProcessor"
        QT_MOC_LITERAL(17, 13),  // "message_ready"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 11),  // "QByteArray&"
        QT_MOC_LITERAL(44, 17),  // "device_data_ready"
        QT_MOC_LITERAL(62, 6),  // "Packet"
        QT_MOC_LITERAL(69, 11),  // "set_request"
        QT_MOC_LITERAL(81, 12),  // "Request_Type"
        QT_MOC_LITERAL(94, 7),  // "set_cel"
        QT_MOC_LITERAL(102, 4)   // "Cel&"
    },
    "MessageProcessor",
    "message_ready",
    "",
    "QByteArray&",
    "device_data_ready",
    "Packet",
    "set_request",
    "Request_Type",
    "set_cel",
    "Cel&"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_MessageProcessor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   43,    2, 0x0a,    4 /* Public */,
       6,    1,   46,    2, 0x0a,    6 /* Public */,
       8,    1,   49,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject MessageProcessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MessageProcessor.offsetsAndSizes,
    qt_meta_data_MessageProcessor,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_MessageProcessor_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MessageProcessor, std::true_type>,
        // method 'message_ready'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QByteArray &, std::false_type>,
        // method 'device_data_ready'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Packet, std::false_type>,
        // method 'set_request'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Request_Type, std::false_type>,
        // method 'set_cel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Cel &, std::false_type>
    >,
    nullptr
} };

void MessageProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessageProcessor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->message_ready((*reinterpret_cast< std::add_pointer_t<QByteArray&>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray&>>(_a[2]))); break;
        case 1: _t->device_data_ready((*reinterpret_cast< std::add_pointer_t<Packet>>(_a[1]))); break;
        case 2: _t->set_request((*reinterpret_cast< std::add_pointer_t<Request_Type>>(_a[1]))); break;
        case 3: _t->set_cel((*reinterpret_cast< std::add_pointer_t<Cel&>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MessageProcessor::*)(QByteArray & , QByteArray & );
            if (_t _q_method = &MessageProcessor::message_ready; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *MessageProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessageProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MessageProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MessageProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MessageProcessor::message_ready(QByteArray & _t1, QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
