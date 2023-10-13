#ifndef SERIAL_MANAGEMENT_H
#define SERIAL_MANAGEMENT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class serial_management
{
public:
    serial_management();
    void test();


private:
    void search_arduino();

    QSerialPort *serial;
    QString portName;

    // Verificar tarjeta conectada de arduino
    quint16 vendorId;
    quint16 productId;

    bool arduinoAvailabe;

    void arduinoInit();

    QByteArray serialData;
    QString serialBuffer;
};

#endif // SERIAL_MANAGEMENT_H
