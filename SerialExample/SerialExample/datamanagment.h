#ifndef DATAMANAGMENT_H
#define DATAMANAGMENT_H

#include <QObject>
#include <QFileDialog>

class datamanagment : public QObject
{
    Q_OBJECT
public:
    datamanagment();

    void pathSelection();
    void fileCreation(QString fileName, QString filePath);

    QString directorioSeleccionado;
    QFile dataFile;

private:
};


#endif // DATAMANAGMENT_H
