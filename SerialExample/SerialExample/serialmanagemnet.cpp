#include "serialmanagemnet.h"
#include <QObject> // Agrega esta línea

serialmanagemnet::serialmanagemnet()
{
    microController = new QSerialPort(); //Incializa la variabñe serial puesta en el header
    microcontrollerAvailable = false;
    serialBuffer = "";
}


void serialmanagemnet::search_port_description()
{
    microControllerNames.clear();   //Borrar la lista anterior que contiene todos los micrcontroladores antes disponibles
    foreach(const QSerialPortInfo& port, QSerialPortInfo::availablePorts()) //Añadir a la lista los microcontoladores que se encuentren disponibles
    {
        microControllerNames.append(port.description());
    }
}

void serialmanagemnet::microcontroller_conecction(QString portDescription)
{
    foreach (const QSerialPortInfo &serialInfo, QSerialPortInfo::availablePorts()) {    //Buscar cada microcontrolador disponible para conexion
        if(serialInfo.description() == portDescription){    //Si detecta el microcontrolador seleccionado por el usuario, obtiene los datos
            qDebug()<<"Puerto: " << serialInfo.portName();
            portName = serialInfo.portName();
            qDebug() << "Vendor ID: " << serialInfo.vendorIdentifier();
            vendorId = serialInfo.vendorIdentifier();
            qDebug() << "Product ID: " << serialInfo.productIdentifier();
            productId = serialInfo.productIdentifier();
            microcontrollerAvailable = true;    // Confirma que el micrcontrolador sí está disponible
            break;
        }else{
            microcontrollerAvailable = false;   //Si no encuentra el micrcontrolador seleccionado por el usuario
        }
    }

    if(microcontrollerAvailable){   //Si hay confirmacion de micrcontrolador disponible, inicializa la conexion
        qDebug() << "Se encontró un " << portDescription <<", iniciando conexión";
        microcontroller_init(portDescription);  //Inicia la conexion con el micrcontrolador seleccionado por el usuario
    }else{
        qDebug() << "No se encontró a " << portDescription; //No se enconro el microcontrolador seleccionado por el usuario, devuelve el mensaje
    }
}



void serialmanagemnet::microcontroller_init(QString portDescription)    //Inicializa la conexion con el microcontrolador especificado por el usuario
{
    microController-> setPortName(portName);
    microController-> setBaudRate(QSerialPort::Baud9600);    //Tiene que ser la Misma que en arduino
    microController-> setDataBits(QSerialPort::Data8);    //La longitud de la cadena de datos que se envia mediante el puerto serial
    microController-> setParity(QSerialPort::NoParity);
    microController-> setStopBits(QSerialPort::OneStop);
    microController-> setFlowControl(QSerialPort::NoFlowControl);
    microController-> open(QIODevice::ReadWrite);

    connect(microController, SIGNAL(readyRead()),this,SLOT(serial_read())); //Conecta la señal de que llega un dato por el serial con el slot de leer el dato

    if (microController->isOpen()){ //Si se pudo conectar con el microcontrolador, especifica el mensaje
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


    if (microController->isReadable() && microcontrollerAvailable) {    //Asegurarse que el micrcontrolador esta disponible y se puede leer
        // Leer datos del puerto serial
        serialData = microController->readAll();
        //Asegurarse que los elementos se leen correctamente
        serialBuffer += QString::fromStdString(serialData.toStdString());

        // Dividir la cadena en elementos utilizando ',' como separador
        QStringList bufferSplit = serialBuffer.split(',', Qt::SkipEmptyParts);  //ADATO, BDATO,...

            // Procesar los elementos divididos
            foreach (const QString &element, bufferSplit) {
            // Procesamiento con cada elemento

//            qDebug() << "Elemento:" << element;
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

void serialmanagemnet::serial_close()   //Terminar conexión con el serial
{
    microController->close();
    qDebug() << "Conexión terminada";
}

void serialmanagemnet::send_data(QString data) //Para enviar datos al arduino
{
    if(microController->isWritable()){  //Asegurarse que se puede escribir por el puerto seril
        microController->write(data.toUtf8());  //Enviar el dato correctamente
    }else{
        qDebug()<<"No se pueden enviar los datos";
    }
}


void serialmanagemnet::test() // Para porbar cosas
{
}

