#include "serial_management.h"

serial_management::serial_management()
{

}

void serial_management::search_arduino()
{
    //Buscar informacion del arduino en cada puerto serial
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        qDebug()<<"Puerto: " << serialInfo.portName(); //PortDescription en python
        portName = serialInfo.portName();
        qDebug() << "Vendor ID: " << serialInfo.vendorIdentifier();
        vendorId = serialInfo.vendorIdentifier();
        qDebug() << "Product ID: " << serialInfo.productIdentifier();
        productId = serialInfo.productIdentifier();
        arduinoAvailabe = true;
    }
    //if(arduinoAvailabe) qDebug() << "Conexión con arduino exitosa"; else{qDebug() << "Conexión con arduino NO exitosa";}
    if(arduinoAvailabe){
        qDebug() << "Se encontró un arduino, iniciando conexión";
        //arduinoInit();
    }else{
        qDebug() << "No se encontró un arduino";
    }
}

void serial_management::test(){
    qDebug() << "Esto es una prueba";
}

void serial_management::arduinoInit()
{
    serial-> setPortName(portName);
    serial-> setBaudRate(QSerialPort::Baud9600);    //Misma que en arduino
    serial-> setDataBits(QSerialPort::Data8);    //La longitud de la cadena de datos que se envia mediante el puerto serial
    serial-> setParity(QSerialPort::NoParity);
    serial-> setStopBits(QSerialPort::OneStop);
    serial-> setFlowControl(QSerialPort::NoFlowControl);
    serial-> open(QIODevice::ReadWrite);

    connect(serial, SIGNAL(readyRead()),this,SLOT(serial_read()));

    if (serial->isOpen()){
        qDebug() << "Coneción con arduino exitosa";
                    ui->pushButton_3->setText("Desconectar");
    }else{
        qDebug() << "No se pudo conectar con el arduino";
        ui->pushButton_3->setText("Conectar");
    }
}

