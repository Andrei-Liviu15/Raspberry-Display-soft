#include "candevice.h"

canDevice::canDevice(QObject* parent) : QObject(parent){

    QString errorString;
    const QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices(
        QStringLiteral("socketcan"), &errorString);
    if (!errorString.isEmpty())
        qDebug() << errorString;
    int i=0;

    //while(devices.)
    qDebug() << devices[i].name();




    m_canDevice= QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), QStringLiteral("vcan0"), &errorString);
    if(!m_canDevice)
        qDebug()  << errorString;
    else
        m_canDevice->connectDevice();
    // QCanBusFrame a(QCanBusFrame::FrameId(123), QByteArray("1234"));
    // m_canDevice->writeFrame(a);


}
