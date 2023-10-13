#include "serialmanagemnet.h"
#include <QObject> // Agrega esta línea

serialmanagemnet::serialmanagemnet()
{
    serial = new QSerialPort(); //Incializa la variabñe serial puesta en el header
    arduinoAvailabe = false;
    serialBuffer = "";
}
void serialmanagemnet::search_arduino()
{
    qDebug()<<"Entro desde aqui";
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
        arduinoInit();
    }else{
        qDebug() << "No se encontró un arduino";
    }
}


void serialmanagemnet::arduinoInit()
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
   //                 ui->pushButton_3->setText("Desconectar");
    }else{
        qDebug() << "No se pudo conectar con el arduino";
     //   ui->pushButton_3->setText("Conectar");
    }
}

void serialmanagemnet::serial_read()
{
    QString data;
    QMap<QChar, QStringList> categoryDataMap;  // Usar un QMap para categorías
    const int limiteDatosPorCategoria = 10;


    if (serial->isReadable() && arduinoAvailabe) {
        // Leer datos del puerto serial
        serialData = serial->readAll();
        //Asegurarse que los elementos se leen correctamente
        serialBuffer += QString::fromStdString(serialData.toStdString());

        // Dividir la cadena en elementos utilizando ',' como separador
        QStringList bufferSplit = serialBuffer.split(',', Qt::SkipEmptyParts);  //ADATO, BDATO,


            // Procesar los elementos divididos
            foreach (const QString &element, bufferSplit) {
            // Procesamiento con cada elemento
            //Verificar que el elemento no este vacio por algún error
            qDebug() << "Elemento:" << element;
            // Verificar que el elemento no esté vacío por algún error
            if (!element.isEmpty()) {
                // Saber el primer carácter del elemento que corresponde a la categoría
                QChar categoryIdentifier = element.at(0);
                // Obtener los datos (eliminar la categoría)
                data = element.mid(1);


                // Obtener la lista de datos de la categoría
                QStringList &categoryDataList = categoryDataMap[categoryIdentifier];

                // Verificar si la lista supera el límite de datos
                if (categoryDataList.size() >= limiteDatosPorCategoria) {
                    // Si supera el límite, elimina el elemento más antiguo (el primero)
                    categoryDataList.pop_front();
                }

                // Usar el QMap para categorías
                categoryDataList.append(data);



                qDebug() << "Categoria: " << categoryIdentifier;
                qDebug() << "Dato: " << data;
            }
        }
    }
    qDebug() << "Categoría A:" << categoryDataMap['A'];
        qDebug() << "Categoría B:" << categoryDataMap['B'];
        qDebug() << "Categoría C:" << categoryDataMap['C'];

}

void serialmanagemnet::serial_close()
{
    qDebug() << "Conexión terminada";
    //ui->pushButton_3->setText("Conectar");
}

void serialmanagemnet::test()
{
    qDebug() << "Esto se envia dese serialmanagemnt.cpp";
}

