#ifndef SERIALMANAGEMNET_H
#define SERIALMANAGEMNET_H

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

    void arduinoInit();
    void search_arduino();
    void serial_close();

    void test();
    //Public variables
public slots:
    void serial_read();

private:
    //Private methods

    //Private variables
    QSerialPort *serial;
    QString portName;

    quint16 vendorId;
    quint16 productId;

    bool arduinoAvailabe;

    QByteArray serialData;
    QString serialBuffer;

};

#endif // SERIALMANAGEMNET_H
