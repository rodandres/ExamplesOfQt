#include "serialmanagemnet.h"
#include <QObject> // Agrega esta línea

serialmanagemnet::serialmanagemnet()
{
    microController = new QSerialPort(); //Incializa la variabñe serial puesta en el header
    microcontrollerAvailable = false;
    serialBuffer = "";
}
void serialmanagemnet::search_controller()
{
  /*  qDebug()<<"Entro desde aqui";
    //Buscar informacion del arduino en cada puerto serial
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        qDebug()<<"Puerto: " << serialInfo.portName(); //PortDescription en python
        portName = serialInfo.portName();
        qDebug() << "Vendor ID: " << serialInfo.vendorIdentifier();
        vendorId = serialInfo.vendorIdentifier();
        qDebug() << "Product ID: " << serialInfo.productIdentifier();
        productId = serialInfo.productIdentifier();
        microcontrollerAvailable = true;
    }
    //if(arduinoAvailabe) qDebug() << "Conexión con arduino exitosa"; else{qDebug() << "Conexión con arduino NO exitosa";}
    if(microcontrollerAvailable){
        qDebug() << "Se encontró un arduino, iniciando conexión";
        microcontroller_init();
    }else{
        qDebug() << "No se encontró un arduino";
    }*/
}


void serialmanagemnet::microcontroller_init(QString portDescription)
{
    microController-> setPortName(portName);
    microController-> setBaudRate(QSerialPort::Baud9600);    //Misma que en arduino
    microController-> setDataBits(QSerialPort::Data8);    //La longitud de la cadena de datos que se envia mediante el puerto serial
    microController-> setParity(QSerialPort::NoParity);
    microController-> setStopBits(QSerialPort::OneStop);
    microController-> setFlowControl(QSerialPort::NoFlowControl);
    microController-> open(QIODevice::ReadWrite);

    connect(microController, SIGNAL(readyRead()),this,SLOT(serial_read()));

    if (microController->isOpen()){
        qDebug() << "Coneción con" << portDescription<<" exitosa";
    }else{
        qDebug() << "No se pudo conectar con " << portDescription;
    }
}

void serialmanagemnet::serial_read()
{
    QString data;
    QMap<QChar, QStringList> categoryDataMap;  // Usar un QMap para categorías
    const int limiteDatosPorCategoria = 10;


    if (microController->isReadable() && microcontrollerAvailable) {
        // Leer datos del puerto serial
        serialData = microController->readAll();
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
    microController->close();
    qDebug() << "Conexión terminada";
}

void serialmanagemnet::send_data(QString data)
{
    if(microController->isWritable()){
        microController->write(data.toUtf8());
    }else{
        qDebug()<<"No se pueden enviar los datos";
    }
}

void serialmanagemnet::search_port_description()
{
    microControllerNames.clear();
    //QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    foreach(const QSerialPortInfo& port, QSerialPortInfo::availablePorts())
    {
        microControllerNames.append(port.description());
    }
}

void serialmanagemnet::microcontroller_conecction(QString portDescription)
{
    //Buscar informacion del arduino en cada puerto serial
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {
        if(serialInfo.description() == portDescription){
            qDebug()<<"Puerto: " << serialInfo.portName(); //PortDescription en python
            portName = serialInfo.portName();
            qDebug() << "Vendor ID: " << serialInfo.vendorIdentifier();
            vendorId = serialInfo.vendorIdentifier();
            qDebug() << "Product ID: " << serialInfo.productIdentifier();
            productId = serialInfo.productIdentifier();
            microcontrollerAvailable = true;
            break;
        }else{
            microcontrollerAvailable = false;
        }
    }
    //if(arduinoAvailabe) qDebug() << "Conexión con arduino exitosa"; else{qDebug() << "Conexión con arduino NO exitosa";}
    if(microcontrollerAvailable){
        qDebug() << "Se encontró un " << portDescription <<", iniciando conexión";
        microcontroller_init(portDescription);
    }else{
        qDebug() << "No se encontró a " << portDescription;
    }
}

void serialmanagemnet::test()
{
    microControllerNames.clear();
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

    // Recorrer la lista e imprimir la descripción de cada puerto
    foreach(const QSerialPortInfo& port, availablePorts)
    {
        //qDebug() << "Descripción del puerto:" << port.description();
        microControllerNames.append(port.description());
    }
    qDebug()<<"Entro";
    foreach(QString a, microControllerNames){
        qDebug()<<a;
    }

}

