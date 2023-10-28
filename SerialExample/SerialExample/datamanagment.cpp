#include "datamanagment.h"

datamanagment::datamanagment()
{

}

void datamanagment::pathSelection()
{
    directorioSeleccionado = QFileDialog::getSaveFileName(nullptr, "Guardar Archivo", QDir::homePath(), "Archivos CSV (*.csv)");//QFileDialog::getExistingDirectory(nullptr, "Seleccionar Carpeta", QDir::homePath());
    qDebug() << directorioSeleccionado;
}

void datamanagment::fileCreation()
{
    pathSelection();
    dataFile.setFileName(directorioSeleccionado);

    if (dataFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Archivo abierto para escritura.";
    } else {
        qDebug() << "Error al abrir el archivo para escritura: " << dataFile.errorString();
    }

    dataWrite("Creacion");
}

void datamanagment::dataWrite(QString data)
{
    if(dataFile.isOpen()){
        qDebug()<<data;
        QTextStream stream(&dataFile);
        stream << data << "," << data<<"2"<<","<<data<<"3"<<"\n";
    }
    //closeFile();
}

void datamanagment::closeFile()
{
    dataFile.close();
}
