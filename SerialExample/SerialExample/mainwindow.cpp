#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialObj = new serialmanagemnet; // Declarar "objeto" como un puntero
    serialObj->search_arduino();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    serialObj->send_data("Esto es una cadena a enviar");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setText("AQUI");
    serialObj->test();

    ui->comboBox->clear();


    foreach (QString data, serialObj->microControllerNames) {
        ui->comboBox->addItem(data);
    }

}


void MainWindow::on_pushButton_3_clicked() //Boton de conectar/desconectar microcontrolador
{
    if(serialObj->microController->isOpen()){
        serialObj->serial_close();
        ui->pushButton_3->setText("Conectar");
    }else{
     serialObj->search_arduino();
        ui->pushButton_3->setText("Desconectar");
    }
}



void MainWindow::on_comboBox_activated(int index)
{
    int indiceSeleccionado = ui->comboBox->currentIndex(); // Obtiene el índice del elemento seleccionado
    if (indiceSeleccionado != -1) {
        // Si el índice seleccionado es diferente de -1, significa que hay un elemento seleccionado
        // Ahora puedes realizar acciones basadas en el índice o acceder al valor del elemento
        QString valorSeleccionado = ui->comboBox->itemText(indiceSeleccionado);
        qDebug()<<valorSeleccionado;// Realiza acciones con el índice o el valor del elemento seleccionado
    } else {
        // No hay elemento seleccionado en el QComboBox
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
}

