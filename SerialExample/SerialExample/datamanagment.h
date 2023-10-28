#ifndef DATAMANAGMENT_H
#define DATAMANAGMENT_H

#include <QObject>
#include <QFileDialog>

class datamanagment : public QObject
{
    Q_OBJECT
public:
    datamanagment();

    void fileCreation();
    void dataWrite(QString data);
    void closeFile();

    QString directorioSeleccionado;
    QFile dataFile;

private:
    void pathSelection();
};


#endif // DATAMANAGMENT_H
