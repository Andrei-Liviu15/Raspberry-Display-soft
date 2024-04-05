#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectDevice();
    connect(m_canDevice, &QCanBusDevice::framesReceived,
            this, &MainWindow::processReceivedFrames);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processReceivedFrames()
{   while(m_canDevice->framesAvailable())
    {
        const QCanBusFrame frame = m_canDevice->readFrame();
        QString data;
        data = QString::fromLatin1(frame.payload().toHex(' ').toUpper());
        int id=frame.frameId();
        id=id+1520;
        if(id==1520)
            {
                QStringList stringList = data.split(" ");
                //Engine RPM code
                // Extract the 6th element from the vector
                QString sixthElement;
                if (stringList.size() >= 6)
                {
                    sixthElement = stringList[5];
                    // Convert the 6th element to integer
                    bool ok;
                    int sixthElementInt = sixthElement.toInt(&ok, 16); // Assuming hexadecimal representation
                    if (ok) {
                        // Convert the integer back to QString
                        QString sixthElementString = QString::number(sixthElementInt);
                        ui->label_RPM->setText(sixthElementString);
                    }
                }
            }

        if(id==1522)
        {
            QStringList stringList = data.split(" ");
            //Mainfold air pressure/air temperature/coolant temmperature code
            QString secondElement;
            QString forthElement;
            QString sixthElement;
            if (stringList.size() >= 6)
            {
                secondElement =stringList[1];
                forthElement =stringList[3];;
                sixthElement = stringList[5];
                bool ok;
                int secondElementInt = secondElement.toInt(&ok, 16);
                int forthElementInt = forthElement.toInt(&ok, 16);
                int sixthElementInt = sixthElement.toInt(&ok, 16); // Assuming hexadecimal representation
                double forthElementdouble = forthElementInt;
                forthElementdouble = (forthElementInt - 32) * 5.0 / 9.0;
                double sixthElementdouble = sixthElementInt;
                sixthElementdouble = (sixthElementInt - 32) * 5.0 / 9.0;
                if (ok) {
                    // Convert the integer back to QString
                    QString secondElementString = QString::number(secondElementInt);
                    QString forthElementString = QString::number(forthElementdouble,'f',2);
                    QString sixthElementString = QString::number(sixthElementdouble,'f',2);
                    ui->label_AirPressure->setText(secondElementString);
                    ui->label_AirTemperature->setText(forthElementString);
                    ui->label_CoolantTemperature->setText(sixthElementString);
                }
            }
        }

        if(id==1523)
        {
            QStringList stringList = data.split(" ");
            // TPS/Battery voltage code
            QString firstElement;
            QString secondElement;
            if (stringList.size() >= 6)
            {
                firstElement =stringList[0];
                secondElement =stringList[1];
                bool ok;
                int firstElementInt = firstElement.toInt(&ok, 16);
                int secondElementInt = secondElement.toInt(&ok, 16);
                if (ok) {
                    // Convert the integer back to QString
                    QString firstElementString = QString::number(firstElementInt);
                    QString secondElementString = QString::number(secondElementInt);
                    ui->label_TPS->setText(firstElementString);
                    ui->label_Battery->setText(secondElementString);
                }
            }
        }

        if(id==1635)
        {
            QStringList stringList = data.split(" ");
            //BSPD code
            QString firstElement;
            QString sixthElement;
            if (stringList.size() >= 6)
            {
                firstElement = stringList[0];
                sixthElement = stringList[5];
                bool ok;
                int firstElementInt = firstElement.toInt(&ok, 16);
                int sixthElementInt = sixthElement.toInt(&ok, 16);
                if (ok)
                {
                    QString firstElementString = QString::number(firstElementInt);
                    QString sixthElementString = QString::number(sixthElementInt);
                    ui->label_BSPD->setText(firstElementString);
                    ui->label->setText(sixthElementString);
                    ui->label->setAlignment(Qt::AlignCenter);
                }
            }
        }

        if(id==1636)
        {
            QStringList stringList = data.split(" ");
            //GPS Speed code
            QString sixthElement;
            if (stringList.size() >= 6)
            {
                sixthElement = stringList[5];
                bool ok;
                int sixthElementInt = sixthElement.toInt(&ok, 16);
                if (ok)
                {
                    QString sixthElementString = QString::number(sixthElementInt);
                    ui->label_GPS->setText(sixthElementString);
                }
            }
        }

      //  QString is=QString::number(id);
        // if(id==115)
        // {
        qDebug() << id;
      //  ui->label->setText(is);

    }

}
void MainWindow::connectDevice()
{
    QString errorString;
    const QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices(
        QStringLiteral("socketcan"), &errorString);
    if (!errorString.isEmpty())
        qDebug() << errorString;
    int i=0;

    //while(devices.)
    qDebug() << devices[i].name();
    int val=500000;
    m_canDevice= QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), QStringLiteral("vcan0"), &errorString);
    if(!m_canDevice)
        qDebug()  << errorString;
    else
        m_canDevice->connectDevice();
    // QCanBusFrame a(QCanBusFrame::FrameId(123), QByteArray("1234"));
    // m_canDevice->writeFrame(a);
}
void MainWindow::on_button1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_button2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

