/****************************************************************************
** Meta object code from reading C++ file 'PayersSelection.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CustomWidget/PayersSelection.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PayersSelection.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PayersSelection_t {
    QByteArrayData data[11];
    char stringdata[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PayersSelection_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PayersSelection_t qt_meta_stringdata_PayersSelection = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 9),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 13),
QT_MOC_LITERAL(4, 41, 18),
QT_MOC_LITERAL(5, 60, 12),
QT_MOC_LITERAL(6, 73, 9),
QT_MOC_LITERAL(7, 83, 6),
QT_MOC_LITERAL(8, 90, 10),
QT_MOC_LITERAL(9, 101, 12),
QT_MOC_LITERAL(10, 114, 11)
    },
    "PayersSelection\0nextPanel\0\0previousPanel\0"
    "ticketHasBeenFiled\0payerChanged\0"
    "payerName\0amount\0fileTicket\0updatePayers\0"
    "clearPayout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PayersSelection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   52,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Float,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PayersSelection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PayersSelection *_t = static_cast<PayersSelection *>(_o);
        switch (_id) {
        case 0: _t->nextPanel(); break;
        case 1: _t->previousPanel(); break;
        case 2: _t->ticketHasBeenFiled(); break;
        case 3: _t->payerChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->fileTicket(); break;
        case 5: _t->updatePayers(); break;
        case 6: _t->clearPayout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PayersSelection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PayersSelection::nextPanel)) {
                *result = 0;
            }
        }
        {
            typedef void (PayersSelection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PayersSelection::previousPanel)) {
                *result = 1;
            }
        }
        {
            typedef void (PayersSelection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PayersSelection::ticketHasBeenFiled)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PayersSelection::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PayersSelection.data,
      qt_meta_data_PayersSelection,  qt_static_metacall, 0, 0}
};


const QMetaObject *PayersSelection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PayersSelection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PayersSelection.stringdata))
        return static_cast<void*>(const_cast< PayersSelection*>(this));
    return QWidget::qt_metacast(_clname);
}

int PayersSelection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PayersSelection::nextPanel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PayersSelection::previousPanel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PayersSelection::ticketHasBeenFiled()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
