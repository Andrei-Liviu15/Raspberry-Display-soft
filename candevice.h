#ifndef CANDEVICE_H
#define CANDEVICE_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>
#include <QVariant>

class canDevice: QObject
{
    Q_OBJECT
public:
    canDevice(QObject* parent = nullptr);
    virtual ~canDevice() = default;

private:
    QCanBusDevice *m_canDevice=nullptr;
};

#endif // CANDEVICE_H
