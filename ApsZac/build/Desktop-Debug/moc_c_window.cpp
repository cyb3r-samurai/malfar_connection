/****************************************************************************
** Meta object code from reading C++ file 'c_window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../c_window.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'c_window.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_C_window_t {
    uint offsetsAndSizes[16];
    char stringdata0[9];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[4];
    char stringdata5[22];
    char stringdata6[24];
    char stringdata7[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_C_window_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_C_window_t qt_meta_stringdata_C_window = {
    {
        QT_MOC_LITERAL(0, 8),  // "C_window"
        QT_MOC_LITERAL(9, 11),  // "cel_created"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 4),  // "Cel&"
        QT_MOC_LITERAL(27, 3),  // "cel"
        QT_MOC_LITERAL(31, 21),  // "on_pushButton_clicked"
        QT_MOC_LITERAL(53, 23),  // "on_pushButton_2_clicked"
        QT_MOC_LITERAL(77, 23)   // "on_pushButton_3_clicked"
    },
    "C_window",
    "cel_created",
    "",
    "Cel&",
    "cel",
    "on_pushButton_clicked",
    "on_pushButton_2_clicked",
    "on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_C_window[] = {

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
       1,    1,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   41,    2, 0x08,    3 /* Private */,
       6,    0,   42,    2, 0x08,    4 /* Private */,
       7,    0,   43,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject C_window::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_C_window.offsetsAndSizes,
    qt_meta_data_C_window,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_C_window_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<C_window, std::true_type>,
        // method 'cel_created'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Cel &, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void C_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<C_window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cel_created((*reinterpret_cast< std::add_pointer_t<Cel&>>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (C_window::*)(Cel & );
            if (_t _q_method = &C_window::cel_created; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *C_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *C_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_C_window.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int C_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void C_window::cel_created(Cel & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
