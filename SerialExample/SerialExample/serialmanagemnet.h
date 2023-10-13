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

    void arduino_init();
    void search_arduino();
    void serial_close();
    void send_data(QString data);
    void test();
    //Public variables
    QSerialPort *microController;

public slots:
    void serial_read();

private:
    //Private methods

    //Private variables
    QString portName;

    quint16 vendorId;
    quint16 productId;

    bool arduinoAvailabe;

    QByteArray serialData;
    QString serialBuffer;

};

#endif // SERIALMANAGEMNET_H
