/****************************************************************************
** Meta object code from reading C++ file 'chatwidget.h'
**
** Created: Sat Nov 8 21:35:44 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chatwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChatWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   45,   11,   11, 0x0a,
     110,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChatWidget[] = {
    "ChatWidget\0\0message\0outgoingMessage(QString)\0"
    "senderId,senderName,message\0"
    "incomingMessage(int,QString,QString)\0"
    "sendMessage()\0"
};

const QMetaObject ChatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChatWidget,
      qt_meta_data_ChatWidget, 0 }
};

const QMetaObject *ChatWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ChatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWidget))
        return static_cast<void*>(const_cast< ChatWidget*>(this));
    if (!strcmp(_clname, "Ui::ChatWidget"))
        return static_cast< Ui::ChatWidget*>(const_cast< ChatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: outgoingMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: incomingMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: sendMessage(); break;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ChatWidget::outgoingMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
