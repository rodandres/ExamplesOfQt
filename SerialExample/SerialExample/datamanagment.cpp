#include "datamanagment.h"

datamanagment::datamanagment()
{

}

void datamanagment::pathSelection()
{
    directorioSeleccionado = QFileDialog::getExistingDirectory(nullptr, "Seleccionar Carpeta", QDir::homePath());
    qDebug() << directorioSeleccionado;
}

void datamanagment::fileCreation(QString fileName, QString filePath)
{
    QString filePathAndName = filePath+"/"+fileName+".csv";
    qDebug()<<filePathAndName;
    //dataFile.setFileName(filePathAndName);
}


