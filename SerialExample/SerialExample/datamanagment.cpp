#include "datamanagment.h"

datamanagment::datamanagment()
{

}

void datamanagment::pathSelection() //Seleccionar la ruta y nombre del archivo donde se van a guardar
{
    directorioSeleccionado = QFileDialog::getSaveFileName(nullptr, "Guardar Archivo", QDir::homePath(), "Archivos CSV (*.csv)"); //Generar ventana de seleccion de nombre y carpeta
    qDebug() << directorioSeleccionado;
}

void datamanagment::fileCreation()  //Crear el archivo con la ruta especficicada
{
    pathSelection();    //Hacer la seleccion de la ruta y nombre
    dataFile.setFileName(directorioSeleccionado);   //Crear el archivo en la ruta y nombre seleccionada

    if (dataFile.open(QIODevice::WriteOnly | QIODevice::Text)) {    //Abrir el archivo para esecritura solamente
        qDebug() << "Archivo abierto para escritura.";
    } else {
        qDebug() << "Error al abrir el archivo para escritura: ";
    }   
}

void datamanagment::dataWrite(QString data) //Escribir datos en el archivo
{
    if(dataFile.isOpen()){  //Asegurarse que el archivo este abierto
        qDebug()<<data;
        QTextStream stream(&dataFile);
        stream << data << "," << data<<"2"<<","<<data<<"3"<<"\n";
    }
    //closeFile();
}

void datamanagment::closeFile() //Cerrar el archivo
{
    dataFile.close(); //Cerrar el archivo
}
