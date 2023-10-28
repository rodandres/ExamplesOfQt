#ifndef SERIALMANAGEMNET_H
#define SERIALMANAGEMNET_H

#include "datamanagment.h"
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>


class serialmanagemnet : public QObject
{
    Q_OBJECT
public:
    serialmanagemnet();

    //Public methods

    void microcontroller_init(QString portDescription);
    void search_controller();
    void serial_close();
    void send_data(QString data);
    void search_port_description();
    void microcontroller_conecction(QString portDescription);
    void test();
    //Public variables
    QSerialPort *microController;
    QList<QString> microControllerNames;

public slots:
    void serial_read();

private:
    //Private methods

    //Private variables
    QString portName;

    quint16 vendorId;
    quint16 productId;

    bool microcontrollerAvailable;

    QByteArray serialData;
    QString serialBuffer;

};

#endif // SERIALMANAGEMNET_H
