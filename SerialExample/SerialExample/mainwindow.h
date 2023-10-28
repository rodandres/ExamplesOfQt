#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QFileDialog>

//For dataManagement
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

#include "serialmanagemnet.h"
#include"datamanagment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();



    void on_comboBox_activated(int index);

    void on_pushButton_4_clicked();

    void on_btn_ruta_clicked();

    void on_btn_test_clicked();

    void on_btn_guardarDatos_clicked();

    void on_btnSendData_clicked();

    void on_btnSearchControllers_clicked();

    void on_btnDisconnect_clicked();

private:
    Ui::MainWindow *ui;

    serialmanagemnet *serialObj; // Declarar objeto como un puntero
    datamanagment *dataObj; // Declarar objeto como un puntero

//Data management
    QString directorioSeleccionado;
};
#endif // MAINWINDOW_H
